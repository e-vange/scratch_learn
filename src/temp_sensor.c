#include <stdio.h>
#include "common.h"
#include "pico_i2c.h"

//#define TEMP_HUM_ADDR 0b1011111
#define TEMP_HUM_ADDR 0x5F

#define WHO_AM_I  0x0F
#define AV_CONF   0x10
#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define STATUS_REG 0x27
#define HUMIDITY_OUT_LSB 0x28
#define HUMIDITY_OUT_MSB 0x29
#define TEMP_OUT_LSB 0x2A
#define TEMP_OUT_MSB 0x2B

#define CAL_T0_degC_x8 0x32
#define CAL_T1_degC_x8 0x33
#define CAL_T0_T1_MSB  0x35
#define CAL_T0_OUT_LSB 0x3C
#define CAL_T0_OUT_MSB 0x3D
#define CAL_T1_OUT_LSB 0x3E
#define CAL_T1_OUT_MSB 0x3F

#define CAL_H0_rH_x2      0x30
#define CAL_H1_rH_x2      0x31
#define CAL_H0_T0_OUT_LSB 0x36
#define CAL_H0_T0_OUT_MSB 0x37
#define CAL_H1_T0_OUT_LSB 0x3A
#define CAL_H1_T0_OUT_MSB 0x3B


/* Configurations */
#define ORD0 0
#define ODR1 1
#define BDR_MODE 0
#define PD_MODE 1


/* Variables */
// temperature
int16 cal_val_T0_OUT = 0;
int16 cal_val_T1_OUT = 0;

uint16 cal_val_T0_DegC = 0;
uint16 cal_val_T1_DegC = 0;

// humidity
int16 cal_val_H0_T0_OUT = 0;
int16 cal_val_H1_T0_OUT = 0;

uint8 cal_val_H0_rH = 0;
uint8 cal_val_H1_rH = 0;




/* Function Definitions */

uint8 get_whoami(void) {
    uint8 ret_buff = 0;
    RET_TYPE ret_val;

    ret_val = read_i2c0_byte(TEMP_HUM_ADDR, WHO_AM_I, &ret_buff);

    if (ret_val == RET_OK) {
        return ret_buff;
    }
    else {
        return (uint8)0;
    }
}

void read_temperature_cals(void) {
    RET_TYPE ret_val = RET_FAIL;

    uint8 raw_t0_degC_x8 = 0;
    uint8 raw_t1_degC_x8 = 0;
    uint8 ret_msb = 0;

    uint8 LSB_buff    = 0;
    uint8 MSB_buff    = 0;

    ret_val = read_i2c0_byte(TEMP_HUM_ADDR, CAL_T0_degC_x8, &raw_t0_degC_x8);
    ret_val = read_i2c0_byte(TEMP_HUM_ADDR, CAL_T0_T1_MSB, &ret_msb);
    cal_val_T0_DegC = lib_pack_u8_2_u16(raw_t0_degC_x8, (ret_msb & 0x03));
    cal_val_T0_DegC = cal_val_T0_DegC/8;

    ret_val = read_i2c0_byte(TEMP_HUM_ADDR, CAL_T1_degC_x8, &raw_t1_degC_x8);
    cal_val_T1_DegC = lib_pack_u8_2_u16(raw_t1_degC_x8, ((ret_msb & 0x0C)>>2));
    cal_val_T1_DegC = cal_val_T1_DegC/8;

    ret_val = read_i2c0_byte(TEMP_HUM_ADDR, CAL_T0_OUT_LSB, &LSB_buff);
    ret_val = read_i2c0_byte(TEMP_HUM_ADDR, CAL_T0_OUT_MSB, &MSB_buff);
    cal_val_T0_OUT = lib_pack_u8_2_s16(LSB_buff, MSB_buff);

    ret_val = read_i2c0_byte(TEMP_HUM_ADDR, CAL_T1_OUT_LSB, &LSB_buff);
    ret_val = read_i2c0_byte(TEMP_HUM_ADDR, CAL_T1_OUT_MSB, &MSB_buff);
    cal_val_T1_OUT = lib_pack_u8_2_s16(LSB_buff, MSB_buff);
}

void read_humidity_cals(void) {
    RET_TYPE ret_val = RET_FAIL;

    uint8 raw_H0_rH_x2 = 0;
    uint8 raw_H1_rH_x2 = 0;

    uint8 LSB_buff    = 0;
    uint8 MSB_buff    = 0;

    ret_val = read_i2c0_byte(TEMP_HUM_ADDR, CAL_H0_rH_x2, &raw_H0_rH_x2);
    cal_val_H0_rH = raw_H0_rH_x2/2;

    ret_val = read_i2c0_byte(TEMP_HUM_ADDR, CAL_H1_rH_x2, &raw_H1_rH_x2);
    cal_val_H1_rH = raw_H1_rH_x2/2;

    ret_val = read_i2c0_byte(TEMP_HUM_ADDR, CAL_H0_T0_OUT_LSB, &LSB_buff);
    ret_val = read_i2c0_byte(TEMP_HUM_ADDR, CAL_H0_T0_OUT_MSB, &MSB_buff);
    cal_val_H0_rH = lib_pack_u8_2_s16(LSB_buff, MSB_buff);

    ret_val = read_i2c0_byte(TEMP_HUM_ADDR, CAL_H1_T0_OUT_LSB, &LSB_buff);
    ret_val = read_i2c0_byte(TEMP_HUM_ADDR, CAL_H1_T0_OUT_MSB, &MSB_buff);
    cal_val_H1_rH = lib_pack_u8_2_s16(LSB_buff, MSB_buff);
}

void get_calibrations(void) {
    read_temperature_cals();
    read_humidity_cals();
}

void init_temp_sensor(void) {
    RET_TYPE ret_val = RET_FAIL;
    uint8 config_byte = 0;

    get_whoami();

    get_calibrations();

    config_byte  = ORD0;
    config_byte |= (ODR1 << 1);
    config_byte |= (BDR_MODE << 2);
    config_byte |= (PD_MODE << 7);

    ret_val = write_i2c0_byte(TEMP_HUM_ADDR, CTRL_REG1, &config_byte);
}

int16 convert_temp(int16 T_out) {
    int16 x_proportion = 0;
    uint16 temperature = 0;

    x_proportion = ((T_out - cal_val_T0_OUT) / (cal_val_T1_OUT - cal_val_T0_OUT));

    temperature = (cal_val_T1_DegC - cal_val_T0_DegC) * x_proportion;

    return temperature;
}

int8 convert_humidity(int16 H_out) {
    uint8  humidity = 0;
    uint16 x_proportion = 0;

    x_proportion = ((H_out - cal_val_H0_T0_OUT) / (cal_val_H1_T0_OUT - cal_val_H0_T0_OUT));

    humidity = (uint8)((cal_val_H1_rH - cal_val_H0_rH) * x_proportion);

    return humidity;
}


uint16 read_temperature(void) {
    RET_TYPE ret_val = RET_FAIL;
    uint8    LSB_buff;
    uint8    MSB_buff;
    int16    temperature_buff;
    uint16   temperature;

    // read LSB
    ret_val = read_i2c0_byte(TEMP_HUM_ADDR, TEMP_OUT_LSB, &LSB_buff);

    // read MSB
    ret_val = read_i2c0_byte(TEMP_HUM_ADDR, TEMP_OUT_MSB, &MSB_buff);

    // combine and convert
    temperature_buff = lib_pack_u8_2_s16(LSB_buff, MSB_buff);

    temperature = convert_temp(temperature_buff);

    return temperature;
}

uint16 read_humidity(void) {
    RET_TYPE ret_val = RET_FAIL;
    uint8    LSB_buff;
    uint8    MSB_buff;
    uint16   humidity_buff;
    uint8    humidity;

    // read LSB
    ret_val = read_i2c0_byte(TEMP_HUM_ADDR, HUMIDITY_OUT_LSB, &LSB_buff);

    // read MSB
    ret_val = read_i2c0_byte(TEMP_HUM_ADDR, HUMIDITY_OUT_MSB, &MSB_buff);

    humidity_buff = lib_pack_u8_2_s16(LSB_buff, MSB_buff);

    humidity = convert_humidity(humidity_buff);

    return humidity;
}

void temp_sensor_loop(void) {
    // uint8 check_addr;
    uint16 Temperature = 0;
    uint8  Humidity = 0;

    // check_addr = get_whoami();

    Temperature = read_temperature();
    Humidity    = read_humidity();

    SetTemperature(Temperature);
    SetHumidity(Humidity);

    // printf("whoami ret: %d ", check_addr);
    printf("temp: %d ", GetTemperature());
    printf("Humid: %d ", GetHumidity());
}
