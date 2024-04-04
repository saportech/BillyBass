#include "dfplayer.h"
#include <Arduino.h>

bool isDFPlayerBusy() {
  #define BUSY_PIN 25
  pinMode(BUSY_PIN,INPUT);
  int busyRead = digitalRead(BUSY_PIN);
  if (busyRead == 1) {
    Serial.println("DFPlayer not busy!");
    return false;
  }
  return true;
}

void playSound(int whatToPlay) {
  switch (whatToPlay) {
  case 1:
    execute_CMD(0x0F, 0x01, 0x01);
    break;
  case 2:
    execute_CMD(0x0F, 0x01, 0x02);
    break;
  case 3:
    execute_CMD(0x0F, 0x01, 0x03);
    break;
  case 4:
    execute_CMD(0x0F, 0x01, 0x04);
    break;
  case 5:
    execute_CMD(0x0F, 0x01, 0x05);
    break;
  default:
    Serial.println("Error in playSomeFile()");
    break;
  }
}

void setVolume(int volume) {
  execute_CMD(0x06, 0, volume); // Set the volume (0x00~0x30)
  Serial.println("Volume set to: " + String(volume));
}

void execute_CMD(byte CMD, byte Par1, byte Par2) {
# define Start_Byte 0x7E
# define Version_Byte 0xFF
# define Command_Length 0x06
# define End_Byte 0xEF
# define Acknowledge 0x00 //Returns info with command 0x41 [0x01: info, 0x00: no info]
  // Calculate the checksum (2 bytes)
  word checksum = -(Version_Byte + Command_Length + CMD + Acknowledge + Par1 + Par2);
  // Build the command line
  byte Command_line[10] = { Start_Byte, Version_Byte, Command_Length, CMD, Acknowledge,
  Par1, Par2, highByte(checksum), lowByte(checksum), End_Byte};
  //Send the command line to the module
  for (byte k=0; k<10; k++)
  {
    Serial2.write( Command_line[k]);
  }
}

void stopSound() {
  execute_CMD(0x16, 0, 0);
  Serial.println("Playback stopped.");
}

void dfPlayerSetup(int txPin) {
  #define RX 34 //Unused
  Serial2.flush();
  Serial2.begin(9600, SERIAL_8N1, RX, txPin);
  stopSound();
  setVolume(15);
}