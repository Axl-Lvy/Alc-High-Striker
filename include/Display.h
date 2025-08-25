//
// Created by Axel on 25/08/2025.
//

#ifndef ALC_HIGH_STRIKER_DISPLAY_H
#define ALC_HIGH_STRIKER_DISPLAY_H
#include <Arduino.h>
#include "SevSeg.h"

/**
 * Class representing a 7-segment display.
 */
class Display {
  public:
    /**
     *  Constructor.
     *
     * @param digitPins Digit pins that control which digit is selected
     * @param segmentPins Segment pins that control which segments are lit
     */
    Display(
      const byte digitPins[],
      const byte segmentPins[]);
    /**
     * Displays a number.
     *
     * @param number Number to display. Should be between 0 and 9999.
     */
    void displayNumber(float number);
    void displayNumber(int number);

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

    /**
     * Refreshes the display. Should be called frequently in the main loop.
     * This simply delegates to the SevSeg library's refreshDisplay method.
     */
    void refresh();

  private:
    SevSeg sevseg;
};


#endif //ALC_HIGH_STRIKER_DISPLAY_H
