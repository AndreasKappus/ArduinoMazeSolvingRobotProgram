#include"Arduino.h"
#include <Encoder.h>

// this class handles the encoders which are attached to the motors to measure wheel rotations which in turn can be used to
// get an accurate reading of distance traveled and speed
class Encoders {
public:

  long getTicksPerSec(Encoder enc);
private:
  long ticksPerSec;
  long oldPosition  = -999;
  long timeInterval = 1000;
  long prevTime = 0;
  
};
