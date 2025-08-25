//
// Created by Axel on 25/08/2025.
//

#ifndef ALC_HIGH_STRIKER_BREATHALYZER_H
#define ALC_HIGH_STRIKER_BREATHALYZER_H


/**
 * Class representing a breathalyzer using an MQ3 sensor.
 */
class Breathalyzer {
  public:
    /**
     * Full constructor.
     *
     * @param analogPin pin connected to the analog output of the MQ3 sensor
     * @param thresholdPin pin connected to the digital output of the MQ3 sensor
     */
    Breathalyzer(int analogPin, int thresholdPin);

    /**
     * Constructor without threshold pin.
     *
     * @param analogPin pin connected to the analog output of the MQ3 sensor
     */
    explicit Breathalyzer(int analogPin);

    /**
     * The sensor requires a warm-up time of approximately 20 seconds after being powered on.
     * This method returns the percentage of the warm-up time that has elapsed.
     *
     * @return true if the sensor is ready, false otherwise
     */
    float getWarmupPercent();

    /**
     * Reads the alcohol level from the sensor.
     * Should only be called when the sensor is ready (after warm-up).
     *
     * @return alcohol level as an integer value, or -1 if the sensor is not ready
     */
    int getAlcoholLevel();

  private:
    int analogPin;
    int thresholdPin;
    bool ready;
    unsigned long startTime;
    int value;
    unsigned long valueChangeTime;

    void refreshValue();
};


#endif //ALC_HIGH_STRIKER_BREATHALYZER_H
