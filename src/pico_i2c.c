#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico_i2c.h"

// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C0_PORT i2c0
#define I2C0_SDA 12
#define I2C0_SCL 13


void setup_i2c(void){
    uint retval;

    // I2C Initialisation. Using it at 400Khz.
    retval = i2c_init(I2C0_PORT, 400*1000);

    gpio_set_function(I2C0_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C0_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C0_SDA);
    gpio_pull_up(I2C0_SCL);
    // For more examples of I2C use see https://github.com/raspberrypi/pico-examples/tree/master/i2c
}

void test_i2c(void) {
    uint retval;
    uint8 retbuff;

    printf("write test\n");
    retval = i2c_write_blocking(I2C0_PORT, 0x5F, &retbuff, 1, false);
    printf("test ret %d\n", retval);

}

RET_TYPE read_i2c0_byte(uint8 addr, uint8 reg_addr, uint8* data) {
    int retval;

    retval = i2c_write_blocking(I2C0_PORT, addr, &reg_addr, (size_t)1, true);

    if (retval == PICO_ERROR_GENERIC){
        return RET_FAIL;
    }

    retval = i2c_read_blocking(I2C0_PORT, addr, data, (size_t)1, false);

    if (retval == PICO_ERROR_GENERIC){
        return RET_FAIL;
    }

    return RET_OK;
}

RET_TYPE write_i2c0_byte(uint8 addr, uint8 reg_addr, uint8* data) {
    int retval;

    retval = i2c_write_blocking(I2C0_PORT, addr, &reg_addr, (size_t)1, true);

    if (retval == PICO_ERROR_GENERIC){
        return RET_FAIL;
    }

    retval = i2c_write_blocking(I2C0_PORT, addr, data, (size_t)1, false);

    if (retval == PICO_ERROR_GENERIC){
        return RET_FAIL;
    }

    return RET_OK;
}


