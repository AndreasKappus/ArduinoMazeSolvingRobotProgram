#include"Car.h"

Car car; // declared globally as it works

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // car setup to setup the pins and PID values
  car.carSetup();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  car.runController();
}
