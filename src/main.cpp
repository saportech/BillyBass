#include <Arduino.h>
#include "Fish.h"
#include "dfplayer.h"

Fish fish1(1);
Fish fish2(2);
Fish fish3(3);

void setup() {

  Serial.begin(115200);
  Serial.println("Billy Bass");
  delay(3000);
  fish1.setupPins();
  fish2.setupPins();
  fish3.setupPins();

  //dfPlayerSetup(21);

}

void loop() {
static unsigned long currentMillis = millis();

  fish1.songStateMachine();

  if (millis() - currentMillis > 5000) {
    fish2.songStateMachine();
  }

  if (millis() - currentMillis > 10000) {
    fish3.songStateMachine();
  }

}


