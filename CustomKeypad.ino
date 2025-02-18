/* @file CustomKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates changing the keypad size and key values.
|| #
*/
#include <Keypad.h>

const byte ROWS = 4;  //four rows
const byte COLS = 4;  //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  { '0', '1', '2', '3' },
  { '4', '5', '6', '7' },
  { '8', '9', 'A', 'B' },
  { 'C', 'D', 'E', 'F' },
};

#define LED_PIN 11

byte rowPins[ROWS] = { 2, 3, 4, 5 };  //connect to the row pinouts of the keypad
byte colPins[COLS] = { 6, 7, 8, 9 };  //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

int brightness = 0;
bool up = true;

void loop() {
  char customKey = customKeypad.getKey();

  if (customKey) {
    Serial.println(customKey);
  }

  analogWrite(LED_PIN, brightness);

  if (random(500) > 2) return;

  if (up) brightness += 2;
  else brightness -= 2;

  if (brightness > 254) up = false;
  if (brightness < 1) up = true;

  // delay(250);
  // i += 1;
}
