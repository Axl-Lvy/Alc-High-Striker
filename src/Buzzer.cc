//
// Created by Axel on 25/08/2025.
//

#include <Arduino.h>

#include "Buzzer.h"
#include "pitches.h"

Buzzer::Buzzer(const uint8_t pin, const float tempo)
  : pin(pin), tempo(tempo),
    notes(new uint16_t[8]{NOTE_C3, NOTE_D3, NOTE_E3, NOTE_F3, NOTE_G3, NOTE_A4, NOTE_B4, NOTE_C4}) {
  previousTime = millis();
  nextNoteTime = millis();
  currentNoteIndex = 0;
}

Buzzer::~Buzzer() {
  delete[] notes;
}

void Buzzer::play() {
  const unsigned long current = millis();
  if (current >= nextNoteTime) {
    const unsigned long duration = getNoteDuration(0.5);
    playNote(notes[currentNoteIndex], duration);
    currentNoteIndex = (currentNoteIndex + 1) % 8;
    nextNoteTime = current + duration;
  }
}

void Buzzer::playNote(const uint16_t note, const unsigned long duration) const {
  tone(pin, note, duration);
}

long Buzzer::getNoteDuration(const float rhythm) const {
  return static_cast<long>((60000.0 / tempo) * rhythm);
}
