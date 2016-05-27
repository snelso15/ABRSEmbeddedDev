/*
 * UIWorker.cpp
 *
 *  Created on: Mar 3, 2016
 *      Author: snelso
 */

#include "UIWorker.h"
int numbikes = 2;
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

	weatherJSON = "";
	currentWeatherTemperature = "";
	currentWeatherForecast = "";
	todaysHighTemperature = "";
	todaysLowTemperature = "";
	weatherIconName = "";

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
	if(navQMsg.dataAvailable){
		if(navQMsg.key == 'r'){
			if (!numbikes){
				numbikes = 1;
			} else{
				numbikes = 2;
			}
			if(uiScreenNum == 0  || uiScreenNum == 9 || uiScreenNum == 4){
				gf->setuiPageNum(gf->drawReturnPage(navQMsg.bikeID));
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
				if (adminCode->compare("6666") == 0) // code is equal, go to admin now
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
		printf("in processing screen\n");
		//int number = std::stoi(rentalCode,nullptr,0);
		int number = atoi(rentalCode->data());
		//printf("int rentalcode is %d\n", number);

		unsigned short bikeId = 0xA000;
		if(numbikes == 0){
			bikeId = 0;
		} else if (numbikes == 1){
			bikeId = 0xA001;
		}
		int rentalSuccess = 0;
		//unsigned int bikeID = 0;
		int bikeUnlockRack = 0;
		if(bikeId){
			if(globalCANStat->getRack(1)->bikePresent){
				rentalSuccess = kioskBeginRental(number, bikeId);
				if(rentalSuccess) pushToCANQ(1);
				bikeUnlockRack = 1;
				//pushToCANQ(1);//brute force it for now
			}
			else if(globalCANStat->getRack(2)->bikePresent){
				rentalSuccess = kioskBeginRental(number, bikeId);
				if(rentalSuccess) pushToCANQ(2);
				bikeUnlockRack = 2;
				//pushToCANQ(2);//brute force it for now
			}
			else if(globalCANStat->getRack(3)->bikePresent){
				rentalSuccess = kioskBeginRental(number, bikeId);
				bikeUnlockRack = 3;
				if(rentalSuccess) pushToCANQ(3);
				//pushToCANQ(3);//brute force it for now
			}
			else if(globalCANStat->getRack(4)->bikePresent){
				rentalSuccess = kioskBeginRental(number, bikeId);
				bikeUnlockRack = 4;
				if(rentalSuccess) pushToCANQ(4);
				//pushToCANQ(4);//brute force it for now
			}
			else if(globalCANStat->getRack(5)->bikePresent){
				rentalSuccess = kioskBeginRental(number, bikeId);
				if(rentalSuccess) pushToCANQ(5);
				bikeUnlockRack = 5;
				//pushToCANQ(4);//brute force it for now
			}
		}

		if (numbikes && rentalSuccess == 1)
		{
			printf("Success\n");
			gf->setuiPageNum(gf->drawSuccessPage(bikeId, bikeUnlockRack));
			if(numbikes == 2){
				numbikes = 1;
			}else if(numbikes == 1){
				numbikes =0;
			}
		}
		else
		{
			printf("Failure\n");
			gf->setuiPageNum(gf->drawFailurePage());
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
	weatherJSON = getWeatherJSON();

	printf("From UIWorker -- weatherJSON is\n%s",weatherJSON.data());


	currentWeatherTemperature = getTemperature();
	gf->setCurrentTemp(currentWeatherTemperature);

	currentWeatherForecast = getWeatherForecast(weatherJSON);
	printf("From UI Worker:::%s\n", currentWeatherForecast.data());
	gf->setcurrentWeatherForecast(currentWeatherForecast);

	todaysHighTemperature = getHighTemperature();
	printf("From UI Worker:::%s\n", todaysHighTemperature.data());
	gf->setHighTemp(todaysHighTemperature);

	todaysLowTemperature = getLowTemperature();
	printf("From UI Worker:::%s\n", todaysLowTemperature.data());
	gf->setLowTemp(todaysLowTemperature);

	weatherIconName = getWeatherIcon();
	printf("From UI Worker:::%s\n", weatherIconName.data());
	gf->setWeatherIconName(weatherIconName);

	gf->setuiPageNum(gf->drawAdvertisementsPage());
}



