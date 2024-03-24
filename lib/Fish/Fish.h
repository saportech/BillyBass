#ifndef FISH_H
#define FISH_H

#include <Arduino.h>

class Fish {
private:
    int type; // Type of fish (1-3)
    int tailHeadPin1;
    int tailHeadPin2;
    int mouthPin1;
    int mouthPin2;

public:
    Fish(int fishType);

    void flapTail();
    void sing();
    void turnHead();
    void stopTailHead();
    void stopMouth();
    void stopAll();
    void setupPins();
};

#endif