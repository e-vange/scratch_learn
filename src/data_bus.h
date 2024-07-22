#ifndef vfb_h
#define vfb_h

#include "pico_types.h"

extern uint16 V_Temperature;
extern uint16 V_Humidity;

static inline uint16 GetTemperature(void) {
    return V_Temperature;
}

static inline void SetTemperature(uint16 Temperature) {
    V_Temperature = Temperature;
}

static inline uint16 GetHumidity(void) {
    return V_Humidity;
}

static inline void SetHumidity(uint16 Humidity) {
    V_Humidity = Humidity;
}

#endif
