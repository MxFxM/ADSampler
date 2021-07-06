#include <Arduino.h>

class ADSampler {
    public:
        ADSampler(void);

        void setup(void);

        void startSampling(void);
        void stopSampling(void);

        void setSampleRate(int samplerate);

        int getSampleRate(void);
};