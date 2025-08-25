#include <Arduino.h>

#include "Buzzer.h"
#include "SevSeg.h"

#define MQ3pin 0

SevSeg sevseg; //Instantiate a seven segment object
Buzzer buzzer(13, 120.0); // Buzzer on pin 5 with tempo 120 BPM
constexpr long interval = 1000;
unsigned long previous = 0;

void displayNumber(const float n) {
  char decimalPrecision;
  if (n >= 1000) {
    decimalPrecision = 0;
  } else if (n >= 100) {
    decimalPrecision = 1;
  } else if (n >= 10) {
    decimalPrecision = 2;
  } else {
    decimalPrecision = 3;
  }
  sevseg.setNumberF(n, decimalPrecision);
}

void setup() {
  constexpr byte numDigits = 4;
  constexpr byte digitPins[] = {12, 9, 8, 6};
  const byte segmentPins[] = {11, 7, 4, 2, 1, 10, 5, 3};
  constexpr bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  constexpr byte hardwareConfig = COMMON_ANODE; // See README.md for options
  constexpr bool updateWithDelays = false; // Default 'false' is Recommended
  constexpr bool leadingZeros = true; // Use 'true' if you'd like to keep the leading zeros

  // Use 'true' if your decimal point doesn't exist or isn't connected. Then, you only need to specify 7 segmentPins[]
  constexpr bool disableDecPoint = false;

  sevseg.begin(hardwareConfig,
               numDigits,
               digitPins,
               segmentPins,
               resistorsOnSegments,
               updateWithDelays,
               leadingZeros,
               disableDecPoint);
}

void loop() {
  buzzer.play();
  const unsigned long current = millis();
  sevseg.refreshDisplay();
  if (current - previous > interval) {
    const float sensorValue = analogRead(MQ3pin);
    previous = current;
    displayNumber(sensorValue);
  }
}
