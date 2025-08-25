//
// Created by Axel on 25/08/2025.
//

#include <Arduino.h>

#include "Breathalyzer.h"

#define WARMUP_TIME 20000 // Time in milliseconds to warm up the sensor
#define VALUE_STABLE_TIME 2000 // Time in milliseconds before considering the value stable


Breathalyzer::Breathalyzer(const int analogPin, const int thresholdPin) : analogPin(analogPin),
                                                                          thresholdPin(thresholdPin) {
  if (thresholdPin > 0) {
    pinMode(thresholdPin, INPUT);
  }
  pinMode(analogPin, INPUT);
  ready = false;
  startTime = millis();
  value = 0;
  valueChangeTime = startTime;
}

Breathalyzer::Breathalyzer(const int analogPin) : Breathalyzer(analogPin, -1) {
}

float Breathalyzer::getWarmupPercent() {
  if (ready) {
    return 1.0;
  }
  const unsigned long current = millis();
  ready = current - startTime >= WARMUP_TIME;
  if (ready) {
    return 1.0;
  }
  const unsigned long elapsed = current - startTime;
  return static_cast<float>(elapsed) / static_cast<float>(WARMUP_TIME);
}
void Breathalyzer::refreshValue() {
  const int newValue = analogRead(analogPin);
  const unsigned long current = millis();
  if (newValue > value || current - valueChangeTime >= VALUE_STABLE_TIME) {
    value = newValue;
    valueChangeTime = current;
  }
}

int Breathalyzer::getAlcoholLevel() {
  if (!ready) {
    return -1;
  }
  refreshValue();
  return value;
}
