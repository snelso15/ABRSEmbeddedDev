/*
 * TeensyWorker.h
 *
 *  Created on: Mar 3, 2016
 *      Author: snelso
 */

#ifndef GTK_TEENSYWORKER_H_
#define GTK_TEENSYWORKER_H_

#include <gtk/gtk.h>
#include "../Teensy/teensyCommunicator.h"
#include "queueTypes.h"
#include "miscTypes.h"

#include "ABRSDebug.h"

#define TEENSY_WORKER_PERIOD_MS 150
#define BACKLIGHT_TIMEOUT_MS 120000


class TeensyWorker {
private:
	//members
	teensyCommunicator *tc;
	GAsyncQueue *navQ;
	GAsyncQueue *numQ;
	UIState *uistate;
	int numberOfIterations;
	bool bLOn;

	//functions
	void pushToNavQ(char key);
	void pushToNumQ(int key);
	bool tryGetButtonPress(); //returns whether or not a value number keypress occured
	void manageBacklight(bool turnOnBackLight);

public:
	TeensyWorker(teensyCommunicator *tc, GAsyncQueue *navQ, GAsyncQueue *numQ, UIState *state);
	~TeensyWorker();
	void work();
};

#endif /* GTK_TEENSYWORKER_H_ */
