//
// Created by Axel on 25/08/2025.
//

#ifndef ALC_HIGH_STRIKER_DISPLAY_H
#define ALC_HIGH_STRIKER_DISPLAY_H
#include <Arduino.h>
#include "ShiftLcd.h"

/**
 * Class representing a 7-segment display.
 */
class Display {
  public:

    /**
     * Constructor.
     *
     * @param lcd_en Pin connected to the LCD Enable (EN) pin.
     * @param lcd_d7 Pin connected to the LCD Data 7 (D7) pin.
     * @param shift_ser Pin connected to the Shift Register Serial (SER) pin.
     * @param shift_srclk Pin connected to the Shift Register Clock (SRCLK) pin.
     */
    Display(
      uint8_t lcd_en,
      uint8_t lcd_d7,
      uint8_t shift_ser,
      uint8_t shift_srclk);
    void displayNumber(uint16_t number);

    /**
     * Displays a percentage. At 0.0, the display is blank, at 1.0 it is full.
     *
     * @param percent Percentage to display. Should be between 0.0 and 1.0.
     */
    void displayPercent(float percent);

    /**
     * Displays an error message.
     */
    void displayError();
    void clear();

  private:
    ShiftLcd lcd;
    bool cleared;
};


#endif //ALC_HIGH_STRIKER_DISPLAY_H
