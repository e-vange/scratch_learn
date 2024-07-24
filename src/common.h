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

#endif
