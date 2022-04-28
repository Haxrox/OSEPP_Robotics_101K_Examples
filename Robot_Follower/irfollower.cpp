/*
 * Class file for IR follower.
 * In this file we implement the methods
 * we described in the header file.
 *
 * created 03 Sep 2013
 * by Blaise Jarrett
 *
 * This example code is in the public domain.
 *
 */

// Include our class header
#include "irfollower.h"
// Include the "Arduino" Library
// This is required to give us access to the pinMode
// and digitalRead
#include <Arduino.h>

// the weight value used for IR Diodes 1 and 6
const int IRFollower::cornerWeight = 90;
// the weight value used for IR Diodes 2 and 5
const int IRFollower::innerWeight = 50;
// the wieght value used for IR Diodes 3 and 4
const int IRFollower::forwardWeight = 10;


// Constructor implementation
// Use the ":" shorthand for initializing class members
// This is called a initialization list
IRFollower::IRFollower(uint8_t d1, uint8_t d2, uint8_t d3,
	uint8_t d4, uint8_t d5, uint8_t d6) : d1_(d1), d2_(d2), d3_(d3),
                                          d4_(d4), d5_(d5), d6_(d6)
{
	// set all the IR Diode digital input pins to
    // input mode
    pinMode(d1_, INPUT);
    pinMode(d2_, INPUT);
    pinMode(d3_, INPUT);
    pinMode(d4_, INPUT);
    pinMode(d5_, INPUT);
    pinMode(d6_, INPUT);
}

double IRFollower::readDegrees()
{
	// a boolean for each IR Diode to store their state
	bool f1, f2, f3, f4, f5, f6;

	// read all the states
	// The active state is 0, we want it to be 1
	// so we negate the readings
	f1 = !digitalRead(d1_);
	f2 = !digitalRead(d2_);
	f3 = !digitalRead(d3_);
	f4 = !digitalRead(d4_);
	f5 = !digitalRead(d5_);
	f6 = !digitalRead(d6_);

	// for computing the average we need a sum accumulator
	// and a divisor count
	double sum = 0;
	int divisor = 0;

	// Right half of the sensor (diodes 1, 2, and 3)
	// Right half is a positive direction
	if (f1)
	{
		// add its weight
		sum += cornerWeight;
		// if we used the weight from the diode we will need
		// to average it. Increment the divisor.
		divisor++;
	}
	if (f2)
	{
		// ""
		sum += innerWeight;
		// ""
		divisor++;
	}
	if (f3)
	{
		// ""
		sum += forwardWeight;
		// ""
		divisor++;
	}

	// Left half of the sensor (diodes 4, 5, and 6)
	// Left half is a negative direction
	if (f4)
	{
		// subtract its weigth because we're in the
		// negative direction
		sum -= forwardWeight;
		// if we used the weight from the diode we will need
		// to average it. Increment the divisor.
		divisor++;
	}
	if (f5)
	{
		// ""
		sum -= innerWeight;
		// ""
		divisor++;
	}
	if (f6)
	{
		// ""
		sum -= cornerWeight;
		// ""
		divisor++;
	}

	// if none of the IR Diodes were active we must return
	// a special number to indicate that there's no light
	// on the sensor.
	// We can use the minimum value an integer can hold because
	// its unlikely or impossible that this value will be used.
	if (!f1 && !f2 && !f3 && !f4 && !f5 && !f6)
		return INTEGER_MIN;

	// get the average and return it
	return sum / divisor;
}
