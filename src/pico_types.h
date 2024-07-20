#ifndef pico_types_h
#define pico_types_h

// Includes
#include <stdint.h>

// boolean
#define TRUE (bool)1;
#define FALSE (bool)0;

// ints
typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef int8_t   int8;
typedef int16_t  int16;
typedef int32_t  int32;


// Return type
typedef enum RET_TYPE{
    RET_OK,
    RET_FAIL,
    RET_WARN,
} RET_TYPE;

#endif
