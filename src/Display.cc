//
// Created by Axel on 25/08/2025.
//

#include "Display.h"
#include "SevSeg.h"

Display::Display(const uint8_t lcd_en,
                 const uint8_t lcd_d7,
                 const uint8_t shift_ser,
                 const uint8_t shift_srclk)
                   : lcd(ShiftLcd(lcd_en, lcd_d7, shift_ser, shift_srclk)), cleared(false) {
  lcd.begin();
}

void Display::displayNumber(const uint16_t number) {
  String zerosToAdd = "";
  if (number < 10) {
    zerosToAdd = "000";
  } else if (number < 100) {
    zerosToAdd = "00";
  } else if (number < 1000) {
    zerosToAdd = "0";
  }
  lcd.write(zerosToAdd + static_cast<String>(number));
}

void Display::displayPercent(const float percent) {
  lcd.writePercent(percent);
}

void Display::displayError() {
  lcd.write("ERROR!");
}

void Display::clear() {
  if (!cleared) {
    lcd.clear();
    cleared = true;
  }
}
