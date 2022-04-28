#ifndef _SENSORSDRV_H_
#define _SENSORSDRV_H_


#include <stdint.h>


class IRDetector
{
  public:
     IRDetector(uint8_t Pin);
     bool Detect();
     bool Active;
  private:
    uint8_t _Pin;
};

class Follower
{
  public:
      Follower(uint8_t Pin1,uint8_t Pin2,uint8_t Pin3,uint8_t Pin4,uint8_t Pin5,uint8_t Pin6);
      int* digitalDetect();
      int* analogDetect();
      
      int LeftWeight();
      int RightWeight();
      int LeftSite();
      int RightSite();      
      
      int value[6];
  private:
      uint8_t _Pin[6];
};

class LED 
{
	public:
		LED(uint8_t PinLed);
                void Flash(unsigned int BlinkTime);
                void On();
                void Off();
	private:
		uint8_t _Pin;
                unsigned long _Timeout;
};

#endif
