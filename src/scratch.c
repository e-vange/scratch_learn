#include <stdio.h>
#include "pico/stdlib.h"
#include "common.h"
#include "init_controller.h"
#include "pico_led.h"
#include "temp_sensor.h"

int main() {
    init_controller();

    printf("Controller Init Done\n");

    init_temp_sensor();

    printf("Entering Periodic Loop\n");
    uint8 counter = 0;

    while (1) {
        toggleUserLED();
        printf("Loop Cnt: %d ", counter);
        counter++;

        temp_sensor_loop();

        printf("\n");

        sleep_ms(1000);
    }
}
