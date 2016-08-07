/*
 * backendCommunicatorThread.h
 *
 *  Created on: Jul 9, 2016
 *      Author: snelso
 */

#ifndef GTK_BACKENDCOMMUNICATORTHREAD_H_
#define GTK_BACKENDCOMMUNICATORTHREAD_H_

#include "MCP25625.h"
//#include "ABRSMsgs.h"
#include "queueTypes.h"
#include <queue>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include "backendCommunicator.h"


struct BackendReturnInputMsg{
	uint16_t bikeIDToReturn;
	int rackNum;
};

struct BackendReturnOutputMsg{
	uint16_t bikeIDToReturn;
	int rackNum;
	bool bikeReturnedSuccess;
};

struct BackendRentInputMsg{
	uint16_t bikeIDToRent;
	int rentalCode;
	int rackNum;
};

struct BackendRentOutputMsg{
	uint16_t bikeIDToRent;
	bool bikeRentalSuccess;
	int rackNum;
};

//void pushToOutputQ(BackendOutputMsg msg);
//bool isInputDataAvailable();

//return functions to be used externally
bool isReturnOutputDataAvailable();
void pushToBackendCommReturnInputQ(BackendReturnInputMsg msg);
BackendReturnOutputMsg popReturnOutputQMsg();


// rental functions to be used externally
bool isRentOutputDataAvailable();
void pushToBackendCommRentInputQ(BackendRentInputMsg msg);
BackendRentOutputMsg popRentOutputQMsg();

void registerBackendCommunicationThreads();

#endif /* GTK_BACKENDCOMMUNICATORTHREAD_H_ */
