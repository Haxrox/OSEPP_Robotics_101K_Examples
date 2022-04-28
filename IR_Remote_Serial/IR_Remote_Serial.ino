/*
 * Tutorial 2b: IR Remote Serial
 * 
 * Prints the IR remote numberpad keypresses
 * over serial.
 *
 * Requires an assembled robot.
 *
 * created 03 Oct 2013
 * by Blaise Jarrett
 *
 * This example code is in the public domain.
 *
 */

// include Ken Shirriff's IR Remote Library
// You must install this if you havn't already
// https://github.com/shirriff/Arduino-IRremote
#include <IRremote.h>
// include our remote control codes
#include "codes.h"

// the pin the IR Receiver is connected to
const int irPin = 12;

// create an IR Receiver object from the library
IRrecv irrecv(irPin);
// we'll need a decode_results variable to store
// the IR readings
decode_results results;

void setup()
{
    // We're going to print the results over serial
    // Open the serial port
    Serial.begin(9600);

    // enable the receiver
    irrecv.enableIRIn();
}

void loop()
{ 
	// check to see if the receiver has received
    // a command
    if (irrecv.decode(&results))
    {
        // send the command code to our function for
        // processing
        processCommand(results.value);

        // tell the library we're ready to listen for
        // another command
        irrecv.resume();
    }
}

void processCommand(unsigned long code)
{
    // use the switch case to chose what to do
    // with the command
    // http://arduino.cc/en/Reference/SwitchCase
    switch (code)
    {
        // 2
        case IR_2:
            Serial.println("2");
            break;
        // 4
        case IR_4:
            Serial.println("4");
            break;
        // 1
        case IR_1:
            Serial.println("1");
            break;
        // 6
        case IR_6:
            Serial.println("6");
            break;
        // 3
        case IR_3:
            Serial.println("3");
            break;
        // 8
        case IR_8:
            Serial.println("8");
            break;
        // 7
        case IR_7:
            Serial.println("7");
            break;
        // 9
        case IR_9:
            Serial.println("9");
            break;
        // 5
        case IR_5:
            Serial.println("5");
            break;
        case IR_REPEAT:
			Serial.println("Repeat");
        	break;
        default:
        	Serial.println("Other");
            break;
    }
}
