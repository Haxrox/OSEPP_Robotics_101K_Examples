/*
 * Tutorial 3a: Robot Follower
 * 
 * Compiles the Serial Follower and the
 * Motor Driver tutorials to get the robot to follow
 * light detected by the IR Follower sensor.
 *
 * Requires an assembled robot.
 *
 * created 03 Oct 2013
 * by Blaise Jarrett
 *
 * This example code is in the public domain.
 *
 */

// include our motor code
#include "motor.h"
 // include our IR Follower code
#include "irfollower.h"

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

// the digital output pins from the IR sensor
// the rightmost IR Diode
const int followD1 = A0;
const int followD2 = A1;
const int followD3 = A2;
const int followD4 = A3;
const int followD5 = A4;
// the leftmost IR Diode
const int followD6 = A5;

// the fastest the robot can go
const int maxSpeed = 255;
// the max and min +- input to driveDegrees
const int steeringMax = 90;

// Create two Motor objects (instances of our Motor class)
// to drive each motor.
Motor rightMotor(motorRIN1Pin, motorRIN2Pin, motorRENPin);
Motor leftMotor(motorLIN1Pin, motorLIN2Pin, motorLENPin);

// Create our IR Follower object
IRFollower irFollower(followD1, followD2, followD3,
					  followD4, followD5, followD6);

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

void setup() {}

void loop()
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
}
