/*
 * workerCallbacks.cpp
 *
 *  Created on: Mar 4, 2016
 *      Author: snelso
 */

#include "workerCallbacks.h"
#include "CommandLineUtils.h"

WorkerContainer *workerContainer = new WorkerContainer;
bool internetUp;

//int internetPingCB(gpointer data){
//	///////////////
//	//DEBUG
//	logText.append("INTERNET PING CALLBACK FIRED");
//	LOG();
//	///////////////
//	if(state->pageNum == 13){
//
//	}
//
//	if (getPing()[0] != '1') {
//		internetUp = false;
//	} else{
//		internetUp = true;
//	}
//
//	return 1; //callbacks need to return a non zero/negative number to continue registry
//}

int uiWorkerCB(gpointer data){
	///////////////
	//DEBUG
	logText.append("UIWORKER CALLBACK FIRED");
	LOG();
	///////////////

	UIWorker * w = (UIWorker *) data;
	w->work();
	return 1; //callbacks need to return a non zero/negative number to continue registry
}

int teensyWorkerCB(gpointer data){

	///////////////
	//DEBUG
	logText.append("teensyWorker CALLBACK FIRED");
	LOG();
	///////////////

	TeensyWorker *w = (TeensyWorker *) data;
	w->work();
	return 1; //callbacks need to return a non zero/negative number to continue registry
}

int CANWorkerCB(gpointer data) {
	///////////////
	//DEBUG
	logText.append("CANWORKER CALLBACK FIRED");
	LOG();
	///////////////

	CANWorker *cw = (CANWorker *) data;
	cw->runWorker();
	return 1; //callbacks need to return a non zero/negative number to continue registry
}

int CANRxCB(gpointer data) {
	///////////////
	//DEBUG
	logText.append("CANWORKER CALLBACK FIRED");
	LOG();
	///////////////
	CANWorker *cw = (CANWorker *) data;
	cw->runRXBufferManager();
	return 1; //callbacks need to return a non zero/negative number to continue registry
}

void cleanUp() {
	delete workerContainer->uiw;
	delete workerContainer->tw;
	delete workerContainer->cw;
}


/*
 * MAKING THIS A GLOBAL FOR keyboard callback
 *
 ******************* */
 UIState *state = new UIState;
 GAsyncQueue *numQ = g_async_queue_new();
/****************************
 *
 *
 *
 */


void key_press_cb(GtkWidget *widget, GdkEventKey *kevent, gpointer data)
{
	///////////////
	//DEBUG
	logText.clear();
	logText.append("---------------------------------------------------");
	logText.append("TEMP KEYBOARD CALLBACK FIRED");
	LOG();
	///////////////

	int inNum = -1;

	gint keyVal = kevent->keyval;
	switch (keyVal){
		case '0':
		{
			inNum = 0;
			break;
		}
		case '1':
		{
			inNum = 1;
			break;
		}
		case '2':
		{
			inNum = 2;
			break;
		}
		case '3':
		{
			inNum = 3;
			break;
		}
		case '4':
		{
			inNum = 4;
			break;
		}
		case '5':
		{
			inNum = 5;
			break;
		}
		case '6':
		{
			inNum = 6;
			break;
		}
		case '7':
		{
			inNum = 7;
			break;
		}
		case '8':
		{
			inNum = 8;
			break;
		}
		case '9':
		{
			inNum = 9;
			break;
		}
	}

	if(inNum != -1){
		//only accept number input if on appropriate screen
		if(state->pageNum == 3){
			//printf("Received a number input on the correct page: %i\n", inNum); //TODO - debug, remove
			pushToNumQ(inNum);
			//return true;
		}
	}
}

void pushToNumQ(int key){
	numQData *numQMsg = new numQData;
	numQMsg->key = key;
	numQMsg->dataAvailable = true;
	g_async_queue_push(numQ, (gpointer)numQMsg);
}


void waitForWifi(){
	int wifiDownSecondsCounter = 0;
	while (getPing()[0] != '1') {
		wifiDownSecondsCounter++;
		sleep(1);
		printf("%d: Internet Down, Retry in 1 second\n", wifiDownSecondsCounter);
		if (wifiDownSecondsCounter == 20)
		{
			// call start_wifi.sh to reconnect to YCP network
			printf("initiating a network reconnect\n");
			reConnectToNetwork();
			wifiDownSecondsCounter = 0;
		}
	}
//	// check a second time
//	sleep(1);
//	while (getPing()[0] != '1') {
//		sleep(1);
//		printf("Internet Down, Retry in 1 second\n");
//	}
	internetUp = true;
}

void registerWorkers() {
	GAsyncQueue *navQ = g_async_queue_new();
	GAsyncQueue *CANQ = g_async_queue_new();
	GAsyncQueue *backendQ = g_async_queue_new();

	initLog();

	state->pageNum = 1;
	graphicalFunctions *gf = new graphicalFunctions();
	teensyCommunicator *tc = new teensyCommunicator();

	UIWorker *uiw = new UIWorker(navQ, numQ, CANQ, backendQ, state, gf);
	TeensyWorker *tw = new TeensyWorker(tc, navQ, numQ, state);
	CANWorker *cw = new CANWorker(CANQ, navQ);

	//callback registry
	gdk_threads_add_timeout(UI_WORKER_PERIOD_MS, uiWorkerCB, uiw);
	gdk_threads_add_timeout(TEENSY_WORKER_PERIOD_MS, teensyWorkerCB, tw);
	gdk_threads_add_timeout(CAN_WORKER_PERIOD_MS, CANWorkerCB, cw);

//	gdk_threads_add_timeout(5000, internetPingCB, NULL);
	gdk_threads_add_timeout(200, CANRxCB, cw);

	//gdk_threads_add_idle(CANRxCB, cw);
	//gdk_threads_add_timeout(100 ,CANRxCB, cw);

	g_signal_connect(G_OBJECT(gf->getMainWindow()), "key_press_event", G_CALLBACK(&key_press_cb), NULL);

	workerContainer->uiw = uiw;
	workerContainer->tw = tw;
	workerContainer->cw = cw;
}
