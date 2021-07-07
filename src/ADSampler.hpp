#include <Arduino.h>

#include <ADSampler_defs.hpp>

#include <ADC.h>
#include <DMAChannel.h>
#include <AnalogBufferDMA.h>

#include <Stream.h>


class ADSampler {
    ADC *adc = new ADC();

    static const uint32_t buffer_size = BUFFER_SIZE;

    AnalogBufferDMA *abdma1;
    AnalogBufferDMA *abdma2;

    int adc0_pin;
    int adc1_pin;

    public:
        ADSampler(void);

        void setup(int adc_0_pin, int adc_1_pin);

        void startSampling(void);
        void stopSampling(void);

        uint32_t getSampleRate(void);
        boolean getDone(void);

        void print(Stream *s);
};