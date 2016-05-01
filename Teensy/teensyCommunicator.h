/*
 * teensyCommunicator.h
 *
 *  Created on: Feb 19, 2016
 *      Author: tj
 */

#ifndef TEENSY_TEENSYCOMMUNICATOR_H_
#define TEENSY_TEENSYCOMMUNICATOR_H_

typedef unsigned char uint8_t;
#include <stdint.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdio.h>
#include <unistd.h>

class teensyCommunicator {
public:
	teensyCommunicator();
	virtual ~teensyCommunicator();
	char checkButtonPress();
	int activateLCDBoard();
	int deactivateLCDBoard();

private:
	uint8_t processByte(uint8_t value);
	void  processPacket(uint8_t *packet);
	void initializePacket(uint8_t *packet, uint8_t *packetArray);
	void printPacket(uint8_t *packet);
	char* identifyPacket(uint8_t *packet);

};

#endif /* TEENSY_TEENSYCOMMUNICATOR_H_ */
