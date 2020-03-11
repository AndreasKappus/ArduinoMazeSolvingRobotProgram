#include"Arduino.h"
#include"Sensors.h"
#include"motors.h"
#include <PID_v1.h>

// this class brings the motors and sensors together.
class Car {
public:
  // car constructor constructs the PID controller components
  Car():leftWallPID(&leftWallInput, &leftWallOutput, &leftWallSetpoint, kp, ki, kd, DIRECT),
        rightWallPID(&rightWallInput, &rightWallOutput, &rightWallSetpoint, kp, ki, kd, DIRECT) {}
        
  void carSetup();
  void setPID();
  void controllerConfig();
  void runController();
  void setPIDValues(int _kp, int _ki, int _kd);
  void leftWallFollow();
  void rightWallFollow();
  void bothWallFollow();
private:
  // pointer to the sensors class to ensure the sensors work with this class
  Sensors* sensors;
  // motors class is essential as this determines the robot's movement
  Motors motors;
  
  double kp, ki, kd;
  
  PID leftWallPID;
  PID rightWallPID;

  double leftWallSetpoint, rightWallSetpoint; // desired value
  double leftWallInput,rightWallInput; // actual value
  double leftWallOutput, rightWallOutput; // what to change it by

  // these variables are used with the sensor pointer to get data from the specified IR sensors
  int leftIR  = 2;
  int frontIR = 1;
  int rightIR = 0;

};
