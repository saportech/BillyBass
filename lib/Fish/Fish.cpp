#include <Arduino.h>
#include "Fish.h"

Fish::Fish(int fishType) : type(fishType) {
    switch (type) {
        case 1:
            tailHeadPin1 = 5;
            tailHeadPin2 = 18;
            mouthPin1 = 22;
            mouthPin2 = 23;
            break;
        case 2:
            tailHeadPin1 = 26;
            tailHeadPin2 = 25;
            mouthPin1 = 33;
            mouthPin2 = 32;
            break;
        case 3:
            tailHeadPin1 = 13;
            tailHeadPin2 = 12;
            mouthPin1 = 14;
            mouthPin2 = 27;
            break;
        default:
            Serial.println("Invalid fish type!");
            break;
    }
}

void Fish::flapTail() {
    const unsigned long TAIL_TIME = 300;
    static long interval = TAIL_TIME;
    static unsigned long previousMillis = 0;
    static bool isFlapping = false;

    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        isFlapping = !isFlapping;

        if (isFlapping) {
            digitalWrite(tailHeadPin1, HIGH);
            digitalWrite(tailHeadPin2, LOW);
            interval = TAIL_TIME;
        } else {
            digitalWrite(tailHeadPin1, LOW);
            digitalWrite(tailHeadPin2, LOW);
            interval = TAIL_TIME / 2;
        }
    }
}

void Fish::sing() {
    const unsigned long MOUTH_TIME = 300;
    static long interval = MOUTH_TIME;
    static unsigned long previousMillis = 0;
    static bool isSinging = false;

    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        isSinging = !isSinging;

        if (isSinging) {
            digitalWrite(mouthPin1, HIGH);
            digitalWrite(mouthPin2, LOW);
            interval = MOUTH_TIME;
        } else {
            digitalWrite(mouthPin1, LOW);
            digitalWrite(mouthPin2, LOW);
            interval = MOUTH_TIME / 2;
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
