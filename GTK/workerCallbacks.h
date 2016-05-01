/*
 * workerCallbacks.h
 *
 *  Created on: Mar 4, 2016
 *      Author: snelso
 */

#ifndef GTK_WORKERCALLBACKS_H_
#define GTK_WORKERCALLBACKS_H_

#include <gtk/gtk.h>
#include "UIWorker.h"
#include "TeensyWorker.h"
#include "CANWorker.h"

#define CAN_WORKER_PERIOD_MS 300
#define RX_MANAGER_PERIOD_MS 100


struct WorkerContainer{
	UIWorker * uiw;
	TeensyWorker * tw;
	CANWorker * cw;
};

int uiWorkerCB(gpointer data);
int teensyWorkerCB(gpointer data);
int CANWorkerCB(gpointer data);
int CANRxCB(gpointer data);
void cleanUp();

//create objects and register the callbacks
void registerWorkers();

#endif /* GTK_WORKERCALLBACKS_H_ */
