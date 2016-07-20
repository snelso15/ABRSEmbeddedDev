/*
 * backendCommunicatorThread.cpp
 *
 *  Created on: May 27, 2016
 *      Author: snelso
 */

#include "backendCommunicatorThread.h"

pthread_t backendCommunicatorRentThread;
pthread_t backendCommunicatorReturnThread;
sem_t backendCommReturnMutex;
sem_t backendCommRentMutex;
std::queue<BackendReturnInputMsg> returnInputQ;
std::queue<BackendReturnOutputMsg> returnOutputQ;

std::queue<BackendRentInputMsg> rentInputQ;
std::queue<BackendRentOutputMsg> rentOutputQ;

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

bool isReturnInputDataAvailable(){
	sem_wait(&backendCommReturnMutex);
	bool ret = !returnInputQ.empty();
	sem_post(&backendCommReturnMutex);
	return ret;
}

bool isReturnOutputDataAvailable(){
	sem_wait(&backendCommReturnMutex);
	bool ret = !returnOutputQ.empty();
	sem_post(&backendCommReturnMutex);
	return ret;
}

BackendReturnInputMsg popReturnInputQMsg(){
	sem_wait(&backendCommReturnMutex);
	BackendReturnInputMsg msg = returnInputQ.front();
	returnInputQ.pop();
	sem_post(&backendCommReturnMutex);
	return msg;
}

BackendReturnOutputMsg popReturnOutputQMsg(){
	sem_wait(&backendCommReturnMutex);
	BackendReturnOutputMsg msg = returnOutputQ.front();
	returnOutputQ.pop();
	sem_post(&backendCommReturnMutex);
	return msg;
}

void performBackendCommunicationReturn() {
	while(isReturnInputDataAvailable()){
		BackendReturnInputMsg inpMsg = popReturnInputQMsg();
		BackendReturnOutputMsg msg;
		msg.bikeIDToReturn = inpMsg.bikeIDToReturn;
		msg.bikeReturnedSuccess = (kioskBeginReturn((unsigned int)inpMsg.bikeIDToReturn)) ? true : false;
		pushToReturnOutputQ(msg);
	}
}

//returns void* so that you can pass data back to calling function if necessary
void* BackendCommunicationReturnThreadRoutine(void* nullPointer){
	while(1){
		performBackendCommunicationReturn();
	}
	return NULL ;
}


//////////////////////////////////
// RENTAL Functions             //
//////////////////////////////////
void pushToBackendCommRentInputQ(BackendRentInputMsg msg){
	sem_wait(&backendCommRentMutex);
	rentInputQ.push(msg);
	sem_post(&backendCommRentMutex);
}

void pushToRentOutputQ(BackendRentOutputMsg msg){
	sem_wait(&backendCommRentMutex);
	rentOutputQ.push(msg);
	sem_post(&backendCommRentMutex);
}

bool isRentInputDataAvailable(){
	sem_wait(&backendCommRentMutex);
	bool ret = !rentInputQ.empty();
	sem_post(&backendCommRentMutex);
	return ret;
}

bool isRentOutputDataAvailable(){
	sem_wait(&backendCommRentMutex);
	bool ret = !rentOutputQ.empty();
	sem_post(&backendCommRentMutex);
	return ret;
}

BackendRentInputMsg popRentInputQMsg(){
	sem_wait(&backendCommRentMutex);
	BackendRentInputMsg msg = rentInputQ.front();
	rentInputQ.pop();
	sem_post(&backendCommRentMutex);
	return msg;
}

BackendRentOutputMsg popRentOutputQMsg(){
	sem_wait(&backendCommRentMutex);
	BackendRentOutputMsg msg = rentOutputQ.front();
	rentOutputQ.pop();
	sem_post(&backendCommRentMutex);
	return msg;
}

void performBackendCommunicationRent() {
	while(isRentInputDataAvailable()){
		BackendRentInputMsg inpMsg = popRentInputQMsg();
		BackendRentOutputMsg msg;
		msg.bikeIDToRent = inpMsg.bikeIDToRent;
		msg.bikeRentalSuccess = false;
		msg.rackNum = inpMsg.rackNum;
		int rentalSuccess = kioskBeginRental(inpMsg.rentalCode, inpMsg.bikeIDToRent);
		if(rentalSuccess ==1){
			msg.bikeRentalSuccess = true;
		}
		pushToRentOutputQ(msg);
	}
}

//returns void* so that you can pass data back to calling function if necessary
void* BackendCommunicationRentThreadRoutine(void* nullPointer){
	while(1){
		performBackendCommunicationRent();
	}
	return NULL ;
}

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

	if(0 != pthread_create(&backendCommunicatorReturnThread, NULL, &BackendCommunicationReturnThreadRoutine, NULL)){
		printf("something went wrong with creating rental thread\n");
	} else{
		//printf("thread registered correctly\n");
	}

	if(0 != pthread_create(&backendCommunicatorRentThread, NULL, &BackendCommunicationRentThreadRoutine, NULL)){
		printf("something went wrong with creating return thread\n");
	} else{
		//printf("thread registered correctly\n");
	}
}




