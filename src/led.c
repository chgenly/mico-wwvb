#include "hardware.h"
#include "led.h"
#include <util/delay.h>

#define D 100

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

void led_begin_wait_for_start_bit() {
    G_ON;
}

void led_end_wait_for_start_bit() {
    G_OFF;
}

void led_begin_wait_for_dollar() {
    B_ON;
}

void led_end_wait_for_dollar() {
    B_OFF;
}
