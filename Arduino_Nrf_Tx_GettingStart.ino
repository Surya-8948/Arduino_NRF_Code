#include <SPI.h>
#include <RF24.h>
RF24 radio(9, 10);      // CE, CSN
const byte address[6] = "00001";
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();
}
void loop() {
  const char text[] = "Hello";
  bool ok = radio.write(&text, sizeof(text));
  if (ok)
    Serial.println("Sent");
  else
    Serial.println("Failed");

  delay(1000);
}
