/*
 * Robot_autonavigation
 * 
 * Use the 1-9 keys to control the robot.
 * Press "PREV" key to turn on the IR avoidance.
 * Press "NEXT" key to turn on the robot IR follower.
 * Press "PLAY" key to turn on both the IR avoidance and IR follower.
 * Press any key to turn IR avoidance and IR follower off.
 *
 * created 01 Aug 2014
 * by Sui Wai
 *
 * This example code is in the public domain.
 *
 */

// include our motor code
#include "motor.h"
// include Ken Shirriff's IR Remote Library
// You must install this if you havn't already
// https://github.com/shirriff/Arduino-IRremote
#include <IRremote.h>
// include our remote control codes
#include "codes.h"
#include "sensorsDRV.h"


#define fwSpeed 255
#define fwTurnSpeed 200
#define softTurnSpeed 160

const int motorRENPin = 10;
const int motorRIN1Pin = 8;
const int motorRIN2Pin = 9;

const int motorLENPin = 5;
const int motorLIN1Pin = 6;
const int motorLIN2Pin = 7;

// the pin the IR Receiver is connected to
const int irPin = 12;

// left IR detector sensor to digital pin 2
const int Left_IRDetector_Pin = 2;
// right IR detector sensor to digital pin 3
const int Right_IRDetector_Pin = 3;

// the pin the Uno's LED is connected to
// this will be lit when the IR follower or IR detector is enabled
const int led_Pin = 13;

// the analog output pins from the IR sensor
// the rightmost IR Diode
Follower follower(A5, A4, A3, A2, A1, A0);


LED led(led_Pin);
IRrecv irrecv(irPin);
IRDetector rightIRDetector(Right_IRDetector_Pin);
IRDetector  leftIRDetector(Left_IRDetector_Pin);

// Create two Motor objects (instances of our Motor class)
// to drive each motor.
Motor rightMotor(motorRIN1Pin, motorRIN2Pin, motorRENPin);
Motor  leftMotor(motorLIN1Pin, motorLIN2Pin, motorLENPin);

unsigned long last_time = 0;
unsigned long last_cmd = 0;
const int repeatTimeout = 150;
decode_results results;

#define RunMode_Stop 0
#define RunMode_Manual 1
#define RunMode_IRDetector 2
#define RunMode_Follower 3
#define RunMode_Both 4
unsigned int RunMode = RunMode_Stop;

void processCommand(unsigned long code);
void RunTheCar();


void setup()
{
  // enable the receiver
  irrecv.enableIRIn();
  leftMotor.freeRun();
  rightMotor.freeRun();
}


void loop()
{
  // check to see if the receiver has received
  // a command
  if (irrecv.decode(&results))
  {
    // yes
    // is it the Repeat command?
    if (results.value != IR_REPEAT)
    {
      // if it isn't remember the command and process it
      last_cmd = results.value;
      last_time = millis();

      processCommand(results.value);
    }
    else
    {
      // if it is reset the timeout
      last_time = millis();
    }

    // tell the library we're ready to listen for
    // another command
    irrecv.resume();
  }
  else
  {
    // no command has been received
    // check to see if we're waiting for a repeat and our
    // if our time has expired
    if (last_cmd != 0 && last_time + repeatTimeout < millis())
    {
      // if the last command was one that caused the robot to move
      // and it has now been released, we need to stop the robot
      if (last_cmd == IR_1 || last_cmd == IR_2 || last_cmd == IR_3 ||
          last_cmd == IR_4 || last_cmd == IR_5 || last_cmd == IR_6 ||
          last_cmd == IR_7 || last_cmd == IR_8 || last_cmd == IR_9)
      {
        // let the robot come to a stop
        RunMode = RunMode_Stop;
      }

      // the time expired, don't wait anymore
      last_cmd = 0;
    }
  }
  RunTheCar();
}
void processCommand(unsigned long code)
{
  switch (code)
  {
    // enables both IR detector an IR follower
    case IR_PLAY:
      RunMode = RunMode_Both;
      break;
      // enable IR follower
    case IR_NEXT:
      RunMode = RunMode_Follower;
      break;
      // enable IR detector
    case IR_PREV:
      RunMode = RunMode_IRDetector;
      break;
    case IR_1:
    case IR_2:
    case IR_3:
    case IR_4:
    case IR_6:
    case IR_7:
    case IR_8:
    case IR_9:
      RunMode = RunMode_Manual;
      break;
      // stops the robot
    case IR_5:
      RunMode = RunMode_Stop;
      break;
    default:
      break;
  }
}

int leftSpeed = 0;
int rightSpeed = 0;

void SetMotor()
{
  if (leftSpeed > 0)
  {
    leftMotor.forward(leftSpeed);
  } else if (leftSpeed < 0) {
    leftMotor.backward(-leftSpeed);
  } else leftMotor.brake();

  if (rightSpeed > 0)
  {
    rightMotor.forward(rightSpeed);
  } else if (rightSpeed < 0) {
    rightMotor.backward(-rightSpeed);
  } else rightMotor.brake();
}


void RunTheCar()
{
  switch (RunMode)
  {
    case RunMode_Manual:
      led.Off();
      GetSpeedByManual();
      break;
    case RunMode_IRDetector:
      led.Flash(200);
      GetSpeedByDetector();
      break;
    case RunMode_Follower:
      led.Flash(500);
      GetSpeedByFollower_Analog();
      break;
    case RunMode_Both:
      led.On();
      if (!GetSpeedByDetector())GetSpeedByFollower_Analog();
      break;
    case RunMode_Stop:
    default:
      leftMotor.freeRun();
      rightMotor.freeRun();
      led.Off();
      return;
      break;
  }
  if (GetSpeedByUnNormal())
  {
    SetMotor();
    delay(300);
  } else {
    SetMotor();
    delay(5);
  }
}


bool GetSpeedByManual()
{
  switch (last_cmd)
  {
      // forwards
    case IR_2:
      leftSpeed = fwSpeed;
      rightSpeed = fwSpeed;
      break;
      // hard left
    case IR_4:
      leftSpeed = -fwTurnSpeed;
      rightSpeed = fwTurnSpeed;
      break;
      // forward-left
    case IR_1:
      leftSpeed = softTurnSpeed;
      rightSpeed = fwTurnSpeed;
      break;
      // hard right
    case IR_6:
      leftSpeed = fwTurnSpeed;
      rightSpeed = -fwTurnSpeed;
      break;
      // forward-right
    case IR_3:
      leftSpeed = fwTurnSpeed;
      rightSpeed = softTurnSpeed;
      break;
      // backwards
    case IR_8:
      leftSpeed = -fwSpeed;
      rightSpeed = -fwSpeed;
      break;
      // backwards-left
    case IR_7:
      leftSpeed = -softTurnSpeed;
      rightSpeed = -fwTurnSpeed;
      break;
      // backwards-right
    case IR_9:
      leftSpeed = -fwTurnSpeed;
      rightSpeed = -softTurnSpeed;
      break;
    default:
      return false;
      break;
  }
  return true;
}


bool GetSpeedByFollower_Analog()
{
  follower.analogDetect();
  int left = follower.LeftWeight();
  int right = follower.RightWeight();
  if ((left > 0) && (right > 0))
  {
    leftSpeed = fwSpeed;
    rightSpeed = fwSpeed;
    return true;
  }
  if ((left < 0) && (right < 0))
  {
    left = follower.LeftSite();
    right = follower.RightSite();
    if (left > right)
    {
      leftSpeed = -fwTurnSpeed;
      rightSpeed = fwTurnSpeed;
    } else {
      leftSpeed = fwTurnSpeed;
      rightSpeed = -fwTurnSpeed;
    }
    return true;
  }
  if (left > 0) leftSpeed = softTurnSpeed; else if (left < 0) leftSpeed = -softTurnSpeed;
  if (right > 0)rightSpeed = softTurnSpeed; else if (right < 0)rightSpeed = -softTurnSpeed;
  return true;
}


bool GetSpeedByDetector()
{
  if (leftIRDetector.Detect())
  {
    rightSpeed = -fwTurnSpeed;
  } else {
    rightSpeed = fwSpeed;
  }

  if (rightIRDetector.Detect())
  {
    leftSpeed = -fwTurnSpeed;
  } else {
    leftSpeed = fwSpeed;
  }
  return (leftIRDetector.Active || rightIRDetector.Active);
}


int Left_Action_Detect = 0;
int Right_Action_Detect = 0;
int Action_Count = 0;


void updateAction()
{
  if (leftSpeed > 0)
  {
    Left_Action_Detect++;
  } else if (leftSpeed < 0) {
    Left_Action_Detect--;
  }
  if (rightSpeed > 0)
  {
    Right_Action_Detect++;
  } else if (rightSpeed < 0) {
    Right_Action_Detect--;;
  }
  Action_Count++;
}
bool CheckUnNormal()
{
  bool result = false;
  if ((Action_Count > 500)) 
  {
    if ((abs(Right_Action_Detect) < 50) || (abs(Left_Action_Detect) < 50))result = true; //前后徘徊,或者其中一个轮子没动=车在一直绕圈子
    if (abs(Left_Action_Detect + Right_Action_Detect) < 50)result = true; //两个轮子反向转动,次数基本相等=原地转圈
    if ((Left_Action_Detect < -50) && (Right_Action_Detect < -50))result = true; //总在退后是不对的
    Action_Count = 0;
    Right_Action_Detect = 0;
    Left_Action_Detect = 0;
  }
  return result;
}
bool GetSpeedByUnNormal()
{
  updateAction();
  if (CheckUnNormal())
  {
    byte plan=(random()%3);
    if(plan== 0)
    {
      leftSpeed =  -fwSpeed;
      rightSpeed = -fwSpeed;      
    }
    else if (plan == 1)
    {
      leftSpeed = fwSpeed;
      rightSpeed = -fwSpeed;
    } else {
      leftSpeed = -fwSpeed;
      rightSpeed = fwSpeed;
    }
    return true;
  }
  return false;
}

