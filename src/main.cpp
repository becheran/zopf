#include <Arduino.h>
#include <Servo.h>

Servo myServo;

const int SERVO_PIN = 9;
const int LEFT  = 10;   // stay a bit away from 0/180 so the servo doesn't hit its end stops
const int RIGHT = 170;

void setup() {
  myServo.attach(SERVO_PIN);
  myServo.write(90);    // start in the middle
  delay(500);
}

void loop() {
  // left to right, slowly
  for (int pos = LEFT; pos <= RIGHT; pos++) {
    myServo.write(pos);
    delay(10);          // larger value = slower movement
  }
  delay(300);

  // right to left
  for (int pos = RIGHT; pos >= LEFT; pos--) {
    myServo.write(pos);
    delay(10);
  }
  delay(300);
}