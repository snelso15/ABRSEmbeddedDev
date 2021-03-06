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
#include "PowerSystems.h"
#include "CANWorker.h"
#include "backendCommunicator.h"
#include "consoleColor.h"
#include "weatherUpdateThread.h"
#include "networkConnectivityThread.h"
#include "timeThread.h"

//#include "workerCallbacks.h"

extern bool internetUp;

#include "ABRSDebug.h"

#define UI_WORKER_PERIOD_MS 150
#define UI_TIMEOUT_MS 30000
#define WEATHER_TIMEOUT_SOONER_MS 20000
#define WEATHER_TIMEOUT_MS 666666
//#define WEATHER_TIMEOUT_MS 120000
#define UI_TIME_UPDATEUI_TIMEOUT 20000

//struct weather {
//    std::string forecastPhrase[21];
//    std::string forcastFileName[21];
//};

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
	std::string * adminCode;
	int numberOfUiIterations;
	int numberOfWeatherIterations;
	int numberOfTimeUIIterations;
	std::string weatherJSON;
	std::string currentWeatherTemperature;
	std::string currentWeatherForecast;
	std::string todaysHighTemperature;
	std::string todaysLowTemperature;
	std::string weatherIconName;
	bool updateWeatherSooner;
	bool openForRent;

	//functions
	navQData tryPopNavQ();
	numQData tryPopNumQ();
	CANQData tryPopCANQ();
	backendQData tryPopBackendQ();
	void pushToCANQ(int id);
	void initUI();
	void updateUI();
	void manageUiTimeout(bool resetToUi);
	void updateWeather();
	void manageWeatherTimeout();
//	std::string getWeatherFile(std::string const &conditionFromWeatherAPICall);
	int getStringSize(std::string const &inputString);
//	std::string compareStrings(std::string const &inputStringA, std::string const &inputStringB);
	void manageCurrentSystemTimeUIUpdateTimeOut();
	bool OpenForRenting(int openHour, int openMinute, int closeHour, int closeMinute, int currentHour, int currentMinute);


public:
	UIWorker(GAsyncQueue *navQ, GAsyncQueue *numQ, GAsyncQueue *CANQ, GAsyncQueue *backendQ, UIState *state, graphicalFunctions *gf);
	~UIWorker();



	void work();
};

#endif /* GTK_UIWORKER_H_ */
