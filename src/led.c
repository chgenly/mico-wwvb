#include "hardware.h"
#include "led.h"
#include <util/delay.h>

#define D 100

void led_loop_top() {
        G_ON;
        B_ON;
         _delay_ms(D);
        G_OFF;
        B_OFF;
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
