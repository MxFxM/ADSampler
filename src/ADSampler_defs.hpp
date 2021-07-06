#include <Arduino.h>

// ================================================================================================
// = USER DEFINED SECTION                                                                         =
// ================================================================================================

#define BUFFER_SIZE 8000

#define AVERAGING_SAMPLES 1

#define ANALOG_RESOLUTION 10

// ================================================================================================
// = DO NOT CHANGE THIS SECTION                                                                         =
// ================================================================================================

#if ANALOG_RESOLUTION == 8
    #define ANALOG_STEPS 256
    #define ANALOG_MAX 255
#elif ANALOG_RESOLUTION == 9
    #define ANALOG_STEPS 512
    #define ANALOG_MAX 511
#elif ANALOG_RESOLUTION == 10
    #define ANALOG_STEPS 1024
    #define ANALOG_MAX 1023
#elif ANALOG_RESOLUTION == 11
    #define ANALOG_STEPS 2048
    #define ANALOG_MAX 2047
#elif ANALOG_RESOLUTION == 12
    #define ANALOG_STEPS 4096
    #define ANALOG_MAX 4095
#else
#endif