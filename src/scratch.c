#include <stdio.h>
#include "pico/stdlib.h"
#include "pico_led.h"
#include "init_controller.h"

int main() {
    init_controller();

    int counter = 0;

    while (1) {
        toggleUserLED();
        printf("Hello, world! %d\n", counter);
        counter++;
        sleep_ms(1000);
    }
}
