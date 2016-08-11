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

//int CANRxCB(gpointer data) {
//	///////////////
//	//DEBUG
//	logText.append("CANWORKER CALLBACK FIRED");
//	LOG();
//	///////////////
//	CANWorker *cw = (CANWorker *) data;
//	cw->runRXBufferManager();
//	return 1; //callbacks need to return a non zero/negative number to continue registry
//}

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
 GAsyncQueue *navQ = g_async_queue_new();
/****************************
 *
 *
 *
 */

 void pushToNavQ(char key){
 	navQData *navQMsg = new navQData;
 	navQMsg->key = key;
 	navQMsg->dataAvailable = true;
 	g_async_queue_push(navQ, (gpointer)navQMsg);
 }

void key_press_cb(GtkWidget *widget, GdkEventKey *kevent, gpointer data)
{
	///////////////
	//DEBUG
	logText.clear();
	logText.append("---------------------------------------------------");
	logText.append("TEMP KEYBOARD CALLBACK FIRED");
	LOG();
	///////////////
	printf("keypress callbacak fired! \n");
	gint keyVal = kevent->keyval;

	int inNum = -1;
	char inChar = 'z';

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
		case 'A':
		{
			inChar = keyVal;

			break;
		}
		case 'B':
		{
			inChar = keyVal;
			break;
		}
		case 'C':
		{
			inChar = keyVal;
			break;
		}
		case 'D':
		{
			inChar = keyVal;
			break;
		}
		case 'E':
		{
			inChar = keyVal;
			break;
		}
		case 'F':
		{
			inChar = keyVal;
			break;
		}
		case 'G':
		{
			inChar = keyVal;
			break;
		}
		case 'H':
		{
			inChar = keyVal;
			break;
		}
		/*
		case 0x23:
		{
			//inChar = 'P';
			inNum = 0;
			break;
		}
		case 0x2A:
		{
			//inChar = 'S';
			inNum = 0;
			break;
		}
		*/
		case 0x23:
		{
			if (state->pageNum == 9)
				inNum = 0;
			else if (state->pageNum == 3)
				inChar = 'P';
			break;
		}
		case 0x2A:
		{
			if (state->pageNum == 9)
				inNum = 0;
			else if (state->pageNum == 3)
				inChar = 'S';
			break;
		}
		default:
			break;
	}
	if(inNum != -1){
		//only accept number input if on appropriate screen
//		if(uistate->pageNum == 3){
		if(state->pageNum == 3 || state->pageNum == 10){   // accept numkeypad presses if on 'info' or 'input rental code' pages
			//printf("Received a number input on the correct page: %i\n", inNum); //TODO - debug, remove

			////DEBUG
			logText.append("teensy.cpp -- pushing ");
			//logText.append(&inChar);
			appendInt(inNum);
			logText.append(" to numQ");
			LOG();
			/////////////////


			pushToNumQ(inNum);
		}
		else if(state->pageNum == 9)  // if a num key was pressed and we are at the idle screen, fake a nav press
		{

			////DEBUG
			logText.append("teensy.cpp -- got number in start screen, pushing a");
			//logText.append(&inChar);
			//appendInt(inNum);
			logText.append(" to navQ");
			LOG();
			/////////////////

			pushToNavQ('a');
		}
	}

	if(inChar != 'z'){
//		if (uistate->pageNum == 12)//admin page
//		{
//			printf("pageNum is 12\n");
//			g_print("pageNum is 12\n");
//			// TODO insert check for admin screen
//			switch (inChar)
//			{
//			case 'A': // turn on driver board
//				g_print("turn on driver board\n");
//				printf("turn on driver board\n");
//				tc->activateLCDBoard();
//				break;
//			case 'B': // turn on backlight
//				g_print("turn on backlight\n");
//				backLightOn();
//				break;
//			case 'E': // turn off driver board
//				g_print("turn off driver board\n");
//				tc->deactivateLCDBoard();
//				break;
//			case 'F': // turn off backlight
//				g_print("turn off backlight\n");
//				backLightOff();
//				break;
//			default:
//				break;
//			}
//		}

		////DEBUG
		logText.append("teensy.cpp -- pushing ");
		appendChar(inChar);
		logText.append(" to navQ");
		LOG();
		/////////////////
		printf("keypress callback writing char: %c! to navQ \n", inChar);

		pushToNavQ(inChar);
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

	//NO!! USE THREAD INSTREAAD
	//gdk_threads_add_timeout(200, CANRxCB, cw);
	registerCanThread();
	registerBackendCommunicationThreads();
	registerWeatherUpdateThread();
	registerInternetConnectionStatusUpdateThread();
	registerTimeStatusThreadUpdateThread();

	//gdk_threads_add_idle(CANRxCB, cw);
	//gdk_threads_add_timeout(100 ,CANRxCB, cw);

	g_signal_connect(G_OBJECT(gf->getMainWindow()), "key_press_event", G_CALLBACK(&key_press_cb), NULL);

	workerContainer->uiw = uiw;
	workerContainer->tw = tw;
	workerContainer->cw = cw;
}
