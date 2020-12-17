/*
    Arduino Jingle Bells
    Copyright (C) 2020 giovanni.organtini@uniroma1.it

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
int speaker = 8; // the pin to which the loudspeaker is attached
int tempo = 200; // the duration of a note

// the melody is defined below
char notes[] = "eee eee egcde   fffffeeeedded g eee eee egcde   fffffeeeggfdc  GGedcG  GGedca  aafedb  Gggfde   GGedcG  GGedca  aafedggggAgfdc   ";

int toPlay[255] = {0};

void setup() {
  // set the speaker pin as an output pin
  Serial.begin(9600);
  pinMode(speaker, OUTPUT);
  // then fill the array toPlay with the frequencies corresponding 
  // to notes (the correspondance is not fully consistent, but...)
  char notesName[] = { 'G', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'A'};
  int tones[] = { 196, 220, 247, 262, 294, 330, 349, 392, 440};

  for (int i = 0; i < sizeof(notes) - 1; i++) {
    for (int j = 0; j <= sizeof(notesName); j++) {
      if (notes[i] == notesName[j]) {
        toPlay[i] = tones[j];
      } else if (notes[i] == ' ') {
        toPlay[i] = 0;
      }
    }
  }
}

void loop() {
  // play the melody
  for (int i = 0; i < sizeof(notes) - 1; i++) {
    if (toPlay[i] != 0) {
      // if we have to play a tone, print its frequency and two
      // integers (one lower than the lowest frequency and one
      // larger) such that, using the serial plotter, the melody 
      // will show as a plot
      for (int k = 0 ; k < 5; k++) {
        Serial.print("190 445 ");
        Serial.println(toPlay[i]);
      }
    }
    tone(speaker, toPlay[i], tempo);
    delay(tempo);
  }
  delay(500);
}
