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
#include "CANThread.h"
#include "backendCommunicatorThread.h"

#include "ABRSDebug.h"

#define CAN_WORKER_PERIOD_MS 150
//#define RX_MANAGER_PERIOD_MS 100


struct WorkerContainer{
	UIWorker * uiw;
	TeensyWorker * tw;
	CANWorker * cw;
};

extern bool internetUp;


int uiWorkerCB(gpointer data);
int teensyWorkerCB(gpointer data);
int CANWorkerCB(gpointer data);
int CANRxCB(gpointer data);
void waitForWifi();
void cleanUp();

//create objects and register the callbacks
void registerWorkers();

// added for keyboard button cb
void pushToNumQ(int key);
void key_press_cb(GtkWidget *widget, GdkEventKey *kevent, gpointer data);

#endif /* GTK_WORKERCALLBACKS_H_ */
