/*
 * CANThread.cpp
 *
 *  Created on: May 27, 2016
 *      Author: snelso
 */

#include "CANThread.h"

pthread_t CANThread;
sem_t mutex;
std::queue<CANMsg> rxMsgs;

void pushToBuffer(CANMsg msg){
	sem_wait(&mutex);
	rxMsgs.push(msg);
	sem_post(&mutex);
}

bool isCANDataAvailable(){
	sem_wait(&mutex);
	bool ret = !rxMsgs.empty();
	sem_post(&mutex);
	return ret;
}

CANMsg popFrontCANMsg(){
	sem_wait(&mutex);
	CANMsg msg = rxMsgs.front();
	rxMsgs.pop();
	sem_post(&mutex);
	return msg;
}

void manageRxBuffer() {
	CANMsg msg;
	int bufNum = isRxMsgPending();
	while(bufNum){ //|| count < maxPerIteration){
		readCANMsg(bufNum-1, &msg);
		//printf("should push msg to can q\n");
		//printf("rx manager got CAN msg!...data: %i, %i, %i, %i, %i, %i, %i, %i\n", msg.data[0], msg.data[1], msg.data[2], msg.data[3], msg.data[4], msg.data[5], msg.data[6], msg.data[7]);
		pushToBuffer(msg);
		//count++;
		bufNum = isRxMsgPending();
	}
}


//returns void* so that you can pass data back to calling function if necessary
void* CANThreadRoutine(void* nullPointer){
	while(1){
		manageRxBuffer();
	}
	return NULL ;
}


void registerCanThread(){

	if(0 != sem_init(&mutex, 0, 1)){
		printf("something went wrong with creating semaphore\n");
	}else{
		//printf("semaphore registered correctly\n");
	}

	if(0 != pthread_create(&CANThread, NULL, &CANThreadRoutine, NULL)){
		printf("something went wrong with creating thread\n");
	} else{
		//printf("thread registered correctly\n");
	}
}




