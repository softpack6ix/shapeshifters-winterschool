

// JOYSTICK -------------------
#define JOYSTICK_X A0 // A2
#define JOYSTICK_Y A1 // A3
#define JOYSTICK_PRESS 10

int joystickX, joystickY;
bool joystickPressed;

void setup() {
  Serial.begin(9600);
}


void loop() {
  readJoystick();
}


void readJoystick() {
  joystickX = analogRead(JOYSTICK_X);
  joystickY = analogRead(JOYSTICK_Y);

  Serial.print("X: ");
  Serial.print(joystickX);
  Serial.print(", Y: ");
  Serial.print(joystickY);

  if (joystickPressed) Serial.print(", PRESSED");
  Serial.println(" ");
}