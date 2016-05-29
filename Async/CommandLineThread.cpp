/*
 * CommandLineThread.cpp
 *
 *  Created on: May 28, 2016
 *      Author: snelso
 */

#include "CommandLineThread.h"

CommandLineThread::CommandLineThread() {
	// TODO Auto-generated constructor stub

}

CommandLineThread::CommandLineThread(bool hasClones) {
}

CommandLineThread::~CommandLineThread() {
	// TODO Auto-generated destructor stub
}



int CommandLineThread::registerThread() {
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
