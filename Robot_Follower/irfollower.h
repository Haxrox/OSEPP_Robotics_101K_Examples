/*
 * Header file for the IR follower class
 *
 * created 03 Sep 2013
 * by Blaise Jarrett
 *
 * This example code is in the public domain.
 *
 */

// Include guard
// See: http://en.wikipedia.org/wiki/Include_guard
#ifndef _IRFOLLOWER_H_
#define _IRFOLLOWER_H_

// Include standard ints so we can use specific integer
// types (uint8_t - unsigned 8 bits)
// See: http://www.nongnu.org/avr-libc/user-manual/group__avr__stdint.html
#include <stdint.h>

// the minimum value an integer can hold
// we'll need this for our getDegrees function
#define INTEGER_MIN -32768

// Declare our IR Follower class
// For info on Object Oriented Programming see:
// http://en.wikipedia.org/wiki/Object-oriented_programming
class IRFollower {
	// Access modifier - Make these members public
	// See: http://en.wikipedia.org/wiki/Access_modifiers
	public:
		// Constructor - Creates our IRFollower object from 6 pins
		IRFollower(uint8_t d1, uint8_t d2, uint8_t d3,
			       uint8_t d4, uint8_t d5, uint8_t d6);
		
		double readDegrees();
	// Access modifier - Make these members private
	private:
		// We need instance variables to
		// remember the pins for the sensor.
		uint8_t d1_;
		uint8_t d2_;
		uint8_t d3_;
		uint8_t d4_;
		uint8_t d5_;
		uint8_t d6_;
		// the weight value used for IR Diodes 1 and 6
		static const int cornerWeight;
		// the weight value used for IR Diodes 2 and 5
		static const int innerWeight;
		// the wieght value used for IR Diodes 3 and 4
		static const int forwardWeight;
// The end of our class declaration
};

// The end of our include guard
#endif