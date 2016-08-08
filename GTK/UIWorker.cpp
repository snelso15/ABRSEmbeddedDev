/*
 * UIWorker.cpp
 *
 *  Created on: Mar 3, 2016
 *      Author: snelso
 */

#include "UIWorker.h"
#include <string>

bool processingRental = false;

UIWorker::UIWorker(GAsyncQueue *navQ, GAsyncQueue *numQ, GAsyncQueue *CANQ, GAsyncQueue *backendQ, UIState * state, graphicalFunctions *gf){
	this->gf = gf;
	this->navQ = navQ;
	this->numQ = numQ;
	this->CANQ = CANQ;
	this->backendQ = backendQ;
	this->uistate = state;
	this->rentalCode = new std::string;
	this->adminCode = new std::string;
	init_battery_comms();
	initUI();

	numberOfWeatherIterations = 0;
//
	weatherJSON = "";
	currentWeatherTemperature = "";
	currentWeatherForecast = "";
	todaysHighTemperature = "";
	todaysLowTemperature = "";
	weatherIconName = "";

	updateWeatherSooner = false;
//
	updateWeather();
}

UIWorker::~UIWorker() {
	// TODO Auto-generated destructor stub
}

void UIWorker::initUI() {
	gf->buildUI();
	gf->connectSignals();
}

//This is the function that updates the UI from a teensy char.  more in-depth logic
//required (switch statement probably) to handle UI navigation cases
void UIWorker::updateUI(){

//	///////////////
//	//DEBUG
//	logText.append("UpdateUI called");
//	LOG();
//	///////////////

	int uiScreenNum = uistate->pageNum;
	///////////////
//	//DEBUG
	logText.append("UIWorker.cpp -- updateUI()");
	LOG();
//	///////////////

	if ((uiScreenNum != 3) && (uiScreenNum != 7))rentalCode->clear();
	if ((uiScreenNum != 10)) adminCode->clear();

	navQData navQMsg = tryPopNavQ();

	//nested ifs or case statement to inspect uiScreenNum variable and update accordingly
	if(isReturnOutputDataAvailable()){
		BackendReturnOutputMsg backendOutputmsg = popReturnOutputQMsg();
		if(backendOutputmsg.bikeReturnedSuccess){
			if(uiScreenNum == 0  || uiScreenNum == 9 || uiScreenNum == 4){
				gf->setuiPageNum(gf->drawReturnPage(backendOutputmsg.bikeIDToReturn, backendOutputmsg.rackNum));
				printf("UIWORKER saw msg from BackendCommsThread that a bike return proccessed successfully, should draw return page.\n");
			}
		} else{
			printf("UIWORKER saw msg from BackendCommsThread that a bike return processed but failed\n");
		}
	}

	if(navQMsg.dataAvailable){
		if(navQMsg.key == 'r'){
			if(uiScreenNum == 0  || uiScreenNum == 9 || uiScreenNum == 4){
	//			gf->setuiPageNum(gf->drawReturnPage(navQMsg.bikeID));
	//			///////////////
	//			//DEBUG
	//			logText.append("UIWorker.cpp -- updateUI()");
	//			LOG();
	//			logText.append("navQMsg.bikeID:");
	//			appendInt(navQMsg.bikeID);
	//			LOG();
	//			///////////////
				// code for 'CLEAR' button on Keypad
			}
		} else if (navQMsg.key == 'A' && uiScreenNum == 0) { // going to rent, check for network first
			if (getConnectedInternetStatus()) {
				// if no bikes force screen 8 with no bikes available (Code 3)
				bool validBikeHeld = false;
				for (int i = 1; i <= NUM_RACKS; i++){
					if(globalCANStat->getRack(i)->bikePresent && globalCANStat->getRack(i)->bikeIdValid){
						validBikeHeld = true;
						break;
					}
				}
				if (!validBikeHeld) {
					gf->setuiPageNum(gf->drawFailurePage(3));
				} else{
					gf->setuiPageNum(gf->drawOnlineCodePage());
				}
			} else {
				gf->setuiPageNum(gf->drawNetworkConnectionDownPage());
			}
		} else if (navQMsg.key == 'E' && uiScreenNum == 0) { // going to rent, check for network first
			if (getConnectedInternetStatus()) {
				gf->setuiPageNum(gf->drawReportProblemPage());
			} else {
				gf->setuiPageNum(gf->drawNetworkConnectionDownPage());
			}
		} else if (navQMsg.key == 'S' && uiScreenNum == 3) {
			rentalCode->clear();
			gf->setuiPageNum(gf->drawOnlineCodePage(*rentalCode));
		} else if (navQMsg.key == 'P' && uiScreenNum == 3 && (rentalCode->length() == 4) ) {  // code for 'ENTER' button on Keypad
			gf->setuiPageNum(gf->drawSubmitPage());
		} else if ((navQMsg.key == 'E' || navQMsg.key == 'e') && uiScreenNum == 3 && (rentalCode->length() == 4) ) {  // code for 'SUBMIT' button in Online Code Menu
			gf->setuiPageNum(gf->drawSubmitPage());
		} else if (navQMsg.key != 'r'){
			////DEBUG
			logText.append("uiworker.cpp --updating UI according to: ");
			//logText.append(&inChar);
			appendChar(navQMsg.key);
			LOG();
			/////////////////

			gf->updateUI(navQMsg.key);
			numberOfUiIterations = 0;
		}
//		///////////////
//		//DEBUG
//		logText.append("UIWorker.cpp -- updateUI()");
//		LOG();
//		logText.append("navQMsg.key:");
//		appendChar(navQMsg.key);
//		LOG();
//		///////////////
	}

	//check to see if ui update should send a CANQ msg - probably nested in above cases
	numQData numQMsg = tryPopNumQ();
	if(numQMsg.dataAvailable){
		//printf("pushing %i to canq...\n", numQMsg.key);
		//pushToCANQ(numQMsg.key);
		if(uiScreenNum == 10) {  // in INFO, check for admin code  //TODO
			if (adminCode->length() == 4) {
				if (adminCode->compare("2486") == 0) // code is equal, go to admin now
				{
					gf->setuiPageNum(gf->drawAdminPage());
				}
			} else {  // code is less than 4, add another number
				char character[2];
				sprintf(character,"%d",numQMsg.key);
				adminCode->append(character);
				printf("from UI worker.. code is : %s\n", adminCode->data());
			}

		}else {  //otherwise you can only be in OnlineRentalCode Page


			if (rentalCode->length() < 4)
			{
				char character[2];
				sprintf(character,"%d",numQMsg.key);
				rentalCode->append(character);
				printf("from UI worker.. code is : %s\n", rentalCode->data());
				gf->setuiPageNum(gf->drawOnlineCodePage(*rentalCode));
			}
			else
			{
				printf("rentalCode is greater than or equal to length 4\n");
				printf("from UI worker.. code is : %s\n", rentalCode->data());
			}
			//printf("rentalCode Length = %d\n", rentalCode->length());
			numberOfUiIterations = 0;
		}
//		///////////////
//		//DEBUG
//		logText.append("UIWorker.cpp -- updateUI()");
//		LOG();
//		logText.append("rentalCode->data():");
//		logText.append(rentalCode->data());
//		LOG();
//		///////////////
	}

	//check to see if ui update should send a backendQ msg - probably nested in above cases

	if (uiScreenNum == 7) // in processing rental screen
	{
		//printf("PROC RENTAL SCREEN WITH TWIRLY THING\r\n");
		if(!processingRental){
			processingRental = true;
			printf("IN PROCESSING SCREEN:\n\r");
			//int number = std::stoi(rentalCode,nullptr,0);
			int number = atoi(rentalCode->data());
			//printf("int rentalcode is %d\n", number);

			int rentalSuccess = 0;
			unsigned int bikeID = 0;
			int bikeUnlockRack = 0;

			printf("rack 1:  id - %x,  present - %d, valid - %d\r\n",globalCANStat->getRack(1)->heldBikeId, globalCANStat->getRack(1)->bikePresent , globalCANStat->getRack(1)->bikeIdValid);
			printf("rack 2:  id - %x,  present - %d, valid - %d\r\n",globalCANStat->getRack(2)->heldBikeId, globalCANStat->getRack(2)->bikePresent , globalCANStat->getRack(2)->bikeIdValid);
			printf("rack 3:  id - %x,  present - %d, valid - %d\r\n",globalCANStat->getRack(3)->heldBikeId, globalCANStat->getRack(3)->bikePresent , globalCANStat->getRack(3)->bikeIdValid);
			printf("rack 4:  id - %x,  present - %d, valid - %d\r\n",globalCANStat->getRack(4)->heldBikeId, globalCANStat->getRack(4)->bikePresent , globalCANStat->getRack(4)->bikeIdValid);
			printf("rack 5:  id - %x,  present - %d, valid - %d\r\n",globalCANStat->getRack(5)->heldBikeId, globalCANStat->getRack(5)->bikePresent , globalCANStat->getRack(5)->bikeIdValid);

			if(globalCANStat->getRack(1)->bikePresent && globalCANStat->getRack(1)->bikeIdValid){
				bikeID = globalCANStat->getRack(1)->heldBikeId;
				BackendRentInputMsg msg;
				msg.rackNum = 1;
				msg.bikeIDToRent = bikeID;
				msg.rentalCode = number;
				printf("telling thread running backencommrent to rent bicycle # %x in rack # %d\r\n", msg.bikeIDToRent , msg.rackNum);
				pushToBackendCommRentInputQ(msg);
	//			rentalSuccess = kioskBeginRental(number, bikeID);
	//			if(rentalSuccess) pushToCANQ(1);
	//			bikeUnlockRack = 1;
			}
			else if(globalCANStat->getRack(2)->bikePresent && globalCANStat->getRack(2)->bikeIdValid){
				bikeID = globalCANStat->getRack(2)->heldBikeId;
				BackendRentInputMsg msg;
				msg.rackNum = 2;
				msg.bikeIDToRent = bikeID;
				msg.rentalCode = number;
				printf("telling thread running backencommrent to rent bicycle # %x in rack # %d\r\n", msg.bikeIDToRent , msg.rackNum);
				pushToBackendCommRentInputQ(msg);
	//			rentalSuccess = kioskBeginRental(number, bikeID);
	//			if(rentalSuccess) pushToCANQ(2);
	//			bikeUnlockRack = 2;
			}
			else if(globalCANStat->getRack(3)->bikePresent && globalCANStat->getRack(3)->bikeIdValid){
				bikeID = globalCANStat->getRack(3)->heldBikeId;
				BackendRentInputMsg msg;
				msg.rackNum = 3;
				msg.bikeIDToRent = bikeID;
				msg.rentalCode = number;
				printf("telling thread running backencommrent to rent bicycle # %x in rack # %d\r\n", msg.bikeIDToRent , msg.rackNum);
				pushToBackendCommRentInputQ(msg);
	//			rentalSuccess = kioskBeginRental(number, bikeID);
	//			bikeUnlockRack = 3;
	//			if(rentalSuccess) pushToCANQ(3);
			}
			else if(globalCANStat->getRack(4)->bikePresent && globalCANStat->getRack(4)->bikeIdValid){
				bikeID = globalCANStat->getRack(4)->heldBikeId;
				BackendRentInputMsg msg;
				msg.rackNum = 4;
				msg.bikeIDToRent = bikeID;
				msg.rentalCode = number;
				printf("telling thread running backencommrent to rent bicycle # %x in rack # %d\r\n", msg.bikeIDToRent , msg.rackNum);
				pushToBackendCommRentInputQ(msg);
	//			rentalSuccess = kioskBeginRental(number, bikeID);
	//			bikeUnlockRack = 4;
	//			if(rentalSuccess) pushToCANQ(4);
			}
			else if(globalCANStat->getRack(5)->bikePresent && globalCANStat->getRack(5)->bikeIdValid){
				bikeID = globalCANStat->getRack(5)->heldBikeId;
				BackendRentInputMsg msg;
				msg.rackNum = 5;
				msg.bikeIDToRent = bikeID;
				msg.rentalCode = number;
				printf("telling thread running backencommrent to rent bicycle # %x in rack # %d\r\n", msg.bikeIDToRent , msg.rackNum);
				pushToBackendCommRentInputQ(msg);
	//			rentalSuccess = kioskBeginRental(number, bikeID);
	//			if(rentalSuccess) pushToCANQ(5);
	//			bikeUnlockRack = 5;
			}
			else{
				//shouldnt ever get here due to earlier check, but just in case....
				printf("no rack met conditions needed for rental\n\r");
				gf->setuiPageNum(gf->drawFailurePage(3)); // rental success code 0 - success, 1 - bad code, 2 - unknown error, 3 - no charged bikes available
			}
		} else if(isRentOutputDataAvailable()){
			printf("SETTING PROCCESSING RENTAL FALSE");
			processingRental = false;
			BackendRentOutputMsg msg = popRentOutputQMsg();
			if (msg.bikeRentalSuccess)
			{
				printf("Success\n");
				pushToCANQ(msg.rackNum);
				gf->setuiPageNum(gf->drawSuccessPage(msg.bikeIDToRent, msg.rackNum));
			}
			else
			{
				printf("Failure\n");
				gf->setuiPageNum(gf->drawFailurePage(msg.rentalSuccessCode)); // rental success code 0 - success, 1 - bad code, 2 - unknown error, 3 - no charged bikes available
			}
		}
	}

	if (uiScreenNum == 15) // processing problem screen
	{
		//bike problem code

		std::string bikeProblemProcessingMessage;

		if (reportBicycleProblem(1, gf->getBikeProblemCode()) == SUCCESS)
		{
			bikeProblemProcessingMessage = "Success";
		}
		else
		{
			bikeProblemProcessingMessage = "Failure";
		}

		gf->setuiPageNum(gf->drawBikeReportProblemProcessingSuccessOrErrorPage(bikeProblemProcessingMessage));

	}

	uistate->pageNum = gf->getuiPageNum();
	// check for ui timeout
	manageUiTimeout(true);
}

navQData  UIWorker::tryPopNavQ(){
	//create data wrapper

	//change code here to use raw c++ queue instead
	//be sure to wrap it in a mutex lock whenever pushed/popped
	navQData navQVal;
	gpointer data = g_async_queue_try_pop(navQ);
	if(data == NULL){
		return navQVal;
	} else {
		//create copy so you can deallocate memory on heap
		navQVal = *(navQData *) data;  //TODO - test this line, not sure if it will work
		delete (navQData *)data;
		return navQVal;
	}
}

numQData  UIWorker::tryPopNumQ(){
	//create data wrapper
	numQData numQVal;
	gpointer data = g_async_queue_try_pop(numQ);
	if(data == NULL){
		return numQVal;
	} else {
		//create copy so you can deallocate memory on heap
		numQVal = *(numQData *) data;  //TODO - test this line, not sure if it will work
		delete (numQData *)data;
		return numQVal;
	}
}

CANQData  UIWorker::tryPopCANQ(){
	//create data wrapper
	CANQData CANQVal;
	gpointer data = g_async_queue_try_pop(CANQ);
	if(data == NULL){
		return CANQVal;
	} else{
		//create copy so you can deallocate memory on heap
		CANQVal = *(CANQData *) data;  //TODO - test this line, not sure if it will work
		delete (CANQData *) data;
		return CANQVal;
	}
}

backendQData  UIWorker::tryPopBackendQ(){
	//create data wrapper
	backendQData backendQVal;
	gpointer data = g_async_queue_try_pop(backendQ);
	if(data == NULL){
		return backendQVal;
	} else{
		//create copy so you can deallocate memory on heap
		backendQVal = *(backendQData *) data;  //TODO - test this line, not sure if it will work
		delete (backendQData *)data; ///deallocate mem on heap
		return backendQVal;
	}
}

void  UIWorker::pushToCANQ(int id){
	CANQData *CANQMsg = new CANQData;
	CANQMsg->idToUnlock = id;
	CANQMsg->dataAvailable = true;
	g_async_queue_push(CANQ, (gpointer)CANQMsg);
}

void UIWorker::work() {
	updateUI();
	periodic_battery_checkup();
	periodic_status_update();
	manageWeatherTimeout();
}

void UIWorker::manageWeatherTimeout(){
	int elapsedWeatherTime = 0;
	elapsedWeatherTime = (numberOfWeatherIterations * UI_WORKER_PERIOD_MS);
	if (updateWeatherSooner) {
		if (elapsedWeatherTime >= WEATHER_TIMEOUT_SOONER_MS){
			if (getPing()[0] == '1') {
				updateWeather();
				numberOfWeatherIterations = 0;
			}
			else {
				numberOfWeatherIterations = numberOfWeatherIterations - 100;
			}
		} else {
			numberOfWeatherIterations++;
		}
	} else {
		if (elapsedWeatherTime >= WEATHER_TIMEOUT_MS){
			if (getPing()[0] == '1') {
				updateWeather();
				numberOfWeatherIterations = 0;
			}
			else {
				numberOfWeatherIterations = numberOfWeatherIterations - 100;
			}
		} else {
			numberOfWeatherIterations++;
		}
	}
}

void UIWorker::manageUiTimeout(bool resetToUi) {

	int elapsedUiTimeoutTime = 0;
	elapsedUiTimeoutTime = (numberOfUiIterations * UI_WORKER_PERIOD_MS);
//	///////////////
//	//DEBUG
//	logText.append("UIWorker.cpp -- manageUiTimeout()");
//	LOG();
//	logText.append("elapsedUiTimeoutTime:");
//	appendInt(elapsedUiTimeoutTime);
//	LOG();
//	///////////////

	 if ((elapsedUiTimeoutTime >= UI_TIMEOUT_MS))  {
		 numberOfUiIterations = 0;
		 gf->setuiPageNum(gf->drawAdvertisementsPage());
		//backLightOff();  // TURN OFF BACKLIGHT
		//bLOn = false;
	 }
	 else {
		 numberOfUiIterations++;
	 }
//	 ///////////////
//	//DEBUG
//	logText.append("UIWorker.cpp -- manageUiTimeout()");
//	LOG();
//	logText.append("numberOfUiIterations:");
//	appendInt(numberOfUiIterations);
//	LOG();
//	///////////////
}

void UIWorker::updateWeather() {
	//parsedWeatherData *weatherDataFromThread = getWeatherDataStruct();

	//weatherJSON = getWeatherJSON();

	parsedWeatherData *tempWeatherDataFromThread = getWeatherDataStruct();
	std::string errorConditionString = "error";
	if((tempWeatherDataFromThread->weatherIconName).compare(errorConditionString) != 0) {
		parsedWeatherData *weatherDataFromThread = tempWeatherDataFromThread;

		printf(ANSI_COLOR_BLUE "From UIWorker -- weatherJSON.txt is %s" ANSI_COLOR_RESET "\n",weatherDataFromThread->weatherJSON.data());

		currentWeatherTemperature = weatherDataFromThread->currentWeatherTemperature;
		gf->setCurrentTemp(currentWeatherTemperature);

		currentWeatherForecast = weatherDataFromThread->currentWeatherForecast;
		printf(ANSI_COLOR_BLUE "From UIWorker -- string size is %d" ANSI_COLOR_RESET "\n", getStringSize(currentWeatherForecast));

		if (getStringSize(currentWeatherForecast) <= 5) //if (getStringSize(currentWeatherForecast) <= 1)
		{
			std::string checkBackSoon = "Initializing Weather System. Please try again soon.";
			gf->setcurrentWeatherForecast(checkBackSoon.data());
			updateWeatherSooner = true;
		}
		else {
			printf(ANSI_COLOR_BLUE "From UI Worker:::%s" ANSI_COLOR_RESET "\n", currentWeatherForecast.data());
			gf->setcurrentWeatherForecast(currentWeatherForecast);
			updateWeatherSooner = false;
		}

		todaysHighTemperature = weatherDataFromThread->todaysHighTemperature;
		printf(ANSI_COLOR_BLUE "From UI Worker:::%s" ANSI_COLOR_RESET "\n", todaysHighTemperature.data());
		gf->setHighTemp(todaysHighTemperature);

		todaysLowTemperature = weatherDataFromThread->todaysLowTemperature;
		printf(ANSI_COLOR_BLUE "From UI Worker:::%s" ANSI_COLOR_RESET "\n", todaysLowTemperature.data());
		gf->setLowTemp(todaysLowTemperature);

		weatherIconName = weatherDataFromThread->weatherIconName;
		printf(ANSI_COLOR_BLUE "From UI Worker:::%s" ANSI_COLOR_RESET "\n", weatherIconName.data());
		gf->setWeatherIconName((weatherIconName));
	}
	//gf->setuiPageNum(gf->drawAdvertisementsPage());
}

int UIWorker::getStringSize(std::string const &inputString){
  size_t sizeOfThisString = inputString.length();
  int bytesOfThisString = static_cast<int>(sizeOfThisString);
  return bytesOfThisString;
}
