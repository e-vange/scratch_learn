#include "pico/stdlib.h"
#include "pico_led.h"
#include "pico_spi.h"
#include "pico_i2c.h"


void init_controller(void){
    stdio_init_all();

    setup_LED();
    // setup_spi();
    setup_i2c();

}
