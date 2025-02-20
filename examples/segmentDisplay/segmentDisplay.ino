// Note this will not work with arduino, only esp 
#define COM 40
#define COM2 1
#define COM3 4


// screen
#define SEGMENTS 6
int segmentPins[] = { 2, 6, 8, 10, 13, 14 };
bool segmentValues[] = { false, true, false, true, false, true };
bool comSignal[] = { false, true };



void setPin(uint8_t PIN, uint8_t STATE) {

  if (STATE == 1) {
    // delay(10);
    pinMode(PIN, INPUT_PULLUP);
    // digitalWrite(PIN, HIGH);
    // 5v met 50k weerstand

  } else if (STATE == 0) {
    pinMode(PIN, OUTPUT);
    digitalWrite(PIN, LOW);
    // gnd

  } else if (STATE == 2) {
    pinMode(PIN, OUTPUT);
    digitalWrite(PIN, LOW);
  }
}


void task_SegmentDisplay(void* parameters) {
  while (true) {
    setPin(COM, 1);
    if (comSignal[0]) setPin(COM2, 1);
    else setPin(COM2, 0);
    if (comSignal[1]) setPin(COM3, 1);
    else setPin(COM3, 0);


    for (int i = 0; i < SEGMENTS; i++) {
      if (segmentValues[i]) setPin(segmentPins[i], 0);
    }

    vTaskDelay(10 / portTICK_PERIOD_MS);

    setPin(COM, 0);
    if (comSignal[0]) setPin(COM2, 0);
    else setPin(COM2, 1);
    if (comSignal[1]) setPin(COM3, 0);
    else setPin(COM3, 1);

    for (int i = 0; i < SEGMENTS; i++) {
      if (segmentValues[i]) setPin(segmentPins[i], 1);
    }


    vTaskDelay(10 / portTICK_PERIOD_MS);

    // check if some segments need to be toggled
    for (int i = 0; i < SEGMENTS; i++) {
      int randSegment = int(random(500));

      if (randSegment < 2) {
        segmentValues[i] = !segmentValues[i];

        // send the 'off' signal to the pin to prevent glitching
        if (!segmentValues[i]) setPin(segmentPins[i], 2);
      }

      int randCom = int(random(1500));
      if (randCom < 2) {
        comSignal[i] = !comSignal[i];

        // send the 'off' signal to the pin to prevent glitching
        if (!comSignal[0]) setPin(COM2, 2);
        if (!comSignal[1]) setPin(COM3, 2);
      }
    }
  }
}




void setup() {
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);

  xTaskCreate(
    task_SegmentDisplay,   /* Function that implements the task. */
    "LCD display control", /* Text name for the task. */
    1000,                  /* Stack size in words, not bytes. */
    NULL,                  /* Parameter passed into the task. */
    1,                     /* Priority at which the task is created. */
    NULL);


}

void loop() {}
