#include <Arduino.h>

#define FIRST 0
#define SECOND 1
#define THIRD 2

// const int TAIL_HEAD1 = 13;
// const int TAIL_HEAD2 = 12;
// const int MOUTH1 = 14;
// const int MOUTH2 = 27;

// const int TAIL_HEAD1 = 26;
// const int TAIL_HEAD2 = 25;
// const int MOUTH1 = 33;
// const int MOUTH2 = 32;

const int TAIL_HEAD1 = 5;
const int TAIL_HEAD2 = 18;
const int MOUTH1 = 22;
const int MOUTH2 = 23;

// void whichFish(int fish) {
//     switch (fish)
//     {
//     case FIRST:
//         const int TAIL_HEAD1 = 13;
//         const int TAIL_HEAD2 = 12;
//         const int MOUTH1 = 14;
//         const int MOUTH2 = 27;
//         break;
//     case SECOND:
//         const int TAIL_HEAD1 = 25;
//         const int TAIL_HEAD2 = 26;
//         const int MOUTH1 = 33;
//         const int MOUTH2 = 32;
//         break;
//     default:
//         break;
//     }
// }

void flapTail() {
  #define TAIL_TIME 300
  static long interval = TAIL_TIME;
  static unsigned long previousMillis = 0;
  static bool isFlapping = false;

  unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;

      isFlapping = !isFlapping;

      if (isFlapping) {
        digitalWrite(TAIL_HEAD1, HIGH);
        digitalWrite(TAIL_HEAD2, LOW);
        interval = TAIL_TIME;
      } else {
        digitalWrite(TAIL_HEAD1, LOW);
        digitalWrite(TAIL_HEAD2, LOW);
        interval = TAIL_TIME/2;
      }
    }
}

void sing() {
#define MOUTH_TIME 300
static long interval = MOUTH_TIME;
static unsigned long previousMillis = 0;
static bool isSinging = false;

unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    isSinging = !isSinging;

    if (isSinging) {
      digitalWrite(MOUTH1, HIGH);
      digitalWrite(MOUTH2, LOW);
      interval = MOUTH_TIME;
    } else {
      digitalWrite(MOUTH1, LOW);
      digitalWrite(MOUTH2, LOW);
      interval = MOUTH_TIME/2;
    }
  }
}

void turnHead() {
    digitalWrite(TAIL_HEAD1, LOW);
    digitalWrite(TAIL_HEAD2, HIGH);
}

void stopTailHead() {
  digitalWrite(TAIL_HEAD1, LOW);
  digitalWrite(TAIL_HEAD2, LOW);
}

void stopMouth() {
  digitalWrite(MOUTH1, LOW);
  digitalWrite(MOUTH2, LOW);
}

void stopAll() {
  digitalWrite(TAIL_HEAD1, LOW);
  digitalWrite(TAIL_HEAD2, LOW);
  digitalWrite(MOUTH1, LOW);
  digitalWrite(MOUTH2, LOW);
}

void pinsSetup() {
  pinMode(TAIL_HEAD1, OUTPUT);
  pinMode(TAIL_HEAD2, OUTPUT);
  pinMode(MOUTH1, OUTPUT);
  pinMode(MOUTH2, OUTPUT);

  stopAll();

}