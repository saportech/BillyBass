#include "communication.h"
//24:6F:28:1E:D3:F0 without red spot on antenna
uint8_t masterMac[] = {0x24, 0x6F, 0x28, 0x1E, 0xD3, 0xF0}; //mac address of esp32 with white spot on antenna
//uint8_t masterMac[] = {0xA4, 0xCF, 0x12, 0x6A, 0x50, 0xD4}; //mac address of esp32 with red spot on antenna

bool Communication::signalReceived = false;

void Communication::OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
    Serial.print("Data received from: ");
    if (memcmp(mac, masterMac, sizeof(masterMac)) == 0 && len == 1 && incomingData[0] == '1') {
        Serial.println("Master");
        signalReceived = true;
    }
}

Communication::Communication() {

}

Communication::~Communication() {
    esp_now_deinit();
}

void Communication::init() {

    Serial.print("MAC address: ");
    Serial.println(WiFi.macAddress());

    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
    memcpy(peerInfo.peer_addr, masterMac, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    
    if (esp_now_add_peer(&peerInfo) != ESP_OK){
        Serial.println("Failed to add peer");
        return;
    }

    Serial.println("ESP-NOW Initialized slave");

    esp_now_register_recv_cb(OnDataRecv);

}

void Communication::setSignalReceived(bool value) {
    signalReceived = value;
}

bool Communication::checkSignalReceived() {
    return signalReceived;
}
