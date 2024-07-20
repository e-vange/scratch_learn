#include <stdio.h>
#include "common.h"
#include "pico_i2c.h"

const uint8 addr_temp_hum = 0b1011111;

uint8 get_whoami(void) {
    uint8 ret_buff = 0;
    RET_TYPE ret_val;

    ret_val = read_i2c0_byte(addr_temp_hum, 0x0F, &ret_buff);

    if (ret_val == RET_OK) {
        return ret_buff;
    }
    else {
        return (uint8)0;
    }
}

uint16 read_temperature(void) {
    RET_TYPE ret_val;
    uint8    ret_buff;
    uint16   Temperature;

    // read LSB
    ret_val = read_i2c0_byte(addr_temp_hum, 0x2A, &ret_buff);

    Temperature = ret_buff;

    // read MSB
    ret_val = read_i2c0_byte(addr_temp_hum, 0x2A, &ret_buff);

    Temperature |= ret_buff << 8;

    return Temperature;

}

void temp_sensor_loop(void) {
    uint8 check_addr;
    uint16 Temperature = 0;

    check_addr = get_whoami();

    Temperature = read_temperature();

    SetTemperature(Temperature);


    printf("whoami ret: %d ", check_addr);
    printf("temp: %d ", GetTemperature());
}
