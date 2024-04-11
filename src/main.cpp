#include <Arduino.h>
#include "Fish.h"
#include "dfplayer.h"
#include "communication.h"
#include "globals.h"

void runFishes(int songNumber);
void runFishesSong1(int songNumber, unsigned long startTimeFish2, unsigned long startTimeFish3);
void runFishesSong2(int songNumber, unsigned long startTimeFish2, unsigned long startTimeFish3);
void runFishesSong3(int songNumber, unsigned long startTimeFish2, unsigned long startTimeFish3);
void resetingAndPlayingNextSong();
void buttonPressed();

bool fishesPlaying = false;

int currentSong = 0;
bool buttonPressedBool = false;
int stateSong1 = 0;
int stateSong2 = 0;
int stateSong3 = 0;

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

  comm.init();

}

void loop() {
  
  if (comm.checkSignalReceived()) {
    comm.setSignalReceived(false);
    if (!fish1.isFishPlaying() && !fish2.isFishPlaying() && !fish3.isFishPlaying()) {
      resetingAndPlayingNextSong();
    }
  }

  if (fishesPlaying) {
    runFishes(currentSong);
  }

}

void resetingAndPlayingNextSong() {
  Serial.println("Fish playing set to true");
  fishesPlaying = true;
  fish1.setFishPlaying(true);
  fish2.setFishPlaying(true);
  fish3.setFishPlaying(true);
  stateSong1 = 0;
  stateSong2 = 0;
  stateSong3 = 0;
  currentSong = currentSong + 1;
  if (currentSong > 3) {
    currentSong = 1;
  }
  Serial.println("Current song: " + String(currentSong));
}

void runFishes(int songNumber) {

  switch(songNumber) {
    case 1:
      runFishesSong1(songNumber, 8110, 7870);
      break;
    case 2:
      runFishesSong2(songNumber, 8630, 8010);
      break;
    case 3:
      runFishesSong3(songNumber, 6750, 5670);
      break;
    default:
      Serial.println("Error in runFishes()");
      break;
  }

}

void runFishesSong1(int songNumber, unsigned long startTimeFish2, unsigned long startTimeFish3) {
static unsigned long previousTime = millis();

  enum BILLY_BASS_SONG_STATE_TYPE { START,
                FISH1,
                FISH2,  
                FISH3
              };
  switch ( stateSong1 )
    {
      case START:
        Serial.println("FISH1");
        previousTime = millis();
        stateSong1++;
        break;
      case FISH1:
        if (millis() - previousTime > startTimeFish2) {
          Serial.println("FISH2");
          previousTime = millis();
          stateSong1++;
          break;
        }
        fish1.perform(songNumber);
        break;
      case FISH2:
        if (millis() - previousTime > startTimeFish3) {
          Serial.println("FISH3");
          previousTime = millis();
          stateSong1++;
          break;
        }
        fish1.perform(songNumber);
        fish2.perform(songNumber);
        break;
      case FISH3:
        fish1.perform(songNumber);
        fish2.perform(songNumber);
        fish3.perform(songNumber);
        break;
    }
}

void runFishesSong2(int songNumber, unsigned long startTimeFish2, unsigned long startTimeFish3) {
static unsigned long previousTime = millis();

  enum BILLY_BASS_SONG_STATE_TYPE { START,
                FISH1,
                FISH2,  
                FISH3
              };
  switch ( stateSong2 )
    {
      case START:
        Serial.println("FISH1");
        previousTime = millis();
        stateSong2++;
        break;
      case FISH1:
        if (millis() - previousTime > startTimeFish2) {
          Serial.println("FISH2");
          previousTime = millis();
          stateSong2++;
          break;
        }
        fish2.perform(songNumber);
        break;
      case FISH2:
        if (millis() - previousTime > startTimeFish3) {
          Serial.println("FISH3");
          previousTime = millis();
          stateSong2++;
          break;
        }
        fish2.perform(songNumber);
        fish3.perform(songNumber);
        break;
      case FISH3:
        fish1.perform(songNumber);
        fish2.perform(songNumber);
        fish3.perform(songNumber);
        break;
    }
}

void runFishesSong3(int songNumber, unsigned long startTimeFish2, unsigned long startTimeFish3) {
static unsigned long previousTime = millis();

  enum BILLY_BASS_SONG_STATE_TYPE { START,
                FISH1,
                FISH2,  
                FISH3
              };
  switch ( stateSong3 )
    {
      case START:
        Serial.println("FISH1");
        previousTime = millis();
        stateSong3++;
        break;
      case FISH1:
        if (millis() - previousTime > startTimeFish2) {
          Serial.println("FISH2");
          previousTime = millis();
          stateSong3++;
          break;
        }
        fish3.perform(songNumber);
        break;
      case FISH2:
        if (millis() - previousTime > startTimeFish3) {
          Serial.println("FISH3");
          previousTime = millis();
          stateSong3++;
          break;
        }
        fish3.perform(songNumber);
        fish2.perform(songNumber);
        break;
      case FISH3:
        fish1.perform(songNumber);
        fish2.perform(songNumber);
        fish3.perform(songNumber);
        break;
    }
}


