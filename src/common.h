#ifndef common_h
#define common_h

#include "pico_types.h"
#include "data_bus.h"

static uint16 lib_pack_u8_2_u16(uint8 LSB, uint8 MSB) {
    uint16 u16_buff = 0;
    uint16 u16_msb = 0;

    u16_buff = (uint16) LSB;

    u16_msb = ((uint16)MSB << 8) & 0xFF00;

    u16_buff |=  u16_msb;

    return u16_buff;
}

static int16 lib_pack_u8_2_s16(uint8 LSB, uint8 MSB) {
    return (int16)lib_pack_u8_2_u16(LSB, MSB);
}

static uint16 lib_linear_interp_s16(int16 x0,
                                    int16 x1,
                                    uint16 y0,
                                    uint16 y1,
                                    int16 x) {
    uint16 x_proportion = 0;
    uint16 y = 0;

    x_proportion = (uint16) ((x - x0) / (x1 - x0));

    y = (y1 - y0) * x_proportion;

    return y;
}

#endif
