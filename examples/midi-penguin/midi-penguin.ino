#include <MIDIUSB.h>  // Include MIDIUSB library

// Define inputs
const int pot1 = A0;
const int pot2 = A3;
const int button1 = 5;
const int button2 = 8;

// Store last button states
int lastButton1State = HIGH;  // Binary: 0 or 1   --- HIGH or LOW
int lastButton2State = HIGH;

// Store last potentiometer values to avoid redundant messages
int lastPot1Value = -1;    // "analog value" : 0 - 127  (2^8)
int lastPot2Value = -1;

void setup() {
  pinMode(button1, INPUT_PULLUP); // Enable internal pull-up resistor
  pinMode(button2, INPUT);
  Serial.begin(9600);
  Serial.print("hello");
}

void loop() {
  // Read potentiometers
  int pot1Value = analogRead(pot1) / 8; // Convert 0-1023 to 0-127
  int pot2Value = analogRead(pot2) / 8;

  // Send MIDI CC if values changed
  if (pot1Value != lastPot1Value) {
    controlChange(0, 10, pot1Value); // Channel 0, CC 10 (Pan)
    lastPot1Value = pot1Value;
  }

  if (pot2Value != lastPot2Value) {
    controlChange(0, 11, pot2Value); // Channel 0, CC 11 (Expression)
    lastPot2Value = pot2Value;
  }

  // Read buttons
  int button1State = digitalRead(button1);
  int button2State = digitalRead(button2);

  // Send Note On/Off when buttons change state
  if (button1State == LOW && lastButton1State == HIGH) {
    noteOn(0, 60, 127); // Button 1: MIDI Note C4 (60)
    Serial.print("btn1");

  } 
  else if (button1State == HIGH && lastButton1State == LOW) {
    noteOff(0, 60, 0);
  }

  if (button2State == LOW && lastButton2State == HIGH) {

    noteOn(0, 62, 127); // Button 2: MIDI Note D4 (62)
    Serial.print("ON");
  } 
  else if (button2State == HIGH && lastButton2State == LOW) {
    noteOff(0, 62, 0);
    Serial.print("OFF");

  }

  // Update last states
  lastButton1State = button1State;
  lastButton2State = button2State;

  // Send MIDI messages
  MidiUSB.flush();

  delay(10); // Small delay to prevent message flooding
}

// MIDI Note On
void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOnPacket = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOnPacket);
 
}

// MIDI Note Off
void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOffPacket = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOffPacket);
}

// MIDI Control Change (CC)
void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t ccPacket = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(ccPacket);
}
