#include <Arduino.h>
#include "Fish.h"
#include "dfplayer.h"
#include "communication.h"

void runFishes(int songNumber);
int currentSong = 1;

Fish fish1(1);
Fish fish2(2);
Fish fish3(3);

Communication comm;

void setup() {

  Serial.begin(115200);
  Serial.println("Billy Bass");
  delay(1000);

  fish1.setupPins();
  fish2.setupPins();
  fish3.setupPins();

  comm.init();

}

void loop() {

  if (comm.checkSignalReceived()) {
    Serial.println("Signal received");
    comm.setSignalReceived(false);
  }

}

void runFishes(int songNumber) {
static unsigned long currentMillis = millis();

  fish1.songStateMachine(songNumber);

  if (millis() - currentMillis > 5000) {
    fish2.songStateMachine(songNumber);
  }

  if (millis() - currentMillis > 10000) {
    fish3.songStateMachine(songNumber);
  }

}


