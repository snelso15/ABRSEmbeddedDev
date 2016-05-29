/*
 * CommandLineThread.h
 *
 *  Created on: May 28, 2016
 *      Author: snelso
 */

#ifndef ASYNC_COMMANDLINETHREAD_H_
#define ASYNC_COMMANDLINETHREAD_H_

#include <queue>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

class CommandLineThread {
public:
	CommandLineThread(bool hasClones);
	virtual ~CommandLineThread();

private:
	bool hasClones;
	int registerThread();
	virtual void* threadMainFn(void *);
	sem_t mutex;

};







#endif /* ASYNC_COMMANDLINETHREAD_H_ */
