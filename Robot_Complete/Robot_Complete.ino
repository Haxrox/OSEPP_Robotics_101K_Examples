/*
 * Tutorial 3c: Robot Complete
 * 
 * RobotRemote and RobotFollower all in one.
 *
 * Use the 1-9 keys to control the robot.
 * Press the 0 key to turn on the robot IR follower.
 * Press any key to turn the IR follower off.
 *
 * created 01 Oct 2013
 * by Blaise Jarrett
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
  // include our IR Follower code
#include "irfollower.h"

// left IR detector sensor to digital pin 2
const int Left_IRDetector_Pin = 2;
// right IR detector sensor to digital pin 3
const int Right_IRDetector_Pin = 3;




// The Right Motors Enable Pin
// Labelled on the motor driver as ENA
// Be carful of PWM Timers
const int motorRENPin = 10;
// The Right Motors IN1 Pin
// Labelled on the motor driver as IN1
const int motorRIN2Pin = 9;
// The Right Motors IN2 Pin
// Labelled on the motor driver as IN2
const int motorRIN1Pin = 8;

// The Left Motors Enable Pin
// Labelled on the motor driver as ENB
// Be carful of PWM Timers
const int motorLENPin = 5;
// The Left Motors IN1 Pin
// Labelled on the motor driver as IN3
const int motorLIN2Pin = 7;
// The Left Motors IN2 Pin
// Labelled on the motor driver as IN4
const int motorLIN1Pin = 6;

// the speed used to drive forward
// (buttons 2, 8)
// 0 to 255
const int fwSpeed = 255;
// the speed used to do a hard turn (spin on the spot)
// (buttons 4, 6)
// 0 to 255
const int fwTurnSpeed = 200;
// the speed used to do a soft turn (buttons 1, 3, 7, 9)
// 0 to 255
uint8_t softTurnSpeed = 100;

// the pin the IR Receiver is connected to
const int irPin = 12;

// the digital output pins from the IR sensor
// the rightmost IR Diode
const int followD1 = A0;
const int followD2 = A1;
const int followD3 = A2;
const int followD4 = A3;
const int followD5 = A4;
// the leftmost IR Diode
const int followD6 = A5;

// the fastest the robot can go for the follower
const int maxSpeed = fwSpeed;
// the max and min +- input to driveDegrees
const int steeringMax = 90;

// Create two Motor objects (instances of our Motor class)
// to drive each motor.
Motor rightMotor(motorRIN1Pin, motorRIN2Pin, motorRENPin);
Motor leftMotor(motorLIN1Pin, motorLIN2Pin, motorLENPin);

// create an IR Receiver object from the library
IRrecv irrecv(irPin);
// we'll need a decode_results variable to store
// the IR readings
decode_results results;

// We're going to need to remember the last command
// and the time the last command was received while
// waiting for a repeat to occur
unsigned long last_time = 0;
unsigned long last_cmd = 0;

// the time a repeat must be sent by to keep the LED on (in ms)
const int repeatTimeout = 150;

// Create our IR Follower object
IRFollower irFollower(followD1, followD2, followD3,
                      followD4, followD5, followD6);

// we will toggle this to enable/disable the follower
bool irFollowerEnabled = false;

// the pin the Uno's LED is connected to
// this will be lit when the IR follower is enabled
const int ledPin = 13;
// we will toggle this to enable/disable the IRDetector
bool irDetectorEnabled=false;


void setup()
{
    // enable the receiver
    irrecv.enableIRIn();

    // Set up our LED
    pinMode(ledPin, OUTPUT);
}

// steer the robot with a degrees value
// Note: If you input 90 degrees, it will not turn the robot
//       90 degrees. It will instead stear the robot to the right
//       as much as possible.
// Think of it as a steering wheel that goes from -90 to 90 degrees.
// Min: -90, Max: 90  
void steerDegrees(double deg)
{
    // if the angle is 0 or close to 0 drive forward
    if (deg > -1 && deg < 1)
    {
        leftMotor.forward(maxSpeed);
        leftMotor.forward(maxSpeed);
        // we don't need to do any more processing, end here
        return;
    }

    // use a linear equation to calculate the motor speed
    // required to turn
    double slope = ((double)maxSpeed * -1) / steeringMax;
    double turnMotorSpeed = (slope * abs(deg)) + maxSpeed;

    // if we're turning right
    if (deg > 1)
    {
        leftMotor.forward(maxSpeed);
        // slow down the right motor
        rightMotor.forward(turnMotorSpeed);
    }
    // if we're turning left
    else if (deg < 1)
    {
        // slow down the left motor
        leftMotor.forward(turnMotorSpeed);
        rightMotor.forward(maxSpeed);
    }
}

void runIRDetector()
{ 
      // read our left and right IR Detector sensors
      int Left_IRDetector = !digitalRead(Left_IRDetector_Pin);
      int Right_IRDetector = !digitalRead(Right_IRDetector_Pin);
      
      if(Right_IRDetector)   //if right ir detector active
      {
        leftMotor.backward(maxSpeed);  // left motor go backward at drive speed
      }else{
        leftMotor.forward(maxSpeed);  // if not, left motor drive forward
      }
      
      if(Left_IRDetector)  // if left ir detector active
      {
        rightMotor.backward(maxSpeed);  // right motor go backward at drive speed
      }else{
        rightMotor.forward(maxSpeed);  // if not, right motor drive forward
      }
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
                leftMotor.freeRun();
                rightMotor.freeRun();
            }

            // the time expired, don't wait anymore
            last_cmd = 0;
        }
    }

    // If the IR follower is on
    if (irFollowerEnabled)
    {
        // read our sensor
        double deg = irFollower.readDegrees();

        // if there is no light
        if (deg == INTEGER_MIN)
        {
            // let the robot come to a stop
            leftMotor.freeRun();
            rightMotor.freeRun();
        }
        else
        {
            // steer it in the direction of the sensor
            steerDegrees(deg);
        }
    }else if(irDetectorEnabled){
      runIRDetector();
    }
    
}

void processCommand(unsigned long code)
{
    switch (code)
    {
        // forwards
        case IR_2:
            leftMotor.forward(fwSpeed);
            rightMotor.forward(fwSpeed);
            break;
        // hard left
        case IR_4:
            leftMotor.backward(fwTurnSpeed);
            rightMotor.forward(fwTurnSpeed);
            break;
        // forward-left
        case IR_1:
            leftMotor.forward(softTurnSpeed);
            rightMotor.forward(fwTurnSpeed);
            break;
        // hard right
        case IR_6:
            leftMotor.forward(fwTurnSpeed);
            rightMotor.backward(fwTurnSpeed);
            break;
        // forward-right
        case IR_3:
            leftMotor.forward(fwTurnSpeed);
            rightMotor.forward(softTurnSpeed);
            break;
        // backwards
        case IR_8:
            leftMotor.backward(fwSpeed);
            rightMotor.backward(fwSpeed);
            break;
        // backwards-left
        case IR_7:
            leftMotor.backward(softTurnSpeed);
            rightMotor.backward(fwTurnSpeed);
            break;
        // backwards-right
        case IR_9:
            leftMotor.backward(fwTurnSpeed);
            rightMotor.backward(softTurnSpeed);
            break;
        // stop
        case IR_5:
            leftMotor.brake();
            rightMotor.brake();
            break;
        case IR_PLAY:
            // turn on the IR Follower
            enableIRFollower();
            break;
        case IR_NEXT:
            // turn on the IR Detector
            enableIRDetector();
            break;
        default:
            break;
    }

    // stop the follower if you pressed one of the keys that make
    // the robot move
    if (code == IR_1 || code == IR_2 || code == IR_3 ||
        code == IR_4 || code == IR_5 || code == IR_6 ||
        code == IR_7 || code == IR_8 || code == IR_9)
    {
        disableIR();
    }
}

void enableIRFollower()
{
    irFollowerEnabled = true;
    irDetectorEnabled = false;
    // turn on the LED
    digitalWrite(ledPin, HIGH);
}

void enableIRDetector()
{
    irDetectorEnabled = true;
    irFollowerEnabled = false;
    // turn on the LED
    digitalWrite(ledPin, HIGH);
}

void disableIR()
{
    irFollowerEnabled = false;
    irDetectorEnabled = false;
    // turn off the LED
    digitalWrite(ledPin, LOW);
}
