#include"Motors.h"
#define ENABLE_LEFT 10
#define ENABLE_RIGHT 9

#define IN1 8
#define IN2 7
#define IN3 12
#define IN4 11

// encoder constructors from an encoder library are used because the library doesnt like the constructors in the encoder class and source files.
Encoder leftEncoder(2, 4);
Encoder rightEncoder(3, 5);

// motor pin setup to ensure the motors can move and perform their specific roles
void Motors::pinSetup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

// this method handles the forward acceleration of the robot.
// Speed values are passed as parameters so the corrected speeds based on PID calculations can be used
void Motors::forward(int leftMotorSpeed, int rightMotorSpeed) {
  analogWrite(ENABLE_LEFT, leftMotorSpeed);
  analogWrite(ENABLE_RIGHT, rightMotorSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  
  digitalWrite(IN4, HIGH);
}


// one motor is reversed while the other is accelerated to turn the robot
void Motors::leftTurn() {
  analogWrite(ENABLE_LEFT, -80);
  analogWrite(ENABLE_RIGHT, 80);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}


void Motors::rightTurn() {
  analogWrite(ENABLE_LEFT, 80);
  analogWrite(ENABLE_RIGHT, -80);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// stops the motors (useful for debugging)
void Motors::stop() {
  digitalWrite(ENABLE_LEFT, LOW);
  digitalWrite(ENABLE_RIGHT, LOW);
}

// uses the created encoder class get the ticks per second based on wheel rotations
long Motors::returnLeftTicks() {
  return encoders->getTicksPerSec(leftEncoder);
}

long Motors::returnRightTicks() {
  return encoders->getTicksPerSec(rightEncoder);
}
