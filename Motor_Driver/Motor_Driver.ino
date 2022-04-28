/*
 * Tutorial 1a: Motor Driver
 * 
 * Drives two motors forward.
 *
 * The circuit:
 *  - 6 pins connected to the L298 Motor Driver
 *
 * created 27 Sep 2013
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
const int motorRIN2Pin = 9;
// The Right Motors IN2 Pin
// Labelled on the motor driver as IN2
const int motorRIN1Pin = 8;

// The Left Motors Enable Pin
// Labelled on the motor driver as ENB
// Be carful of PWM Timers
const int motorLENPin = 7;
// The Left Motors IN1 Pin
// Labelled on the motor driver as IN3
const int motorLIN2Pin = 6;
// The Left Motors IN2 Pin
// Labelled on the motor driver as IN4
const int motorLIN1Pin = 5;


// Create two Motor objects (instances of our Motor class)
// to drive each motor.
Motor rightMotor(motorRIN1Pin, motorRIN2Pin, motorRENPin);
Motor leftMotor(motorLIN1Pin, motorLIN2Pin, motorLENPin);

void setup()
{
    // Let's just make them go forward to test the
    // motors and the Motor class.
    rightMotor.forward(200);
    leftMotor.backward(200);
}

void loop()
{ 
    
}

