/*
 * PiSPICommands.c
 *
 *  Created on: Jan 28, 2016
 *      Author: Samuel Nelson
 */


#include "PiSPICommands.h"


/*
 * THINGS TO TRY IF NOT WORKING:
 * 1. lower speed in INITSPI call
 * 2. change channel from 0 to 1 in INITSPI
 * 3. make sure wait is long enough in busyWait call in resetCAN function
 *
 * */

int initSPI(){
	//will return -1 on error, or Linux file descriptor
	return wiringPiSPISetup (0, 500000); /* Initialization of SPI component */
}

uint8_t readReg(uint8_t regAddress){
	uint8_t dataBuf[3] = {CMD_READ, regAddress, 0x00}; //last byte doesn't matter, just to provide clocking for response

	//returns an int, not sure what that int is
	wiringPiSPIDataRW (0, dataBuf, 3);
	return dataBuf[2];
}

void writeReg(uint8_t regAddress, uint8_t val){
	uint8_t dataBuf[3] = {CMD_WRITE, regAddress, val};

	//returns an int, not sure what that int is
	wiringPiSPIDataRW (0, dataBuf, 3);
}

void bitModReg(uint8_t regAddress, uint8_t mask, uint8_t byteToWrite){
	uint8_t dataBuf[4] = {CMD_BIT_MOD, regAddress, mask, byteToWrite};

	//returns an int, not sure what that int is
	wiringPiSPIDataRW (0, dataBuf, 4);
}

void resetCAN(){
	uint8_t resetCmd = CMD_RESET;
	wiringPiSPIDataRW (0, &resetCmd, 1);

	//needs calibration
	busyWait(TJ_PI_TWO_SEC_WAIT/2); //wait for device clock to stabilize
}




