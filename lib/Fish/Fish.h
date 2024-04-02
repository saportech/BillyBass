#ifndef FISH_H
#define FISH_H

#include <Arduino.h>
#include "dfplayer.h"

class Fish {
private:
    int type;
    int tailHeadPin1;
    int tailHeadPin2;
    int mouthPin1;
    int mouthPin2;

    int txPin;

    unsigned long intervalFlap;
    unsigned long previousMillisFlap;
    bool isFlapping;

    unsigned long intervalSing;
    unsigned long previousMillisSing;
    bool isSinging;
    
    int state;
    unsigned long previousMillisSM;

public:
    Fish(int fishType);

    void flapTail();
    void sing();
    void turnHead();
    void stopTailHead();
    void stopMouth();
    void stopAll();
    void setupPins();
    void songStateMachine(int songNumber);
    void Test();

};

#endif