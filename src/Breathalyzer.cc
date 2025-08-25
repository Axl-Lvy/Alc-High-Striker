//
// Created by Axel on 25/08/2025.
//

#include <Arduino.h>

#include "Breathalyzer.h"

#define WARMUP_TIME 20000 // Time in milliseconds to warm up the sensor


Breathalyzer::Breathalyzer(const int analogPin, const int thresholdPin) : analogPin(analogPin),
                                                                          thresholdPin(thresholdPin) {
  if (thresholdPin > 0) {
    pinMode(thresholdPin, INPUT);
  }
  pinMode(analogPin, INPUT);
  ready = false;
  startTime = millis();
}

Breathalyzer::Breathalyzer(const int analogPin) : Breathalyzer(analogPin, -1) {
}

float Breathalyzer::getWarmupPercent() {
  if (ready) {
    return 1.0;
  }
  const long current = millis();
  ready = current - startTime >= WARMUP_TIME;
  if (ready) {
    return 1.0;
  }
  const long elapsed = current - startTime;
  return static_cast<float>(elapsed) / static_cast<float>(WARMUP_TIME);
}

int Breathalyzer::getAlcoholLevel() const {
  if (!ready) {
    return -1;
  }
  return analogRead(analogPin);
}
