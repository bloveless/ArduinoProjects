#include "pitches.h"
#define NO_SOUND 0 // make the rests in music

/*
 * Doorbell basic Bell
 * requires prepaired XBee Radios
 */
 
int speakerPin = 16;
int ledPin = 13;

void setup() {
  pinMode(speakerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  Serial1.begin(9600);
}

void loop() {
  // look for a capital D over the serial port and ring the bell if found
  if (Serial1.available() > 0) {
    if(Serial1.read() == 'D') { 
      playTune();
      while(Serial1.read() >= 0); // remove anything else in the serial buffer.
    }
  }
}

// notes in the melody (James Bond intro):
int melody[] = {
   //Introduction
  NOTE_E4,NOTE_F4,NOTE_F4,NOTE_F4,NOTE_F4,NOTE_E4,NOTE_E4,NOTE_E4,
  NOTE_E4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_E4,NOTE_E4,NOTE_E4,
  NOTE_E4,NOTE_F4,NOTE_F4,NOTE_F4,NOTE_F4,NOTE_E4,NOTE_E4,NOTE_E4,
  NOTE_E4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_E4,NOTE_E4,NOTE_E4,
  NOTE_DS5,NOTE_D5,NOTE_B4,NOTE_A4,NOTE_B4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  8,16,16,8,4,8,8,8,
  8,16,16,8,4,8,8,8,
  8,16,16,8,4,8,8,8,
  8,16,16,8,4,8,8,8,
  8,2,8,8,2
};

void playTune() {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 37; thisNote++) {

    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1450 / 4, eighth note = 1450/8, etc.
    int noteDuration = 1450/noteDurations[thisNote];
    tone(speakerPin, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(speakerPin);
  }
}
