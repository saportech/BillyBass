#ifndef DFPLAYER_H
#define DFPLAYER_H

#include <Arduino.h>

bool isDFPlayerBusy();
void playSound(int whatToPlay);
void setVolume(int volume);
void execute_CMD(byte CMD, byte Par1, byte Par2);
void dfPlayerSetup(int txPin);

#endif  // DFPLAYER_H