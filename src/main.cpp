#include <Arduino.h>
#include "movements.h"

void songStateMachine();

const int MOTOR_RUN_TIME = 3000;

void setup() {

  Serial.begin(115200);
  Serial.println("Billy Bass");
  delay(1000);

  pinsSetup();


}

void loop() {

  songStateMachine();

}

void songStateMachine() {
  static int state = 0;
  static unsigned int lastMillis = 0;
  #define TIME 3000

  enum BILLY_BASS_STATE_TYPE { TAIL,  
                    HEAD_FRONT_AND_SING, 
                    HEAD_BACK_AND_SING,
                    FINISH
                  };
  switch ( state )
    {
      case TAIL:
        if (millis() - lastMillis > TIME) {
          lastMillis = millis();
          state++;
          Serial.println("HEAD_FRONT_AND_SING");
          break;
        }
        flapTail();
        break;
      case HEAD_FRONT_AND_SING:
        if (millis() - lastMillis > 5000) {
          lastMillis = millis();
          state++;
          Serial.println("HEAD_BACK_AND_SING");
          stopAll();
          break;
        }
        turnHead();
        sing();
        break;
      case HEAD_BACK_AND_SING:
        if (millis() - lastMillis > TIME) {
          lastMillis = millis();
          state++;
          Serial.println("FINISH");
          stopAll();
          break;
        }
        sing();
        break;
      case FINISH:
        if (millis() - lastMillis > 1000) {
          stopAll();
          state = 0;
          lastMillis = millis();
        }
        break;
    }
}


