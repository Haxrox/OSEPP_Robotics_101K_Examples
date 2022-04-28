#include "SensorsDRV.h"
#include <Arduino.h>



LED::LED(uint8_t PinLed)
{
    _Pin=PinLed;
    _Timeout=0;
    pinMode(_Pin, OUTPUT);
}

void LED::Flash(unsigned int BlinkTime)
{
  if((millis()>_Timeout ))
  {
    if(digitalRead(_Pin))digitalWrite(_Pin, LOW);else digitalWrite(_Pin,HIGH);
    if(BlinkTime>3000)BlinkTime=3000;
    _Timeout=millis()+BlinkTime;
  }
}

void LED::On()
{
  digitalWrite(_Pin, HIGH);
}

void LED::Off()
{
  digitalWrite(_Pin, LOW);
}
