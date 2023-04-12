#include <Arduino.h>
#include <Wire.h>
#include <TFLI2C.h>
#include <Timer.h>

// GENERAL
int interval = 50;

// LIDAR SENSOR
TFLI2C lidar; // lidar object
int16_t distance; // input distance in cm
int16_t address = TFL_DEF_ADR; // lidar address
int threshold = 100; // distance threshold in cm

// ANGLE SENSOR/POTENTIOMETER
int potentiometer = A0; // potentiometer pin #
int minAngle = 0; // minimum steering wheel angle
int maxAngle = 100; // maximum steering wheel angle

// ALERT OUTPUT
int led = 4; // led pin #
int speaker = 5; // speaker pin #
int alertTime = 500; // time of alert in ms

void setup() {
  Serial.begin(115200);
  Wire.begin();
  pinMode(potentiometer, INPUT);
  pinMode(speaker, OUTPUT);
  pinMode(led, OUTPUT);
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
  tone(speaker, 85);
  digitalWrite(led, HIGH);
  delay(alertTime);
  noTone(speaker);
  digitalWrite(led, LOW);
}

bool turning() {
  int angle = analogRead(potentiometer);

  if(angle < minAngle || angle > maxAngle) {
    return true;
  }

  return false;
}

// gets if arduino has a velocity (we not doing this)
bool moving() {
  return true;
}
