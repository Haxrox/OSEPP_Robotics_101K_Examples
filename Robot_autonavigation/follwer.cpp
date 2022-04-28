#include "SensorsDRV.h"
#include <Arduino.h>

Follower::Follower(uint8_t Pin1, uint8_t Pin2, uint8_t Pin3, uint8_t Pin4, uint8_t Pin5, uint8_t Pin6)
{
  _Pin[0] = Pin1;
  _Pin[1] = Pin2;
  _Pin[2] = Pin3;
  _Pin[3] = Pin4;
  _Pin[4] = Pin5;
  _Pin[5] = Pin6;
  for (int i = 0; i < 6; i++)pinMode(_Pin[i], INPUT);
}

int* Follower::digitalDetect()
{
  for (int i = 0; i < 6; i++)value[i] = digitalRead(_Pin[i]);
  return value;
}
int* Follower::analogDetect()
{
  for (int i = 0; i < 6; i++)value[i] = (0x3ff - analogRead(_Pin[i]));
  return value;
}


//for analog only
int Follower::LeftWeight()
{
  return (value[3] - value[5] - value[4] + (value[2] + value[1] + value[0]) / 3);
}
int Follower::RightWeight()
{
  return (value[2] - value[0] - value[1] + (value[3] + value[4] + value[5]) / 3);
}

int Follower::LeftSite()
{
  return (value[3] + value[4] + value[5]);
}
int Follower::RightSite()
{
  return (value[0] + value[1] + value[2]);
}

