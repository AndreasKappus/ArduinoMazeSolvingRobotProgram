#include"Encoders.h"


// gets the ticks per second based on time interval and wheel position based on rotation
long Encoders::getTicksPerSec(Encoder enc) {
  
  long currentTime = millis();
  float newTime = (float)(currentTime - prevTime) / 1000;
  Serial.print("Old Position");
  Serial.println(oldPosition);
  // forward is negative, backward is positive
  long newPosition = enc.read();
  double ticksPerSec = (double)(newPosition - oldPosition) / newTime;
  ticksPerSec *= -1;
  Serial.print("TICKS PER SECOND: ");
  
  oldPosition = newPosition;
  prevTime = currentTime;

  enc.write(0);
  return newPosition;
}
