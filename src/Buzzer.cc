//
// Created by Axel on 25/08/2025.
//

#include <Buzzer.h>
#include <Arduino.h>
#include <pitches.h>

Buzzer::Buzzer(const int pin, const float tempo)
  : pin(pin), tempo(tempo) {
  previousTime = millis();
  nextNoteTime = millis();
  currentNoteIndex = 0;
  notes = new int[8]{NOTE_C3, NOTE_D3, NOTE_E3, NOTE_F3, NOTE_G3, NOTE_A4, NOTE_B4, NOTE_C4};
}

void Buzzer::play() {
  const long current = millis();
  if (current >= nextNoteTime) {
    const long duration = getNoteDuration(0.5);
    playNote(notes[currentNoteIndex], duration);
    currentNoteIndex = (currentNoteIndex + 1) % 8;
    nextNoteTime = current + duration;
  }
}

void Buzzer::stop() {
  // Logique pour arrêter le buzzer
}

void Buzzer::playNote(const int note, const float duration) {
  tone(pin, note, duration);
}

float Buzzer::getNoteDuration(const float rhythm) const {
  return (60000.0 / tempo) * rhythm;
}
