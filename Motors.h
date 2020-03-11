#include"Arduino.h"
#include"Encoders.h"
#include<Encoder.h>

class Motors {
public:
  void forward(int leftMotorSpeed, int rightMotorSpeed);
  void leftTurn();
  void rightTurn();
  void stop();
  void pinSetup();
  long returnLeftTicks();
  long returnRightTicks();
private:
  int ENABLE_LEFT;
  int ENABLE_RIGHT;
  Encoders* encoders; // encoder pointer used as encoder has a composite relationship with the motors class
  int IN1;
  int IN2;
  int IN3;
  int IN4;
};
