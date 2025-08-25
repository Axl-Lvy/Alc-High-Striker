//
// Created by Axel on 25/08/2025.
//

#ifndef ALC_HIGH_STRIKER_BUZZER_H
#define ALC_HIGH_STRIKER_BUZZER_H

class Buzzer {
  public:
    Buzzer(uint8_t pin, float tempo);
    ~Buzzer();
    void play();

  private:
    void playNote(uint16_t note, unsigned long duration) const;
    long getNoteDuration(float rhythm) const;
    uint8_t pin;
    float tempo;
    unsigned long previousTime;
    unsigned long nextNoteTime;
    uint8_t currentNoteIndex;
    uint16_t* notes;
};


#endif //ALC_HIGH_STRIKER_BUZZER_H