#include <Arduino.h>
#include <Wire.h>
#include <TFLI2C.h>

TFLI2C lidar;

int16_t distance; // in centimeters
int16_t address;
int16_t interval;

void setup() {
  address = TFL_DEF_ADR;
  interval = 50;

  Serial.begin(115200);
  Wire.begin();
}

void loop() {
  if (lidar.getData(distance, address)) {

    if(distance < threshold && turning() && moving()) {
      alert();
    }

  }
  delay(interval);
}

void alert() {

}

bool turning() {

}

bool moving() {

}
