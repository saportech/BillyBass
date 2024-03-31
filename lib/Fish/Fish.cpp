#include <Arduino.h>
#include "Fish.h"

Fish::Fish(int fishType) : type(fishType) {
    switch (type) {
        case 1:
            tailHeadPin1 = 5;
            tailHeadPin2 = 18;
            mouthPin1 = 19;
            mouthPin2 = 4;
            txPin = 21;
            break;
        case 2:
            tailHeadPin1 = 26;
            tailHeadPin2 = 25;
            mouthPin1 = 33;
            mouthPin2 = 32;
            txPin = 22;
            break;
        case 3:
            tailHeadPin1 = 13;
            tailHeadPin2 = 12;
            mouthPin1 = 14;
            mouthPin2 = 27;
            txPin = 23;
            break;
        default:
            Serial.println("Invalid fish type!");
            break;
    }

    int PWMPin = 2;
    ledcSetup(0, 20000, 8);
    ledcAttachPin(PWMPin, 0);
    ledcWrite(0, 100);

    intervalFlap = 300;
    intervalSing = 300;
    previousMillisFlap = 0;
    previousMillisSing = 0;
    isFlapping = false;
    isSinging = false;
    state = 0;
    previousMillisSM = 0;

}

void Fish::Test() {

    static bool turnedHead = false;
    static unsigned long previousMillis = millis();

    sing();

    if (millis() - previousMillis > 5000 && !turnedHead) {
        turnHead();
        turnedHead = true;
    }
    
}

void Fish::songStateMachine() {
  
  #define TIME 3000

  enum BILLY_BASS_STATE_TYPE { START,
                    TAIL,  
                    HEAD_FRONT_AND_SING, 
                    HEAD_BACK_AND_SING,
                    FINISH
                  };
  switch ( state )
    {
      case START:
        Serial.println("START" + String(txPin));
        dfPlayerSetup(txPin);
        playSound(1);
        previousMillisSM = millis();
        state++;
        break;
      case TAIL:
        if (millis() - previousMillisSM > TIME) {
          previousMillisSM = millis();
          state++;
          Serial.println("HEAD_FRONT_AND_SING" + String(tailHeadPin1));
          turnHead();
          break;
        }
        flapTail();
        break;
      case HEAD_FRONT_AND_SING:
        if (millis() - previousMillisSM > TIME) {
          previousMillisSM = millis();
          state++;
          Serial.println("HEAD_BACK_AND_SING" + String(tailHeadPin1));
          stopAll();
          break;
        }
        sing();
        break;
      case HEAD_BACK_AND_SING:
        if (millis() - previousMillisSM > TIME) {
          previousMillisSM = millis();
          state++;
          Serial.println("FINISH" + String(tailHeadPin1));
          stopAll();
          break;
        }
        sing();
        break;
      case FINISH:
        if (millis() - previousMillisSM > TIME) {
          stopAll();
          state = 0;
          previousMillisSM = millis();
        }
        break;
    }
}

void Fish::flapTail() {

    if (millis() - previousMillisFlap >= intervalFlap) {
        previousMillisFlap = millis();
        isFlapping = !isFlapping;

        if (isFlapping) {
            digitalWrite(tailHeadPin1, HIGH);
            digitalWrite(tailHeadPin2, LOW);
            intervalFlap = 300;
        } else {
            digitalWrite(tailHeadPin1, LOW);
            digitalWrite(tailHeadPin2, LOW);
            intervalFlap = 150;
        }
    }
}

void Fish::sing() {
    const int MOUTH_TIME = 300;
    
    if (millis() - previousMillisSing >= intervalSing) {
        previousMillisSing = millis();
        isSinging = !isSinging;

        if (isSinging) {
            digitalWrite(mouthPin1, HIGH);
            digitalWrite(mouthPin2, LOW);
            intervalSing = MOUTH_TIME;
        } else {
            digitalWrite(mouthPin1, LOW);
            digitalWrite(mouthPin2, LOW);
            intervalSing = MOUTH_TIME / 2;
        }
    }
}

void Fish::turnHead() {
    digitalWrite(tailHeadPin1, LOW);
    digitalWrite(tailHeadPin2, HIGH);
}

void Fish::stopTailHead() {
    digitalWrite(tailHeadPin1, LOW);
    digitalWrite(tailHeadPin2, LOW);
}

void Fish::stopMouth() {
    digitalWrite(mouthPin1, LOW);
    digitalWrite(mouthPin2, LOW);
}

void Fish::stopAll() {
    digitalWrite(tailHeadPin1, LOW);
    digitalWrite(tailHeadPin2, LOW);
    digitalWrite(mouthPin1, LOW);
    digitalWrite(mouthPin2, LOW);
}

void Fish::setupPins() {
    pinMode(tailHeadPin1, OUTPUT);
    pinMode(tailHeadPin2, OUTPUT);
    pinMode(mouthPin1, OUTPUT);
    pinMode(mouthPin2, OUTPUT);

    stopAll();
}
