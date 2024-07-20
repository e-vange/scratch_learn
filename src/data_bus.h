#ifndef vfb_h
#define vfb_h

#include "pico_types.h"

extern uint16 V_Temperature;

static inline uint16 GetTemperature(void) {
    return V_Temperature;
}

static inline void SetTemperature(uint16 Temperature) {
    V_Temperature = Temperature;
}

#endif
