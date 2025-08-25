#include <Arduino.h>

#include "Breathalyzer.h"
#include "Buzzer.h"
#include "Display.h"

Buzzer buzzer(13, 120.0); // NOSONAR
Breathalyzer breathalyzer(0); // NOSONAR
Display display(new byte[4]{12, 9, 8, 6}, new byte[8]{11, 7, 4, 2, 1, 10, 5, 3}); // NOSONAR
constexpr long refreshInterval = 0;
unsigned long previous = 0; // NOSONAR

void setup() {
  // Nothing to do
}

void loop() {
  buzzer.play();
  const float warmupPercent = breathalyzer.getWarmupPercent();
  if (warmupPercent < 1.0f) {
    display.displayPercent(warmupPercent);
  } else {
    const unsigned long current = millis();
    if (current >= refreshInterval + previous) {
      previous = current;
      const uint16_t alcoholLevel = breathalyzer.getAlcoholLevel();
      display.displayNumber(alcoholLevel);
    }
  }
  display.refresh();
}
