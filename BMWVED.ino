/*
BMW VED control
*/

#include <Servo.h> 

#include "MsTimer2.h"
#include "pitches.h"


int bytes_available = 0;
char data[64];

int led = 13;

void setup() {
  // initialize serial:
  Serial.begin(9600, SERIAL_8N1);
  play_music();
  // initialize the digital pin as an output.
  MsTimer2::set(500, blink);
  MsTimer2::start();
}

void loop() {
  bytes_available = Serial.available();
  if (bytes_available > 0) {
    Serial.readBytes(data, bytes_available);
    Serial.write((byte*)data, bytes_available);
  }

}

void blink() {
  static boolean output = HIGH;
  digitalWrite(led, output);
  output = !output;
}

int melody[] = { NOTE_B4, NOTE_A4,NOTE_C4, NOTE_D4, NOTE_G4, NOTE_F4, NOTE_A3, NOTE_B3, NOTE_F4, NOTE_E4, NOTE_G3, NOTE_B3, NOTE_E4};
int noteDurations[] = {8, 8, 4, 4, 8, 8, 4, 4, 8, 8, 4, 4, 4 };

void play_music() {
  for (int thisNote = 0; thisNote < sizeof(melody)/sizeof(int); thisNote++) {
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/noteDurations[thisNote];
    tone(8, melody[thisNote],noteDuration);
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}






