#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

// Function declarations
void setup();
void loop();
void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
void sendData();
void setupEspNow();

//uint8_t slaveMac[] = {0x24, 0x6F, 0x28, 0x1E, 0xD3, 0xF0};//Of esp32 without red spot on antenna
uint8_t slaveMac[] = {0xFC, 0xB4, 0x67, 0x73, 0xEF, 0x4C};//of Billy Bass
esp_now_peer_info_t peerInfo;

const int buttonPin = 12;

void setup() {

  Serial.begin(115200);

  pinMode(buttonPin, INPUT_PULLUP);

  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());

  setupEspNow();

}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    Serial.println("Button pressed");
    sendData();
    delay(1000);
  }
}

void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Data sent to: ");
  if (status == ESP_NOW_SEND_SUCCESS) {
    Serial.println("Signal sent to master successfully");
  } else {
    Serial.println("Failed to send signal to master");
  }
}

void sendData() {

  uint8_t data = '1';

  esp_err_t result = esp_now_send(slaveMac, (uint8_t*)&data, sizeof(data));

  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }

}

void setupEspNow() {

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_send_cb(onDataSent);
  memcpy(peerInfo.peer_addr, slaveMac, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

  Serial.println("ESP-NOW Initialized master");

}
