#include "gps.h"
#include "led.h"
#include <stdbool.h>

#define NMEA_MAX_MSG_LENGTH 82 // including starting '$' and ending '\n'


static inline int is_digit(char c) {
    return ('0' <= c && c <= '9');
}

static inline int to_digit(char c) {
    return c - '0';
}

const char *msg1 = "$PAIR062,0";
const char *msg2 = ",0";
const char *msg3 = "*3";
const char *msg_suffix = "\r\n";

static void gps_init_chunked(
    volatile unsigned char *port,
    unsigned char num,
    baud_rate rate,
    char type,
    char enable,
    char chksum
) {
    serial_put_string(port, num, rate, msg1);
    serial_put_char(port, num, rate, type);
    serial_put_string(port, num, rate, msg2);
    serial_put_char(port, num, rate, enable);
    serial_put_string(port, num, rate, msg3);
    serial_put_char(port, num, rate, chksum);
    serial_put_string(port, num, rate, msg_suffix);
}

void gps_init(
    volatile unsigned char *port,
    unsigned char num,
    baud_rate rate
) {
    // rate control: disable everything
    //
    // Set the rates for all NMEA types, except for ZDA.
    gps_init_chunked(port, num, rate, '0', '0', 'E'); //GGA - GPS fix
    gps_init_chunked(port, num, rate, '1', '0', 'F'); //GLL - Lat and Long
    gps_init_chunked(port, num, rate, '2', '0', 'C'); //GSA
    gps_init_chunked(port, num, rate, '3', '0', 'D'); //GSV - Satellites in view.
    gps_init_chunked(port, num, rate, '4', '0', 'A'); //RMC
    gps_init_chunked(port, num, rate, '5', '0', 'B'); //VTG - Velocity over ground
    gps_init_chunked(port, num, rate, '6', '1', '9'); //ZDA - time date
    gps_init_chunked(port, num, rate, '7', '0', '9'); //GRS
    gps_init_chunked(port, num, rate, '8', '0', '6'); //GST
}

int gps_get_time(
    volatile unsigned char *pin,
    unsigned char pin_num,
    baud_rate rate,
    int *year,
    int *month,
    int *day,
    int *hour,
    int *minute,
    int *second
) {
    // TODO have some kind of timeout (maybe the caller should set that up, though)

    // wait for '$' character
    led_begin_wait_for_dollar();
    while (serial_get_char(pin, pin_num, rate) != '$') {
    }
    led_end_wait_for_dollar();

    // get rest of message
    static char nmea_buf[NMEA_MAX_MSG_LENGTH+1];
    int idx = 0;
    while (idx < NMEA_MAX_MSG_LENGTH) {
        char c = serial_get_char(pin, pin_num, rate);
        nmea_buf[idx] = c;
        idx++;
        if (c == '\n') {
            nmea_buf[idx] = 0;
            break;
        }
    }
    
    // quick sanity check
    // TODO maybe check the checksum?
    // format is "$GPZDA,hhmmss.sss,dd,mm,yyyy,xx,yy*CC"
    //
    // we just want UTC time, so we need it to be at least the length of
    // "GPZDA,hhmmss.sss,dd,mm,yyyy,,*CC\r\n"

    if (idx < 34) {
        return -1; // maybe we don't have the time yet or something else went wrong
    }
    if (nmea_buf[0] != 'G' ||
            (nmea_buf[1] != 'N' && nmea_buf[1] != 'P') ||
            nmea_buf[2] != 'Z' ||
            nmea_buf[3] != 'D' ||
            nmea_buf[4] != 'A') {
        return -1;
    }
    // parse
    if (!is_digit(nmea_buf[6]) || !is_digit(nmea_buf[7])) {
        return -1;
    }
    *hour = to_digit(nmea_buf[6]) * 10 + to_digit(nmea_buf[7]);
    if (!is_digit(nmea_buf[8]) || !is_digit(nmea_buf[9])) {
        return -1;
    }
    *minute = to_digit(nmea_buf[8]) * 10 + to_digit(nmea_buf[9]);
    if (!is_digit(nmea_buf[10]) || !is_digit(nmea_buf[11])) {
        return -1;
    }
    *second = to_digit(nmea_buf[10]) * 10 + to_digit(nmea_buf[11]);
    if (!is_digit(nmea_buf[17]) || !is_digit(nmea_buf[18])) {
            return -1;
    }
    *day = to_digit(nmea_buf[17]) * 10 + to_digit(nmea_buf[18]);
    if (!is_digit(nmea_buf[20]) || !is_digit(nmea_buf[21])) {
        return -1;
    }
    *month = to_digit(nmea_buf[20]) * 10 + to_digit(nmea_buf[21]);
    if (!is_digit(nmea_buf[23]) ||
            !is_digit(nmea_buf[24]) ||
            !is_digit(nmea_buf[25]) ||
            !is_digit(nmea_buf[26])) {
        return -1;
    }
    *year = to_digit(nmea_buf[23]) * 1000 + to_digit(nmea_buf[24]) * 100 +
        to_digit(nmea_buf[25]) * 10 + to_digit(nmea_buf[26]);

    return 0;
}
