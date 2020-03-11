#include"Sensors.h"

// the constructor allocates the pin parameters to the variables declared in the sensors class to set the pins
Sensors::Sensors(int _leftPin,int _frontPin,int _rightPin) {
   LEFTPIN    = _leftPin;
   FRONTPIN   = _frontPin;
   RIGHTPIN   = _rightPin;
}

// returns a distance reading. since the IR sensor is light based, the closer an object, the higher the distance
double Sensors::readSensor(int pin) {
  return analogRead(pin);
}
