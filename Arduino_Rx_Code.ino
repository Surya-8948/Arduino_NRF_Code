/*
====================================================
 NRF24L01 Receiver Example
====================================================
Receives Structure
Prints:
Joystick X
Joystick Y
LED
Servo Angle
*/
#include <SPI.h>
#include <RF24.h>
RF24 radio(9,10);
const byte address[6] = "NODE1";
// Same Structure
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

  if(!radio.begin())
  {
    Serial.println("NRF24 Missing");
    while(1);
  }

  // Receive Address
  radio.openReadingPipe(0,address);

  radio.setPALevel(RF24_PA_LOW);

  radio.setDataRate(RF24_250KBPS);

  radio.setChannel(100);

  radio.setRetries(5,15);

  radio.setCRCLength(RF24_CRC_16);

  // RX Mode
  radio.startListening();

  Serial.println("Receiver Ready");
}

void loop()
{

  // Check New Packet

  if(radio.available())
  {

      radio.read(&data,sizeof(data));

      Serial.println("----------------");

      Serial.print("Joystick X : ");
      Serial.println(data.joyX);

      Serial.print("Joystick Y : ");
      Serial.println(data.joyY);

      Serial.print("LED : ");
      Serial.println(data.led);

      Serial.print("Servo : ");
      Serial.println(data.servo);

      Serial.println("----------------");

  }

}
