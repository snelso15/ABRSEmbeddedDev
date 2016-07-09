/*
 * backendCommunicatorThread.cpp
 *
 *  Created on: May 27, 2016
 *      Author: snelso
 */

#include "backendCommunicatorThread.h"

pthread_t backendCommunicatorRentalThread;
sem_t backendCommReturnMutex;
sem_t backendCommRentMutex;
std::queue<BackendReturnInputMsg> returnInputQ;
std::queue<BackendReturnOutputMsg> returnOutputQ;


//////////////////////////////////
// Return Functions             //
//////////////////////////////////
void pushToBackendCommReturnInputQ(BackendReturnInputMsg msg){
	sem_wait(&backendCommReturnMutex);
	returnInputQ.push(msg);
	sem_post(&backendCommReturnMutex);
}

void pushToReturnOutputQ(BackendReturnOutputMsg msg){
	sem_wait(&backendCommReturnMutex);
	returnOutputQ.push(msg);
	sem_post(&backendCommReturnMutex);
}

bool isRentalInputDataAvailable(){
	sem_wait(&backendCommReturnMutex);
	bool ret = !returnInputQ.empty();
	sem_post(&backendCommReturnMutex);
	return ret;
}

bool isRentalOutputDataAvailable(){
	sem_wait(&backendCommReturnMutex);
	bool ret = !returnOutputQ.empty();
	sem_post(&backendCommReturnMutex);
	return ret;
}

BackendReturnInputMsg popRentalInputQMsg(){
	sem_wait(&backendCommReturnMutex);
	BackendReturnInputMsg msg = returnInputQ.front();
	returnInputQ.pop();
	sem_post(&backendCommReturnMutex);
	return msg;
}

BackendReturnOutputMsg popRentalOutputQMsg(){
	sem_wait(&backendCommReturnMutex);
	BackendReturnOutputMsg msg = returnOutputQ.front();
	returnOutputQ.pop();
	sem_post(&backendCommReturnMutex);
	return msg;
}

void performBackendCommunicationRental() {
	while(isRentalInputDataAvailable()){
		BackendReturnInputMsg inpMsg = popRentalInputQMsg();
		BackendReturnOutputMsg msg;
		msg.bikeIDToReturn = inpMsg.bikeIDToReturn;
		msg.bikeReturnedSuccess = (kioskBeginReturn((unsigned int)inpMsg.bikeIDToReturn)) ? true : false;
		pushToReturnOutputQ(msg);
	}
}

//returns void* so that you can pass data back to calling function if necessary
void* BackendCommunicationRentalThreadRoutine(void* nullPointer){
	while(1){
		performBackendCommunicationRental();
	}
	return NULL ;
}

//////////////////////////////////
// RENTAL Functions             //
//////////////////////////////////

void registerBackendCommunicationThreads(){

	if(0 != sem_init(&backendCommReturnMutex, 0, 1)){
		printf("something went wrong with creating backend return semaphore\n");
	}else{
		//printf("semaphore registered correctly\n");
	}

	if(0 != sem_init(&backendCommRentMutex, 0, 1)){
		printf("something went wrong with creating backend rent semaphore\n");
	}else{
		//printf("semaphore registered correctly\n");
	}

	if(0 != pthread_create(&backendCommunicatorRentalThread, NULL, &BackendCommunicationRentalThreadRoutine, NULL)){
		printf("something went wrong with creating thread\n");
	} else{
		//printf("thread registered correctly\n");
	}
}




