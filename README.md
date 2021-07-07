# ADSampler

Samples the Teensy 4.1 ADCs.

## Note:

This requires a change in the DMA library:
In file "AnalogBufferDMA.cpp" add the line "#include <ADC.h>" at the top.