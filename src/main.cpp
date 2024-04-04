#include <Arduino.h>
#include "Fish.h"
#include "dfplayer.h"
#include "communication.h"
#include "globals.h"

void runFishes(int songNumber);
void buttonPressed();

int currentSong = 1;
bool buttonPressedBool = false;

Fish fish1(1);
Fish fish2(2);
Fish fish3(3);

Communication comm;

void setup() {

  Serial.begin(115200);
  Serial.println("Billy Bass");

  Serial.flush();

  fish1.setupPins();
  fish2.setupPins();
  fish3.setupPins();

  dfPlayerSetup(21);
  delay(300);
  dfPlayerSetup(22);
  delay(300);
  dfPlayerSetup(23);
  delay(300);


  //comm.init();

}

void loop() {

  fish2.perform(1);

}

void runFishes(int songNumber) {

  switch(songNumber) {
    case 1:
      fish1.perform(songNumber);
      fish2.perform(songNumber);
      fish3.perform(songNumber);
      break;
    case 2:
      fish1.perform(songNumber);
      fish2.perform(songNumber);
      fish3.perform(songNumber);
      break;
    case 3:
      fish1.perform(songNumber);
      fish2.perform(songNumber);
      fish3.perform(songNumber);
      break;
    default:
      Serial.println("Error in runFishes()");
      break;
  }

}


