#include <Arduino.h>
#include <Servo.h>

Servo myServo;

const int SERVO_PIN = 6;      // was D9; any digital pin works with the Servo library
const int LED_PIN = LED_BUILTIN; // onboard LED (D13)
const int LEFT  = 10;   // stay a bit away from 0/180 so the servo doesn't hit its end stops
const int RIGHT = 170;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  // 5 quick blinks = new sketch was uploaded and is running
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  }

  myServo.attach(SERVO_PIN);
  myServo.write(90);    // start in the middle
  delay(500);
}

void loop() {
  // left to right, slowly (LED on)
  digitalWrite(LED_PIN, HIGH);
  for (int pos = LEFT; pos <= RIGHT; pos++) {
    myServo.write(pos);
    delay(10);          // larger value = slower movement
  }
  delay(300);

  // right to left (LED off)
  digitalWrite(LED_PIN, LOW);
  for (int pos = RIGHT; pos >= LEFT; pos--) {
    myServo.write(pos);
    delay(10);
  }
  delay(300);
}