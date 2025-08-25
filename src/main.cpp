#include <Arduino.h>

#include "Breathalyzer.h"
#include "Buzzer.h"
#include "Display.h"

#define MQ3pin 0

Buzzer buzzer(13, 120.0);
Breathalyzer breathalyzer(MQ3pin);
Display display(new byte[4]{12, 9, 8, 6}, new byte[8]{11, 7, 4, 2, 1, 10, 5, 3});
constexpr long refreshInterval = 0;
unsigned long previous = 0;

void setup() {}

void loop() {
  buzzer.play();
  const float warmupPercent = breathalyzer.getWarmupPercent();
  if (warmupPercent < 1.0f) {
    display.displayPercent(warmupPercent);
  } else {
    const unsigned long current = millis();
    if (current - previous >= refreshInterval) {
      previous = current;
      const int alcoholLevel = breathalyzer.getAlcoholLevel();
      if (alcoholLevel >= 0) {
        display.displayNumber(alcoholLevel);
      } else {
        display.displayError();
      }
    }
  }
  display.refresh();
}
