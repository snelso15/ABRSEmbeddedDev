/*
 * backLightControl.cpp
 *
 *  Created on: Mar 7, 2016
 *      Author: snelso
 */

#include "backLightControl.h"

#include <stdio.h>
#include <wiringPi.h>

//const int ledPin1 = 27;
//const int ledPin2 = 22;
const int backlightPin = 13;

void backLightOn(void)
{
//        //wiringPiSetupGpio();
//        pinMode(ledPin1, OUTPUT);
//        pinMode(ledPin2, OUTPUT);
//
//        printf("backLightOn/n");
//
//		digitalWrite(ledPin2, HIGH);
//		delay(500);
//		digitalWrite(ledPin2, LOW);

	pinMode(backlightPin, OUTPUT);
	digitalWrite(backlightPin, HIGH);
	return;
}

void backLightOff(void)
{
//        //wiringPiSetupGpio();
//        pinMode(ledPin1, OUTPUT);
//        pinMode(ledPin2, OUTPUT);
//
//        printf("backLightOff/n");
//
//		digitalWrite(ledPin1, HIGH);
//		delay(500);
//		digitalWrite(ledPin1, LOW);

	pinMode(backlightPin, OUTPUT);
	digitalWrite(backlightPin, LOW);
	return;
}

