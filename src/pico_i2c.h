#ifndef pico_i2c_h
#define pico_i2c_h

#include "common.h"

void setup_i2c(void);

RET_TYPE read_i2c0_byte(uint8 addr, uint8 reg_addr, uint8* data);
RET_TYPE write_i2c0_byte(uint8 addr, uint8 reg_addr, uint8* data);
void test_i2c(void);

#endif
