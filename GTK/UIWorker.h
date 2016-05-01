/*
 * UIWorker.h
 *
 *  Created on: Mar 3, 2016
 *      Author: snelso
 */

#ifndef GTK_UIWORKER_H_
#define GTK_UIWORKER_H_

#include "graphicalFunctions.h"
#include "queueTypes.h"
#include <gtk/gtk.h>
#include "miscTypes.h"
#include <stdlib.h>
#include "backendFunctionality.h"
#include <string>

#define UI_WORKER_PERIOD_MS 150
#define UI_TIMEOUT_MS 30000

class UIWorker {

private:
	//fields
	GAsyncQueue *navQ;
	GAsyncQueue *numQ;
	GAsyncQueue *CANQ;
	GAsyncQueue *backendQ;
	UIState *uistate;
	graphicalFunctions *gf;
	std::string * rentalCode;
	int numberOfUiIterations;

	//functions
	navQData tryPopNavQ();
	numQData tryPopNumQ();
	CANQData tryPopCANQ();
	backendQData tryPopBackendQ();
	void pushToCANQ(int id);
	void initUI();
	void updateUI();
	void manageUiTimeout(bool resetToUi);

public:
	UIWorker(GAsyncQueue *navQ, GAsyncQueue *numQ, GAsyncQueue *CANQ, GAsyncQueue *backendQ, UIState *state, graphicalFunctions *gf);
	~UIWorker();

	void work();
};

#endif /* GTK_UIWORKER_H_ */
