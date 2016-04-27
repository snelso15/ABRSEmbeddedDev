/*
 * TeensyWorker.cpp
 *
 *  Created on: Mar 3, 2016
 *      Author: snelso
 */

#include "TeensyWorker.h"
#include "backLightControl.h"

TeensyWorker::TeensyWorker(teensyCommunicator *tc, GAsyncQueue *navQ, GAsyncQueue *numQ, UIState *state){
	this->tc = tc;
	this->navQ = navQ;
	this->numQ = numQ;
	this->uistate = state;
	numberOfIterations = 0;
	wiringPiSetupSys();
	this->bLOn = true;
	backLightOn(); // activate backlight at start
}

TeensyWorker::~TeensyWorker() {

}

void TeensyWorker::pushToNavQ(char key){
	navQData *navQMsg = new navQData;
	navQMsg->key = key;
	navQMsg->dataAvailable = true;
	g_async_queue_push(navQ, (gpointer)navQMsg);
}

void TeensyWorker::pushToNumQ(int key){
	numQData *numQMsg = new numQData;
	numQMsg->key = key;
	numQMsg->dataAvailable = true;
	g_async_queue_push(numQ, (gpointer)numQMsg);
}

bool TeensyWorker::tryGetButtonPress(){
	//printf("PageNum is %d\n", uistate->pageNum);
	char keyVal = tc->checkButtonPress();

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
		default:
			break;
	}
	if(inNum != -1){
		//only accept number input if on appropriate screen
		if(uistate->pageNum == 3){
			//printf("Received a number input on the correct page: %i\n", inNum); //TODO - debug, remove
			pushToNumQ(inNum);
			return true;
		}
		else if(uistate->pageNum == 9)  // if a num key was pressed and we are at the idle screen, fake a nav press
		{
			pushToNavQ('a');
			return true;
		}
	}

	if(inChar != 'z'){
		if (uistate->pageNum == 12)//admin page
		{
			printf("pageNum is 12\n");
			g_print("pageNum is 12\n");
			// TODO insert check for admin screen
			switch (inChar)
			{
			case 'A': // turn on driver board
				g_print("turn on driver board\n");
				printf("turn on driver board\n");
				tc->activateLCDBoard();
				break;
			case 'B': // turn on backlight
				g_print("turn on backlight\n");
				backLightOn();
				break;
			case 'E': // turn off driver board
				g_print("turn off driver board\n");
				tc->deactivateLCDBoard();
				break;
			case 'F': // turn off backlight
				g_print("turn off backlight\n");
				backLightOff();
				break;
			default:
				break;
			}
		}
		pushToNavQ(inChar);
		return true;
	}


	return false;
}

void TeensyWorker::work() { // TODO extend to support lcd driver board
	manageBacklight(tryGetButtonPress());
}

void TeensyWorker::manageBacklight(bool turnOnBacklight) {
	if (turnOnBacklight) {
		backLightOn();
		bLOn = true;
		numberOfIterations = 0;
	}
	else if ((numberOfIterations * TEENSY_WORKER_PERIOD_MS >= BACKLIGHT_TIMEOUT_MS) && bLOn)  {
		backLightOff();  // TURN OFF BACKLIGHT
		bLOn = false;
	}
	else {
		numberOfIterations++;
	}

}
