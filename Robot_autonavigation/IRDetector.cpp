#include "SensorsDRV.h"
#include <Arduino.h>


IRDetector::IRDetector(uint8_t Pin)
{
  _Pin=Pin;
  pinMode(_Pin,INPUT);
}
bool IRDetector::Detect()
{
  Active=!digitalRead(_Pin);
  return Active;
}

