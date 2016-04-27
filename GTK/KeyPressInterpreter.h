/*
 * KeyPressInterpreter.h
 *
 *  Created on: Feb 23, 2016
 *      Author: snelso
 */

#ifndef GTK_KEYPRESSINTERPRETER_H_
#define GTK_KEYPRESSINTERPRETER_H_

#include <gtk/gtk.h>
#include <iostream>
#include "../Teensy/teensyCommunicator.h"
#include "graphicalFunctions.h"

extern graphicalFunctions gF;

struct keyWrapper{
	int numKey;
	char navKey;
};



class KeyPressInterpreter {
public:
	KeyPressInterpreter(GAsyncQueue *q, GAsyncQueue *nq, teensyCommunicator *tcomm);
	virtual ~KeyPressInterpreter();

	//functions
	void processKeyCommands();
	int tryDataPullNumPad();
	char tryDataPullNavigation();
	void resetCodeBuffer();
	int testCode();
	GAsyncQueue * getQueue(int qNum);
	teensyCommunicator * getTC();
	void printQueue();

private:
	//members
	int lastCode[7];
	GAsyncQueue *asynq;
	GAsyncQueue *nasynq;
	teensyCommunicator *tc;

	//functions
	int bumpAdd(int val);

};

#endif /* GTK_KEYPRESSINTERPRETER_H_ */
