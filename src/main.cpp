#include <Arduino.h>

#include <ADSampler.hpp>

ADSampler sampler = ADSampler();

#define ADC0_PIN A0
#define ADC1_PIN A1

#define PWM_PIN 9

volatile boolean converting = false;

volatile uint32_t starttime;
volatile uint32_t endtime;

void setup() {
  sampler.setup(ADC0_PIN, ADC1_PIN);

  pinMode(PWM_PIN, OUTPUT);
  analogWriteResolution(9);
  analogWriteFrequency(PWM_PIN, 74000);
  analogWrite(PWM_PIN, 100);

  Serial.begin(9600);
}

void loop() {
  if (converting) {
    if (sampler.getDone()) {
      endtime = micros();

      sampler.stopSampling();
      sampler.print(&Serial);

      Serial.print("Start sampling at ");
      Serial.println(starttime);
      Serial.print("Done sampling at ");
      Serial.println(endtime);
      Serial.print("Sampling took ");
      Serial.println(endtime - starttime);

      Serial.println();
      converting = false;
    }
  } else {
    if (Serial.available()) {
      if (Serial.read() == char('s')) {
        sampler.startSampling();
        starttime = micros();

        converting = true;
      }
    }
  }
}