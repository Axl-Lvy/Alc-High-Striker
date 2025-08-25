//
// Created by Axel on 25/08/2025.
//

#ifndef ALC_HIGH_STRIKER_BUZZER_H
#define ALC_HIGH_STRIKER_BUZZER_H

class Buzzer {
  public:
    Buzzer(int pin, float tempo);
    void play();
    void stop();

  private:
    void playNote(int note, float duration) const;
    float getNoteDuration(float rhythm) const;
    int pin;
    float tempo;
    float previousTime;
    float nextNoteTime;
    int currentNoteIndex;
    int* notes;
};


#endif //ALC_HIGH_STRIKER_BUZZER_H