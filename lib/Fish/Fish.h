#ifndef FISH_H
#define FISH_H

#include <Arduino.h>
#include <queue>
#include "dfplayer.h"
#include "globals.h"

struct Action {
  unsigned long duration;
  int action;
};

class Fish {
private:
    std::queue<Action> actionQueue;
    int type;
    int tailHeadPin1;
    int tailHeadPin2;
    int mouthPin1;
    int mouthPin2;

    int txPin;
    
    int state;
    unsigned long previousMillisSM;

    bool isFirstPerformCall;
    bool isFirstTimeEmpty;

    bool isFishPlayingBool;

public:
    Fish(int fishType);

    void setupPins();
    void turnHead();
    void stopTailHead();
    void stopMouth();
    void stopAll();
    void performAction(unsigned long time, int action);
    void updateAction();
    void perform(int songNumber);
    void turnTail();
    bool isFishPlaying();
    void setFishPlaying(bool isFishPlaying);

};

#endif