int ledPin = 13;      // select the pin for the LED
const int buttonPin = 2;  // the number of the pushbutton pin
int buttonState = 0;  // variable for reading the pushbutton status


void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); //  <--- mind that you are setting INPUT_PULLUP not INPUT

  Serial.begin(9600);
  
}

void loop() {

  buttonState = digitalRead(buttonPin);

// if button is pressed
  if (buttonState == LOW) {

    Serial.println("HIGH");
    digitalWrite(ledPin, HIGH);
  } 
  // if button is not pressed
  else {
    Serial.println("LOW");
    digitalWrite(ledPin, LOW);
  }

  delay(100);
 
}
