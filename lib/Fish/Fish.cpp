#include <Arduino.h>
#include "Fish.h"

std::queue<Action> actionQueue;

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
    isFirstPerformCall = true;

}

void Fish::performAction(unsigned long duration, int action) {
  Action newAction = {duration, action};
  actionQueue.push(newAction);
}

void Fish::perform(int songNumber) {
    if (isFirstPerformCall) {
        Serial.println("Performing song " + String(songNumber) + " on fish type " + String(type));
        dfPlayerSetup(txPin);
        playSound(songNumber);
        
        switch (type) {
            case 1://Fish number 1
                switch (songNumber) {
                    case 1://Song 1
                        
                        break;
                    case 2://Song 2
                        performAction(1, OPEN_MOUTH);//Ignored
                        performAction(1, TURN_HEAD);
                        performAction(1000, OPEN_MOUTH);
                        performAction(100, CLOSE_MOUTH);
                        performAction(1000, OPEN_MOUTH);
                        performAction(100, CLOSE_MOUTH);
                        performAction(400, OPEN_MOUTH);
                        performAction(100, CLOSE_MOUTH);
                        performAction(400, OPEN_MOUTH);
                        performAction(100, CLOSE_MOUTH);
                        performAction(1000, OPEN_MOUTH);
                        performAction(1000, CLOSE_MOUTH);
                        performAction(1000, RETURN_HEAD_TAIL);
                        break;
                    case 3://Song 3

                        break;
                    default:
                        break;
                }
                break;
            case 2://Fish number 2
                switch (songNumber) {
                    case 1://Song 1
                        performAction(1, OPEN_MOUTH);//Ignored
                        performAction(1, TURN_HEAD);
                        performAction(1000, OPEN_MOUTH);
                        performAction(100, CLOSE_MOUTH);
                        performAction(1000, OPEN_MOUTH);
                        performAction(100, CLOSE_MOUTH);
                        performAction(400, OPEN_MOUTH);
                        performAction(100, CLOSE_MOUTH);
                        performAction(1000, TAIL);
                        performAction(100, RETURN_HEAD_TAIL);
                        performAction(1000, TAIL);
                        performAction(100, RETURN_HEAD_TAIL);
                        performAction(1000, TAIL);
                        performAction(100, RETURN_HEAD_TAIL);
                        
                        break;
                    case 2://Song 2

                        break;
                    case 3://Song 3

                        break;
                    default:
                        break;
                }
                break;
            case 3://Fish number 3
                switch (songNumber) {
                    case 1://Song 1

                        break;
                    case 2://Song 2

                        break;
                    case 3://Song 3

                        break;
                    default:
                        break;
                }
                break;
            default:
                Serial.println("Invalid fish type!");
                break;
        }
        isFirstPerformCall = false;
    } else {
        updateAction();
    }
}

void Fish::updateAction() {
  if (!actionQueue.empty()) {
    Action currentAction = actionQueue.front();
    
    if (millis() - previousMillisSM >= currentAction.duration) {

      actionQueue.pop();
      
      if (!actionQueue.empty()) {
        Action nextAction = actionQueue.front();
        previousMillisSM = millis();
        
        switch(nextAction.action) {
          case OPEN_MOUTH:
            //Serial.println("Opening mouth");
            digitalWrite(mouthPin1, HIGH);
            digitalWrite(mouthPin2, LOW);
            break;
          case CLOSE_MOUTH:
            //Serial.println("Closing mouth");
            digitalWrite(mouthPin1, LOW);
            digitalWrite(mouthPin2, LOW);
            break;
          case TURN_HEAD:
            //Serial.println("Turning head");
            turnHead();
            break;
          case RETURN_HEAD_TAIL:
            //Serial.println("Returning head");
            stopTailHead();
            break;
          case TAIL:
            //Serial.println("Flapping tail");
            turnTail();
            break;
          default:
            Serial.println("Invalid action");
            break;
        }
      }
    }
  }
}

void Fish::songStateMachine(int songNumber) {
  
  #define TIME 3000

  enum BILLY_BASS_STATE_TYPE { START,
                    SECTION1,  
                    SECTION2,
                    SECTION3,
                    FINISH
                  };
  switch ( state )
    {
      case START:
        Serial.println("START" + String(txPin));
        dfPlayerSetup(txPin);
        playSound(songNumber);
        previousMillisSM = millis();
        turnHead();
        state++;
        break;
      case SECTION1:
        if (millis() - previousMillisSM > 8540) {
          previousMillisSM = millis();
          state++;
          Serial.println("SECTION2" + String(tailHeadPin1));
          stopAll();
          break;
        }
        sing();
        break;
      case SECTION2:
        if (millis() - previousMillisSM > 8130) {
          previousMillisSM = millis();
          state++;
          Serial.println("SECTION3" + String(tailHeadPin1));
          turnHead();
          break;
        }
        sing();
        break;
      case SECTION3:
        if (millis() - previousMillisSM > 8400) {
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
    const int MOUTH_TIME = 1000;
    
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
            intervalSing = MOUTH_TIME;
        }
    }
}

void Fish::turnHead() {
    digitalWrite(tailHeadPin1, LOW);
    digitalWrite(tailHeadPin2, HIGH);
}

void Fish::turnTail() {
    digitalWrite(tailHeadPin1, HIGH);
    digitalWrite(tailHeadPin2, LOW);
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
