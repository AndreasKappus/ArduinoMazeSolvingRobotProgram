#include"Arduino.h"
class Sensors {
public:
  // constructor to set up pins and read sensor method for IR sensor data stream
  Sensors(int leftPin,int frontPin,int rightPin);

  double readSensor(int pin);
private:
  int LEFTPIN;
  int FRONTPIN;
  int RIGHTPIN;
};
