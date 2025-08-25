//
// Created by Axel on 25/08/2025.
//

#include "Display.h"
#include "SevSeg.h"

Display::Display(
  const byte digitPins[],
  const byte segmentPins[]) {
  sevseg.begin(COMMON_ANODE,
               4,
               digitPins,
               segmentPins,
               false,
               false,
               false,
               false);
}

void Display::displayNumber(const float number) {
  char decimalPrecision;
  if (number >= 1000) {
    decimalPrecision = 0;
  } else if (number >= 100) {
    decimalPrecision = 1;
  } else if (number >= 10) {
    decimalPrecision = 2;
  } else {
    decimalPrecision = 3;
  }
  sevseg.setNumberF(number, decimalPrecision);
}

void Display::displayNumber(const int number) {
  if (number < 0 || number > 9999) {
    displayError();
    return;
  }
  sevseg.setNumber(number);
}

void Display::displayPercent(const float percent) {
  if (percent > 1.0f || percent < 0.0f) {
    displayError();
    return;
  }

  constexpr int totalSegments = 28;
  const int segmentsToLight = round(percent * totalSegments);

  uint8_t segmentCodes[4] = {0, 0, 0, 0};

  const int fullDigits = segmentsToLight / 7;

  for (int i = 0; i < fullDigits && i < 4; i++) {
    segmentCodes[3 - i] = 0x7F;
  }

  const int remainingSegments = segmentsToLight % 7;
  if (remainingSegments > 0 && fullDigits < 4) {
    const uint8_t segmentMasks[] = {
      0b00000001,  // A (top)
      0b00000011,  // A + B (top right)
      0b00000111,  // A + B + C (bottom right)
      0b00001111,  // A + B + C + D (bottom)
      0b00011111,  // A + B + C + D + E (bottom left)
      0b00111111,  // A + B + C + D + E + F (top left)
      0b01111111,  // A + B + C + D + E + F + G (mid)
    };
    segmentCodes[3 - fullDigits] = segmentMasks[remainingSegments - 1];
  }

  sevseg.setSegments(segmentCodes);
}

void Display::displayError() {
  sevseg.setChars(" ERR");
}

void Display::refresh() {
  sevseg.refreshDisplay();
}
