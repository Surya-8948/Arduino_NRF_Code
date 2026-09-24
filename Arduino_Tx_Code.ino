/*
====================================================
 NRF24L01 Transmitter 
 Author : Surya Mani Bajpai
====================================================
This code sends:
1. Joystick X
2. Joystick Y
3. LED Status
4. Servo Angle
Every 100ms
*/
#include <SPI.h>
#include <RF24.h>

// CE = D9
// CSN = D10
RF24 radio(9, 10);

// Communication Address (Must be same on RX)
const byte address[6] = "NODE1";

// Structure (TX and RX must be exactly same)
struct ControlData
{
  int joyX;
  int joyY;
  bool led;
  int servo;
};

ControlData data;

void setup()
{
  Serial.begin(115200);

  // Initialize NRF24
  if (!radio.begin())
  {
    Serial.println("NRF24 Not Found");
    while (1);
  }

  // Receiver Address
  radio.openWritingPipe(address);

  // Reliable Configuration
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS); 
  radio.setChannel(100);
  radio.setRetries(5, 15); // delay , times 
  radio.setCRCLength(RF24_CRC_16);

  // TX Mode
  radio.stopListening();

  Serial.println("Transmitter Ready");
}

void loop()
{
  // Example Data
  data.joyX = analogRead(A0);
  data.joyY = analogRead(A1);
  data.led = true;
  data.servo = 90;
  // Send Structure
  bool ok = radio.write(&data, sizeof(data));
  if (ok)
    Serial.println("Packet Sent");
  else
    Serial.println("Transmission Failed");
  delay(100);
}
