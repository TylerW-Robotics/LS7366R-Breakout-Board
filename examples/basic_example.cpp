// Libraries
#include <Arduino.h>
#include <SPI.h>
#include <LS7366R.h>

// --
// Functions
// Encoder Object
LS7366R enA(7);
LS7366R enB(8);


// --
// 
#define INTERVAL 1000


long previousMillis = 0;        // will store last time LED was updated

void setup() {
  Serial.begin(9600);
  SPI.begin();
  enA.initEncoder();
  enA.clearEncoderCount();
}

void loop() {
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis > INTERVAL) {
    previousMillis = currentMillis;
    enA.readEncoder();
    Serial.print("Encoder A: ");
    Serial.println(enA.enCount);

  }
}
