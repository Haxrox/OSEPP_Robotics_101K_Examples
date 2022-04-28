/*
 * Tutorial 3b: Robot Remote
 * 
 * This tutorial shows you how to use the remote
 * to control the robot. This is a combination of the
 * Motor Driver and IR Remote LED Repeat tutorials.
 *
 * Use the 1-9 keys to control the robot.
 *
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

void setup()
{
    // enable the receiver
    irrecv.enableIRIn();
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
        default:
            break;
    }
}
