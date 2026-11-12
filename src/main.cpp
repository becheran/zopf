#include <Arduino.h>
#include <Servo.h>

// ---------------------------------------------------------------------------
// Zopf: wags a hair tail with an MG90S servo, running on 4x AAA NiMH.
//
// The servo pulls the most current (and heats the batteries) when it
// accelerates the tail hard or gets blocked. This sketch keeps the current low:
//  * smooth start/stop (no jerks at the end points) -> low peak current
//  * slower sweep over a smaller range              -> less torque needed
//  * servo is switched off during pauses            -> ~0 mA while resting
// The PTC fuse in the battery wire is the hardware backup (see README).
// ---------------------------------------------------------------------------

Servo myServo;

const int SERVO_PIN = 6;
const int LED_PIN = LED_BUILTIN;   // onboard LED (D13)

// --- Settings: change these to tune the movement ---------------------------
const int LEFT  = 30;                 // degrees; keep well away from the end stops (0/180)
const int RIGHT = 150;                // and make sure the tail can swing freely across this range
const unsigned long MOVE_MS  = 300;  // time for one sweep; smaller = faster = more current
const unsigned long PAUSE_MS = 100;   // pause at each end (servo off)
// ----------------------------------------------------------------------------

const unsigned long FRAME_MS = 20;    // servo gets a new pulse every 20 ms anyway

int currentPos = (LEFT + RIGHT) / 2;

void servoOn() {
  myServo.write(currentPos);  // set the position first, so attaching doesn't make it jump
  myServo.attach(SERVO_PIN);
}

void servoOff() {
  myServo.detach();           // no signal -> motor is idle and draws almost nothing
}

// Smoothly move from currentPos to target in MOVE_MS (ease in / ease out).
void moveTo(int target) {
  const int start = currentPos;
  const unsigned long t0 = millis();
  for (;;) {
    unsigned long elapsed = millis() - t0;
    if (elapsed >= MOVE_MS) break;
    float t = (float)elapsed / MOVE_MS;          // 0..1
    float eased = (1.0f - cos(PI * t)) * 0.5f;   // slow at both ends, fastest in the middle
    myServo.write(start + (int)lround((target - start) * eased));
    delay(FRAME_MS);
  }
  myServo.write(target);
  currentPos = target;
}

void restWithServoOff(unsigned long ms) {
  // Let the servo reach its target before cutting the signal.
  delay(100);
  servoOff();
  delay(ms);
  servoOn();
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  // 5 quick blinks = new sketch was uploaded and is running
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  }

  servoOn();       // starts in the middle
  delay(500);
}

void loop() {
  // left to right (LED on)
  digitalWrite(LED_PIN, HIGH);
  moveTo(RIGHT);
  restWithServoOff(PAUSE_MS);

  // right to left (LED off)
  digitalWrite(LED_PIN, LOW);
  moveTo(LEFT);
  restWithServoOff(PAUSE_MS);
}
