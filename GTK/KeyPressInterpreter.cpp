/*
 * KeyPressInterpreter.cpp
 *
 *  Created on: Feb 23, 2016
 *      Author: snelso
 */

#include "KeyPressInterpreter.h"

KeyPressInterpreter::KeyPressInterpreter(GAsyncQueue *q, GAsyncQueue *nq, teensyCommunicator *tcomm) {
	lastCode[0] = -1;
	lastCode[1] = -1;
	lastCode[2] = -1;
	lastCode[3] = -1;
	lastCode[4] = -1;
	lastCode[5] = -1;
	lastCode[6] = -1;
	asynq = q;
	nasynq = nq;
	tc = tcomm;
}

KeyPressInterpreter::~KeyPressInterpreter() {}

int KeyPressInterpreter::testCode(){
	if( lastCode[0] == 9 &&
		lastCode[1] == 0 &&
		lastCode[2] == 3 &&
		lastCode[3] == 5 &&
		lastCode[4] == 7 &&
		lastCode[5] == 6 &&
		lastCode[6] == 8 )
		return 1;
	else return 0;
}



int KeyPressInterpreter::tryDataPullNumPad(){
	g_async_queue_ref(asynq);
	gpointer data = g_async_queue_try_pop(asynq);
	g_async_queue_unref(asynq);
	keyWrapper *p_kw = NULL;
	int key = -1;
	if(data != NULL){
		p_kw = (keyWrapper *)(data);
		key = p_kw->numKey;
		bumpAdd(key);
	}
	return key;
}

char KeyPressInterpreter::tryDataPullNavigation()
{
	g_async_queue_ref(nasynq);
	gpointer data = g_async_queue_try_pop(nasynq);
	g_async_queue_unref(nasynq);
	keyWrapper *p_n_kw = NULL;
	char key = 'z';
	if(data != NULL){
		p_n_kw = (keyWrapper *)(data);
		key = p_n_kw->navKey;
		// callback for UI
		printf("=======%c=========UPDATE UI================\n", key);
		gF.printSomething();
		gF.updateUI(key);
	}
	return key;
}

int KeyPressInterpreter::bumpAdd(int val){
	lastCode[6] = lastCode[5];
	lastCode[5] = lastCode[4];
	lastCode[4] = lastCode[3];
	lastCode[3] = lastCode[2];
	lastCode[2] = lastCode[1];
	lastCode[1] = lastCode[0];
	lastCode[0] = val;
}

void KeyPressInterpreter::resetCodeBuffer(){
	lastCode[0] = -1;
	lastCode[1] = -1;
	lastCode[2] = -1;
	lastCode[3] = -1;
	lastCode[4] = -1;
	lastCode[5] = -1;
	lastCode[6] = -1;
}

GAsyncQueue * KeyPressInterpreter::getQueue(int qNum){
	if (qNum == 1)
		return asynq;
	return nasynq;
}

teensyCommunicator * KeyPressInterpreter::getTC(){
	return tc;
}

void KeyPressInterpreter::printQueue(){
	printf("Queue: %i, %i, %i, %i, %i, %i, %i\n", lastCode[0], lastCode[1], lastCode[2], lastCode[3], lastCode[4], lastCode[5], lastCode[6]);
}

