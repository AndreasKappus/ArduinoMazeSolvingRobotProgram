#include"Car.h"



// handles the setup for the robot and their seperate components, this method is used in setup function in the main arduino file
void Car::carSetup() {
  // sensors constructor
  Sensors(leftIR, frontIR, rightIR);
  
  motors.pinSetup();

  // set PID values first as set tunings is inside the setPID method
  setPIDValues(2, 0, 0.02);
  setPID();
}

// call methods from the PID library to set the tunings and the output limits to ensure the PID controllers work
void Car::setPID() {
  
  leftWallPID.SetMode(AUTOMATIC);
  rightWallPID.SetMode(AUTOMATIC);


  leftWallPID.SetTunings(kp, ki, kd);
  rightWallPID.SetTunings(kp, ki, kd);


  leftWallPID.SetOutputLimits(-200, 200);
  rightWallPID.SetOutputLimits(-200, 200);

}

// setter function so the K values can be set and adjusted easily
// kd represents the proportional gain, ki represents the integral and kd represents the derivative
void Car::setPIDValues(int _kp, int _ki, int _kd) {
  kp = _kp;
  ki = _ki;
  kd = _kd;
}


// this method uses the left IR sensor as the left wall PID input which is then used to directly control the motors 
// based on the setpoint which is the ideal distance the robot should be from the wall
void Car::leftWallFollow() {
  leftWallInput = sensors->readSensor(leftIR);
  leftWallSetpoint = 400;
  // boolean condition which is used with the right IR sensor to check if there is no more space to move
  bool frontLeft = sensors->readSensor(frontIR) > 400  && sensors->readSensor(leftIR) > 400;

  // PID library method handles the calculations for the PID controller which is then used to directly control the motors
  // the output is calculated which would be subtracted/added to the motor speeds
  leftWallPID.Compute();

  // speeds/slows motors based on distance from the wall
  double newLSpeed = 100 + leftWallOutput;
  double newRSpeed = 100 - leftWallOutput;

  // the new speed is then used to accelerate based on distance and the output values
  motors.forward(newLSpeed, newRSpeed);

  // checks if robot cannot go anywhere, if true, the robot should stop
  if(frontLeft && sensors->readSensor(rightIR) > 400) {
    motors.stop();
    delay(100);
  }

  // since the robot is already following the left wall, this check is used to ensure head-on collisions don't occur
  if(sensors->readSensor(frontIR) > 400) {
    // stop method is used to help control turning (IT WORKS DONT REMOVE)
    motors.stop();
    motors.rightTurn(); 
    
  }
}

// this method is the same as left wall controller, except it follows the right wall and handles the PID calculations based on the
// robot's distance from the right wall.
void Car::rightWallFollow() {
  rightWallInput = sensors->readSensor(rightIR);
  rightWallSetpoint = 400;
  bool frontLeft = sensors->readSensor(frontIR) > 400  && sensors->readSensor(leftIR) > 400;
  rightWallPID.Compute();

  // this is inverted to enable the robot's correction when veering away from the distance setpoint
  double newLSpeed = 100 - rightWallOutput;
  double newRSpeed = 100 + rightWallOutput;

  motors.forward(newLSpeed, newRSpeed);
  
  if(frontLeft && sensors->readSensor(rightIR) > 400) {
    motors.stop();
    delay(100);
  }
  
  if(sensors->readSensor(frontIR) > 400) {
    motors.stop();
    motors.leftTurn();
    
  }
}

// this method uses both PID controllers based on the closest wall
// if the left wall is closer, then the left wall PID controller is used and the robot follows the left wall
// if the right wall is closer, then the right wall PID controller is used and the robot follows the right wall
void Car::bothWallFollow() {
  if(sensors->readSensor(leftIR) > sensors->readSensor(rightIR)) {
    leftWallFollow();
  }
  if(sensors->readSensor(leftIR) < sensors->readSensor(rightIR)) {
    rightWallFollow();
  }
  
}

// this handles function handles which PID controller to use
// uncomment one and leave the other two commented to run selected PID controlled movement methods
void Car::controllerConfig() {


  leftWallFollow();
//  rightWallFollow();
//  BothWallFollow();

}

// runs the controller configuration, this method is used in the main loop
void Car::runController() {
  controllerConfig();

}
