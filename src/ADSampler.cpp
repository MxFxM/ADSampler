#include <Arduino.h>

#include <ADSampler.hpp>

///#include <ADC.h>
//#include <ADC_util.h>

/*!
 * @brief Constructor
 *
 * Constructor is called when a new object of the class is initialized.
 * Do not create more than one object of the ADSampler class!
 */
ADSampler::ADSampler(void) {
    // create a dma buffer for the first adc
    DMAMEM static volatile uint16_t __attribute__((aligned(32))) dma_adc_buff1[buffer_size];
    abdma1 = new AnalogBufferDMA(dma_adc_buff1, buffer_size);

    // create a dma buffer for the second adc
    DMAMEM static volatile uint16_t __attribute__((aligned(32))) dma_adc_buff2[buffer_size];
    abdma2 = new AnalogBufferDMA(dma_adc_buff2, buffer_size);
}

/*!
 * @brief Setup
 *
 * The setup is called once at the beginning of the code.
 * All pins are initialized.
 * General ADC setup is performed.
 * 
 * @param adc_0_pin input pin for the first adc
 * @param adc_1_pin input pin for the second adc
 */
void ADSampler::setup(int adc_0_pin, int adc_1_pin) {
    // copy pin numbers to class
    adc0_pin = adc_0_pin;
    adc1_pin = adc_1_pin;

    // adc pins are inputs
    pinMode(adc0_pin, INPUT);
    pinMode(adc1_pin, INPUT);

    // set the averaging and the ADC resolution
    adc->adc0->setAveraging(AVERAGING_SAMPLES);
    adc->adc0->setResolution(ANALOG_RESOLUTION);
    adc->adc0->setSamplingSpeed(ADC_SAMPLING_SPEED::VERY_HIGH_SPEED);
    adc->adc0->setConversionSpeed(ADC_CONVERSION_SPEED::VERY_HIGH_SPEED);

    adc->adc1->setAveraging(AVERAGING_SAMPLES);
    adc->adc1->setResolution(ANALOG_RESOLUTION);
    adc->adc1->setSamplingSpeed(ADC_SAMPLING_SPEED::VERY_HIGH_SPEED);
    adc->adc1->setConversionSpeed(ADC_CONVERSION_SPEED::VERY_HIGH_SPEED);

    // setup the dma channel
    abdma1->init(adc, ADC_0);
    abdma2->init(adc, ADC_1);

    //abdma1->stopOnCompletion(true);
    //abdma2->stopOnCompletion(true);

    // setup the adc multiplexing
    adc->adc0->startSingleRead(adc0_pin);
    adc->adc1->startSingleRead(adc1_pin);
}

/*!
 * @brief Start Sampling
 *
 * Start the sampling with the previously defined frequency
 */
void ADSampler::startSampling(void) {
    abdma1->clearInterrupt();
    abdma2->clearInterrupt();
    abdma1->clearCompletion();
    abdma2->clearCompletion();

    // setup the dma channel
    abdma1->init(adc, ADC_0);
    abdma2->init(adc, ADC_1);

    //adc->adc0->startSingleRead(adc0_pin);
    //adc->adc1->startSingleRead(adc1_pin);

    adc->adc0->startTimer(SAMPLE_RATE);
    adc->adc1->startTimer(SAMPLE_RATE);
}

/*!
 * @brief Stop Sampling
 *
 */
void ADSampler::stopSampling(void) {
    adc->adc0->stopTimer();
    adc->adc1->stopTimer();

    //abdma1->clearInterrupt();
    //abdma2->clearInterrupt();
    //abdma1->clearCompletion();
    //abdma2->clearCompletion();
}

/*!
 * @brief Get Sample Rate
 *
 * Get the real sample rate.
 * It can differ from the set sampling rate, because the CPU clock limits the possibilities.
 * Both ADCs run at the same sample rate.
 * This value is valid, when the ADCs are running.
 * 
 * @return sample rate in Hz
 */
uint32_t ADSampler::getSampleRate(void) {
    return adc->adc0->getTimerFrequency();
}

/*!
 * @brief Get Status
 *
 * Check if both ADC channels have filled up their buffers.
 * 
 * @return true, if both ADC buffers are full
 */
boolean ADSampler::getDone(void) {
    return (abdma1->interrupted() && abdma2->interrupted());
}

/*!
 * @brief Print Values
 *
 * Write the values of both buffers to the stream.
 * The values are written as bytes.
 * The high byte followed by the low byte (16 bit values).
 * For each entry in the buffers, first the ADC 0 value is written, then ADC 1.
 * Between each entry the combination \r\n is written.
 * This is 0x0D 0x0A in hex.
 * 
 * @param *s pointer to the output stream
 */
void ADSampler::print(Stream *s) {
    uint8_t cr = 0x0D;
    uint8_t lf = 0x0A;

    volatile uint16_t *pbuffer0 = abdma1->bufferLastISRFilled();
    volatile uint16_t *end_pbuffer0 = pbuffer0 + abdma1->bufferCountLastISRFilled();

    volatile uint16_t *pbuffer1 = abdma2->bufferLastISRFilled();
    volatile uint16_t *end_pbuffer1 = pbuffer1 + abdma2->bufferCountLastISRFilled();

    while (pbuffer0 < end_pbuffer0 && pbuffer1 < end_pbuffer1) {
        s->write(*pbuffer0 >> 8 & 0xFF);
        s->write(*pbuffer0 & 0xFF);
        s->write(*pbuffer1 >> 8 & 0xFF);
        s->write(*pbuffer1 & 0xFF);
        pbuffer0++;
        pbuffer1++;
        s->write(cr);
        s->write(lf);
    }

    s->write(cr);
    s->write(lf);
}