/*
 * CANThread.cpp
 *
 *  Created on: May 27, 2016
 *      Author: snelso
 */


#include "CANThread.h"

pthread_t CANThread;
sem_t mutex;


void manageRxBuffer() {
	CANMsg msg;
	int bufNum = isRxMsgPending();
	while(bufNum){ //|| count < maxPerIteration){
		readCANMsg(bufNum-1, &msg);
		//printf("should push msg to can q\n");
		printf("rx manager got CAN msg!...data: %i, %i, %i, %i, %i, %i, %i, %i\n", msg.data[0], msg.data[1], msg.data[2], msg.data[3], msg.data[4], msg.data[5], msg.data[6], msg.data[7]);
//		rxMsgs->push(msg);
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
	}

	if(0 != pthread_create(&CANThread, NULL, &CANThreadRoutine, NULL)){
		printf("something went wrong with creating threads\n");
	}
}




