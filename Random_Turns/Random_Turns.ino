/*
 * Tutorial 1b: Random Turns
 * 
 * This tutorial shows you how to
 * get your robot to drive around randomly.
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
// 0 to 255
const int driveSpeed = 200;
// the speed used to turn
// 0 to 255
const int turnSpeed = 200;

// Create two Motor objects (instances of our Motor class)
// to drive each motor.
Motor rightMotor(motorRIN1Pin, motorRIN2Pin, motorRENPin);
Motor leftMotor(motorLIN1Pin, motorLIN2Pin, motorLENPin);

void setup()
{

}

void loop()
{ 
    int randomDrive, randomTurn;
    // See Random definition at:
    // http://arduino.cc/en/Reference/random
    //
    // get a random number for the time we're going
    // to drive forward.
    randomDrive = random(200, 3000);
    // get a random number for the time we're going
    // turn.
    randomTurn = random(200, 1000);

    // drive forward
    rightMotor.forward(driveSpeed);
    leftMotor.forward(driveSpeed);
    // keep driving forward for a random time
    delay(randomDrive);

    // turn
    rightMotor.forward(turnSpeed);
    leftMotor.backward(turnSpeed);
    // keep turning for a random time
    delay(randomTurn);
}
