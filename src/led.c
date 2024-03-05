#include "hardware.h"
#include "led.h"
#include <util/delay.h>

#define D 100

/* Flash green and blue leds three times. */
void led_loop_top() {
    for(int i=0; i<3; ++i) {
        G_ON;
        B_ON;
         _delay_ms(D);
        G_OFF;
        B_OFF;
         _delay_ms(D);
    }
}

void flash_green() {
    B_OFF;
    for(int i=0; i<10; ++i) {
        G_ON;
         _delay_ms(D);
        G_OFF;
         _delay_ms(D);
    }
}

void flash_blue() {
    G_OFF;
    for(int i=0; i<10; ++i) {
        B_ON;
         _delay_ms(D);
        B_OFF;
         _delay_ms(D);
    }
}

/* Green on */
void led_begin_wait_for_start_bit() {
    G_ON;
}

/* Green off */
void led_end_wait_for_start_bit() {
    G_OFF;
}

/* Blue on*/
void led_begin_wait_for_dollar() {
    B_ON;
}

/* Blue off */
void led_end_wait_for_dollar() {
    B_OFF;
}

void led_debug(int n) {
    _delay_ms(500);
    for(int i=0; i<n; ++i) {
        B_OFF;
        G_ON;
        _delay_ms(200);
        B_ON;
        G_OFF;
        _delay_ms(200);
    }
    B_OFF;
    _delay_ms(500);
}