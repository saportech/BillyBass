#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

class Communication {
public:
    Communication();
    ~Communication();
    void init();
    bool checkSignalReceived();
    void setSignalReceived(bool value);
    static void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);
private:
    esp_now_peer_info_t peerInfo;
    static bool signalReceived;
};

#endif // COMMUNICATION_H
