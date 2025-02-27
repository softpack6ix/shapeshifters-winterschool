#include "MIDIUSB.h"




void setup() {
  Serial.begin(115200);
}


void loop() {
  // Serial.println("Sending note on");
  // sendNoteOn(0, 48, 64);  // Channel 0, middle C, normal velocity
  // MidiUSB.flush();
  // delay(1000);
  // Serial.println("Sending note off");
  // sendNoteOff(0, 48, 64);  // Channel 0, middle C, normal velocity
  // MidiUSB.flush();
  // delay(1000);

  Serial.println("Sending control change");
  sendControlChange(0, 10, 65);  // Set the value of controller 10 on channel 0 to 65
  MidiUSB.flush();
  delay(1000);
}


