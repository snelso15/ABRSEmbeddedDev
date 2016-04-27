/*
 * UIWorker.cpp
 *
 *  Created on: Mar 3, 2016
 *      Author: snelso
 */

#include "UIWorker.h"

UIWorker::UIWorker(GAsyncQueue *navQ, GAsyncQueue *numQ, GAsyncQueue *CANQ, GAsyncQueue *backendQ, UIState * state, graphicalFunctions *gf){
	this->gf = gf;
	this->navQ =navQ;
	this->numQ =numQ;
	this->CANQ =CANQ;
	this->backendQ = backendQ;
	this->uistate = state;
	this->rentalCode = new std::string;
	init_battery_comms();
	initUI();

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

	///////////////
	//DEBUG
	logText.clear();
	logText.append("UpdateUI called");
	LOG();
	///////////////

	int uiScreenNum = uistate->pageNum;

	if ((uiScreenNum != 3) && (uiScreenNum != 7))rentalCode->clear();

	navQData navQMsg = tryPopNavQ();

	//nested ifs or case statement to inspect uiScreenNum variable and update accordingly
	if(navQMsg.dataAvailable){
		if(navQMsg.key == 'r' && (uiScreenNum == 0  || uiScreenNum == 9) ){
			gf->setuiPageNum(gf->drawReturnPage(navQMsg.bikeID));
		} else if (navQMsg.key != 'r'){
			gf->updateUI(navQMsg.key);
			numberOfUiIterations = 0;
		}
	}

	//check to see if ui update should send a CANQ msg - probably nested in above cases
	numQData numQMsg = tryPopNumQ();
	if(numQMsg.dataAvailable){
		//printf("pushing %i to canq...\n", numQMsg.key);
		//pushToCANQ(numQMsg.key);
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
		printf("rentalCode Length = %d\n", rentalCode->length());
		numberOfUiIterations = 0;
	}

	//check to see if ui update should send a backendQ msg - probably nested in above cases

	if (uiScreenNum == 7) // in processing rental screen
	{
		printf("in processing screen\n");
		//int number = std::stoi(rentalCode,nullptr,0);
		int number = atoi(rentalCode->data());
		printf("int rentalcode is %d\n", number);

		bool rentalSuccess = false;
		unsigned int bikeID = 0;
		if(globalCANStat->getRack(1)->bikePresent){
			rentalSuccess = kioskBeginRental(number, 0xA000);
			bikeID = 0xA000;
			if(rentalSuccess) pushToCANQ(1);
		}
		else if(globalCANStat->getRack(2)->bikePresent){
			rentalSuccess = kioskBeginRental(number, 0xA000);
			bikeID = 0xA000;
			if(rentalSuccess) pushToCANQ(2);
		} else{
			printf("should unlock bike, but no valid bike held!!!!");
		}

		if (rentalSuccess)
		{
			printf("Success\n");
			gf->setuiPageNum(gf->drawSuccessPage(bikeID));
		}
		else
		{
			printf("Failure\n");
			gf->setuiPageNum(gf->drawFailurePage());
		}
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
	} else{
		//create copy so you can deallocate memory on heap
		navQVal = *(navQData *) data;  //TODO - test this line, not sure if it will work
		delete data;
		return navQVal;
	}
}

numQData  UIWorker::tryPopNumQ(){
	//create data wrapper
	numQData numQVal;
	gpointer data = g_async_queue_try_pop(numQ);
	if(data == NULL){
		return numQVal;
	} else{
		//create copy so you can deallocate memory on heap
		numQVal = *(numQData *) data;  //TODO - test this line, not sure if it will work
		delete data;
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
		delete data;
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
		delete data; ///deallocate mem on heap
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
}

void UIWorker::manageUiTimeout(bool resetToUi) {
//	if (resetToUi) {
//		//backLightOn();
//		bLOn = true;
//		numberOfIterations = 0;
//	}
	 if ((numberOfUiIterations * UI_WORKER_PERIOD_MS >= UI_TIMEOUT_MS))  {
		 numberOfUiIterations = 0;
		 gf->setuiPageNum(gf->drawAdvertisementsPage());
		//backLightOff();  // TURN OFF BACKLIGHT
		//bLOn = false;
	}
	else {
		numberOfUiIterations++;
	}
}



