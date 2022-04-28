/*
 * Tutorial 2a: Serial Follower
 * 
 * Prints the position of the light read by
 * the IR follower sensor.
 *
 * Requires an assembled robot.
 *
 * created 03 Oct 2013
 * by Blaise Jarrett
 *
 * This example code is in the public domain.
 *
 */

// include our IR Follower code
#include "irfollower.h"

// the digital output pins from the IR sensor
// the rightmost IR Diode
const int followD1 = A0;
const int followD2 = A1;
const int followD3 = A2;
const int followD4 = A3;
const int followD5 = A4;
// the leftmost IR Diode
const int followD6 = A5;

// Create our IR Follower object
IRFollower irFollower(followD1, followD2, followD3,
					  followD4, followD5, followD6);

void setup()
{
	// We're going to print the results over serial
	// Open the serial port
    Serial.begin(9600);
}

void loop()
{ 
	// read our sensor
	double deg = irFollower.readDegrees();

	// if there is no light
	if (deg == INTEGER_MIN)
	{
		Serial.println("No direction");
	}
	else
	{
		// print the reading
		Serial.print("Deg: ");
		Serial.println(deg);
	}

	// wait to avoid flooding the serial monitor
	delay(300);
}
