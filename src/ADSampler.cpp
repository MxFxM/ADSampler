#include <Arduino.h>

#include <ADSampler.hpp>

/*!
 * @brief Constructor
 *
 * Constructor is called when a new object of the class is initialized.
 * Do not create more than one object of the ADSampler class!
 */
ADSampler::ADSampler(void) {}

/*!
 * @brief Setup
 *
 * The setup is called once at the beginning of the code.
 * All pins are initialized.
 * General ADC setup is performed.
 */
void ADSampler::setup(void) {}

/*!
 * @brief Start Sampling
 *
 */
void ADSampler::startSampling(void) {}

/*!
 * @brief Stop Sampling
 *
 */
void ADSampler::stopSampling(void) {}

/*!
 * @brief Set Sample Rate
 *
 * Set the sample rate.
 * The real sample rate can differ, because the CPU clock limits the possibilites.
 * To get the real sample rate, use getSampleRate().
 * 
 * @param samplerate sample rate in Hz
 */
void ADSampler::setSampleRate(int samplerate) {}

/*!
 * @brief Get Sample Rate
 *
 * Get the real sample rate.
 * It can differ from the set sampling rate, because the CPU clock limits the possibilities.
 * 
 * @return sample rate in Hz
 */
int ADSampler::getSampleRate(void) {}