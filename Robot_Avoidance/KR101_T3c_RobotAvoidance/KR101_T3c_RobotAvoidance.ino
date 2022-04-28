/*
 * Tutorial : Robot Detector
 * 
 * This tutorial shows you how to
 * get your robot to avoid running into objects.
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

// The Right Motors Enable Pin
// Labelled on the motor driver as ENA
// Be carful of PWM Timers
const int motorRENPin = 10;
// The Right Motors IN1 Pin
// Labelled on the motor driver as IN1
const int motorRIN1Pin = 9;
// The Right Motors IN2 Pin
// Labelled on the motor driver as IN2
const int motorRIN2Pin = 8;

// The Left Motors Enable Pin
// Labelled on the motor driver as ENB
// Be carful of PWM Timers
const int motorLENPin = 5;
// The Left Motors IN1 Pin
// Labelled on the motor driver as IN3
const int motorLIN1Pin = 7;
// The Left Motors IN2 Pin
// Labelled on the motor driver as IN4
const int motorLIN2Pin = 6;

// left IR detector sensor to digital pin 2
const int Left_IRDetector_Pin = 1;
// right IR detector sensor to digital pin 3
const int Right_IRDetector_Pin = 1;

// the speed used to drive forward
// 0 to 255
const int driveSpeed = 255;
// the speed used to turn
// 0 to 255
const int turnSpeed = 200;

// Create two Motor objects (instances of our Motor class)
// to drive each motor.
Motor rightMotor(motorRIN1Pin, motorRIN2Pin, motorRENPin);
Motor leftMotor(motorLIN1Pin, motorLIN2Pin, motorLENPin);

void setup()
{
    // Set each IR detectors sensor pin to digital input
    pinMode(Left_IRDetector_Pin, 1);
    pinMode(Right_IRDetector_Pin,1);
}

void loop()
{ 
    // read our left and right IR Detector sensors
    int Left_IRDetector = digitalRead(Left_IRDetector_Pin);
    int Right_IRDetector = digitalRead(Right_IRDetector_Pin);

    if(Left_IRDetector&&Right_IRDetector)// if both of our sensors are active
    {
        // drive both motors backward at drive speed
        rightMotor.backward(50); 
        leftMotor.backward(50);
    }
    else if(Left_IRDetector||Right_IRDetector)
    {
        // turn at turn speed
        rightMotor.backward(50);
        leftMotor.forward(50);
    }
    else
    {
        // drive both motors forward at drive speed
        rightMotor.forward(100);
        leftMotor.forward(100); 
    }
}
    

