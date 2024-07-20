#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#define USER_LED 25

bool user_led_state = false;

void setup_LED(void) {
    // set up user LED on board
    gpio_init(USER_LED);
    gpio_set_dir(USER_LED, GPIO_OUT);
}

void toggleUserLED(void) {
    user_led_state = !user_led_state;
    gpio_put(USER_LED, user_led_state);
}

