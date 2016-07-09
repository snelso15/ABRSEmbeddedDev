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
};

struct BackendReturnOutputMsg{
	uint16_t bikeIDToReturn;
	bool bikeReturnedSuccess;
};

struct BackendRentInputMsg{
	uint16_t bikeID;
	int rentalCode;
};

struct BackendRentOutputMsg{
	uint16_t bikeIDToRent;
	bool bikeRentalSuccess;
};

//void pushToOutputQ(BackendOutputMsg msg);
//bool isInputDataAvailable();

bool isRentalOutputDataAvailable();
void pushToBackendCommReturnInputQ(BackendReturnInputMsg msg);
BackendReturnOutputMsg popRentalOutputQMsg();
void registerBackendCommunicationThreads();

#endif /* GTK_BACKENDCOMMUNICATORTHREAD_H_ */
