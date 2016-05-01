/*
 * workerCallbacks.cpp
 *
 *  Created on: Mar 4, 2016
 *      Author: snelso
 */

#include "workerCallbacks.h"

WorkerContainer *workerContainer = new WorkerContainer;

int uiWorkerCB(gpointer data){
	UIWorker * w = (UIWorker *) data;
	w->work();
	return 1; //callbacks need to return a non zero/negative number to continue registry
}

int teensyWorkerCB(gpointer data){
	TeensyWorker *w = (TeensyWorker *) data;
	w->work();
	return 1; //callbacks need to return a non zero/negative number to continue registry
}

int CANWorkerCB(gpointer data) {
	CANWorker *cw = (CANWorker *) data;
	cw->runWorker();
	return 1; //callbacks need to return a non zero/negative number to continue registry
}

int CANRxCB(gpointer data) {
	CANWorker *cw = (CANWorker *) data;
	cw->runRXBufferManager();
	return 1; //callbacks need to return a non zero/negative number to continue registry
}

void cleanUp() {
	delete workerContainer->uiw;
	delete workerContainer->tw;
	delete workerContainer->cw;
}

void registerWorkers() {
	GAsyncQueue *navQ = g_async_queue_new();
	GAsyncQueue *numQ = g_async_queue_new();
	GAsyncQueue *CANQ = g_async_queue_new();
	GAsyncQueue *backendQ = g_async_queue_new();

	UIState *state = new UIState;
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
	//gdk_threads_add_timeout(RX_MANAGER_PERIOD_MS, CANRxCB, cw);
	gdk_threads_add_idle(CANRxCB, cw);

	workerContainer->uiw = uiw;
	workerContainer->tw = tw;
	workerContainer->cw = cw;
}
