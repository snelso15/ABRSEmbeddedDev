﻿#ifndef graphicalFunction_H
#define graphicalFunction_H

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include "kioskKeyInput.h"
#include "weatherMonitor.h"
#include "backendCommunicator.h"
#include "CommandLineUtils.h"
#include "PowerSystems.h"
#include "consoleColor.h"

class graphicalFunctions
{
#define UI_BUTTON_POSITION_1 135 //120
#define UI_BUTTON_POSITION_2 235 //220
#define UI_BUTTON_POSITION_3 335 //320
#define UI_BUTTON_POSITION_4 435 //420

	private:
		kioskKeyInput kki;

		GtkWidget *mainWindow;

		// KUI Object Declaration
		GtkWidget *centerNotebook;
		GtkWidget *leftNotebook;
		GtkWidget *rightNotebook;
		GtkWidget *table;
		GtkWidget *frame;
		GtkWidget *label;
		GtkWidget *label1;
		GtkWidget *checkbutton;
		GtkWidget *button;
		GtkWidget *image;
		GtkWidget *fixed;
		GtkWidget *centerFixed;
		GtkWidget *leftFixed;
		GtkWidget *rightFixed;
		GtkWidget *keypadLabel;
		// end KUI Object Declaration


		// online payment code variables
		gchar onlineCode[5];
		gchar *p1 = onlineCode;
		gint onlineCodeCounter;

		// for menu navigation
		gint uiPageNum = 0;
		gchar key = 'z';

		std::string currentTemp = "";
		std::string currentWeatherForecast = "";
		std::string highTemp = "";
		std::string lowTemp = "";
		std::string weatherIconName = "";
		std::string closingTime = "";
		std::string openingTime = "";

		int bikeRackNumber = 0;
		int bikeReturnRackNumber = 0;

		int currentTime_Hours = 12;
		int currentTime_Minutes = 0;

		int openingTime_Hours = 7;
		int openingTime_Minutes = 30;

		int closingTime_Hours = 21;
		int closingTime_Minutes = 30;

		BIKE_CONDITION_CODE bikeCode = NO_ISSUES;

	public:

		graphicalFunctions(void);
		void updateUI(char key);
		gint connectSignals();
		gint buildUI();
		gint drawWelcomePage(void);
		gint drawNextPage(void);
		gint drawPrevPage(void);
		gint drawRentPage(void);
		gint drawReportProblemPage(void);
		gint drawMapPage(void);
		gint drawCreditCardPage(void);
		gint drawOnlineCodePage(void);
		gint drawOnlineCodePage(std::string code);
		gint drawSubmitPage(void);
		gint drawSuccessPage(unsigned int bikeID, int racknum);
		gint drawFailurePage(int rentalSuccessCode);
		gint printSomething(void);
		gint drawInfoPage(void);
		gint drawWeatherPage(void);
		gint drawAdminPage(void);
		gint drawReturnPage(unsigned int, int rackNum);
		gint drawAdvertisementsPage(void);
		gint drawBikeProblemsPage(int rackNumber);
		gint drawBikeReportProblemProcessingPage(BIKE_CONDITION_CODE code);
		gint drawBikeReportProblemProcessingSuccessOrErrorPage(std::string successOrError);
		//static gint key_press_cb(GtkWidget *widget, GdkEventKey *kevent, gpointer* data);
		static void destroy_window( GtkWidget *widget,gpointer  pointer );
		gint drawOnlineRentHelpPageStepOne(void);
		gint drawOnlineRentHelpPageStepTwo(void);
		gint drawNetworkConnectionDownPage(void);
		gint drawOperatingHoursPage(void);

		//getters/setters
		GtkWidget* getMainWindow(){
			return mainWindow;
		}

		kioskKeyInput getKKI(){
			return kki;
		}

		gint getuiPageNum(){
			return uiPageNum;
		}

		void setuiPageNum(gint val){
			uiPageNum = val;
		}

		void setCurrentTemp(std::string temp) {
			currentTemp = temp;
		}

		void setcurrentWeatherForecast(std::string forecast) {
			currentWeatherForecast = forecast;
		}

		void setHighTemp(std::string high) {
			highTemp = high;
		}

		void setLowTemp(std::string low) {
			lowTemp = low;
		}

		void setWeatherIconName(std::string name) {
			weatherIconName = name;
		}

		void setClosingTime(std::string functionClosingTime) {
			closingTime = functionClosingTime;
		}

		void setOpeningtime(std::string functionOpeningTime) {
			openingTime = functionOpeningTime;
		}


		void setCurrentTime_Hours(int hour) {
			currentTime_Hours = hour;
		}

		int getCurrentTime_Hours(void) {
			return currentTime_Hours;
		}

		void setCurrentTime_Minutes(int minute) {
			currentTime_Minutes = minute;
		}

		int getCurrentTime_Minutes(void) {
			return currentTime_Minutes;
		}

		void setOpeningTime_Hours(int hour) {
			openingTime_Hours = hour;
		}

		int getOpeningTime_Hours(void) {
			return openingTime_Hours;
		}

		void setOpeningtTime_Minutes(int minute) {
			openingTime_Minutes = minute;
		}

		int getOpeningTime_Minutes(void) {
			return openingTime_Minutes;
		}

		void setClosingTime_Hours(int hour) {
			closingTime_Hours = hour;
		}

		int getClosingTime_Hours(void) {
			return closingTime_Hours;
		}

		void setClosingTime_Minutes(int minute) {
			closingTime_Minutes = minute;
		}

		int getClosingTime_Minutes(void) {
			return closingTime_Minutes;
		}



		int getBikeRackNumber(void)
		{
			return bikeRackNumber;
		}

		void setBikeRackNumber(int number)
		{
			bikeRackNumber = number;
		}
		int getBikeReturnRackNumber(void)
		{
			return bikeReturnRackNumber;
		}

		void setBikeReturnRackNumber(int number)
		{
			bikeReturnRackNumber = number;
		}


		BIKE_CONDITION_CODE getBikeProblemCode(void)
		{
			return bikeCode;
		}

		void setBikeProblemCode(BIKE_CONDITION_CODE code)
		{
			bikeCode = code;
		}

//		constexpr unsigned int str2int(const char* str, int h = 0)
//		{
//		    return !str[h] ? 5381 : (str2int(str, h+1)*33) ^ str[h];
//		}

		int getStringSize(std::string const &inputString){
		  size_t sizeOfThisString = inputString.length();
		  int bytesOfThisString = static_cast<int>(sizeOfThisString);
		  return bytesOfThisString;
		}

		std::string getTimeString(int hours, int minutes){
			char am_pm[10];

			if (hours > 12) {
				hours = hours % 12;
				sprintf(am_pm, "%s","pm");
			} else {
				sprintf(am_pm, "%s", "am");
			}

			char currentTime[30];

			if (minutes < 10) {
				sprintf(currentTime, "%d:0%d %s", hours, minutes, am_pm);
			} else {
				sprintf(currentTime, "%d:%d %s", hours, minutes, am_pm);
			}
			std::string currentTimeString = currentTime;
			return currentTimeString.c_str();
		}
};


/*
static void key_press_cb(GtkWidget *widget, GdkEventKey *kevent, gpointer data)
{
	graphicalFunctions *gFp = static_cast<graphicalFunctions *>(data);
	switch( kevent->keyval )
	{
		case KEY_UP:
            printf("Up\n");//key up
            gtk_main_quit();
            break;
        case KEY_DOWN:
        	gFp->setuiPageNum(gFp->drawWelcomePage());
            break;
        case KEY_RIGHT:
			gFp->setuiPageNum(gFp->drawNextPage());
            break;
        case KEY_LEFT:
			gFp->setuiPageNum(gFp->drawPrevPage());
            break;

        default:
			printf("%d", kevent->keyval);
			break;
	}

	gint key = gFp->getKKI().readKey(kevent->keyval);

	switch (gFp->getuiPageNum())
	{
		case (0):  // welcome screen
		{
			printf("i'm in case 0\n");

			gFp->drawWelcomePage();


			switch (key)
			{
				case 'a':  // Rent Screen
					gFp->setuiPageNum(gFp->drawRentPage());
					printf("i saw in a %c at %d\n", key, gFp->getuiPageNum());
            		key = 'z';
					break;
				case 'b':
					printf("i saw in a %c at %d\n", key, gFp->getuiPageNum());
					break;
				case 'c':
					printf("i saw in a %c at %d\n", key, gFp->getuiPageNum());
					break;
				case 'e':  // Report Problem
					gFp->setuiPageNum(gFp->drawReportProblemPage());
					printf("i saw in a %c at %d\n", key, gFp->getuiPageNum());
            		key = 'z';
					break;
				case 'f':
					printf("i saw in a %c at %d\n", key, gFp->getuiPageNum());
					break;
				case 'g':  // Map
					gFp->setuiPageNum(gFp->drawMapPage());
					printf("i saw in a %c at %d\n", key, gFp->getuiPageNum());
            		key = 'z';
					break;
				default:
					break;
			}
			break;
		}
		case (1):  // Rent screen
		{
			printf("i'm in case 1\n");
			switch (key)
			{
				case 'a':  // Credit Card
					gFp->setuiPageNum(gFp->drawCreditCardPage());
            		key = 'z';
					break;
				case 'd': // Back
					gFp->setuiPageNum(gFp->drawWelcomePage());
            		key = 'z';
					break;
				case 'e':  // Online Code
					gFp->setuiPageNum(gFp->drawOnlineCodePage());
            		key = 'z';
					break;
				case 'h':  // Cancel
					gFp->setuiPageNum(gFp->drawWelcomePage());
            		key = 'z';
					break;
				default:
					break;
			}
			break;
		}
		case (2):  // Swipe Credit Card
		{
			printf("i'm in case 2\n");
			switch (key)
			{
				case 'd':  // Back
					gFp->setuiPageNum(gFp->drawRentPage());
            		key = 'z';
					break;
				case 'h': // Cancel
					gFp->setuiPageNum(gFp->drawWelcomePage());
            		key = 'z';
					break;
				default:
					break;
			}
			break;
		}
		case (3):  // Online Payment
		{
			printf("i'm in case 3\n");
			switch (key)
			{
				case 'd':  // Back
					gFp->setuiPageNum(gFp->drawRentPage());
					printf("i saw in a %c at %d\n", key, gFp->getuiPageNum());
            		key = 'z';
					break;
				case 'e':  // submit
					gFp->setuiPageNum(gFp->drawSubmitPage());
            		key = 'z';
					break;
				case 'h': // Cancel
					gFp->setuiPageNum(gFp->drawWelcomePage());
            		key = 'z';
					break;
				default:  // was the keypad used?
					break;
			}
			break;
		}
		case (5):  // Map Screen
		{
			printf("i'm in case 5\n");
			switch (key)
			{
				case 'd':  // Back
					gFp->setuiPageNum(gFp->drawWelcomePage());
            		key = 'z';
					break;
				default:
					break;
			}
			break;
		}
		case (6):  // Report Problem
		{
			printf("i'm in case 6\n");
			switch (key)
			{
				case 'd':  // Back
					gFp->setuiPageNum(gFp->drawWelcomePage());
            		key = 'z';
					break;
				case 'h':  // Back
					gFp->setuiPageNum(gFp->drawWelcomePage());
            		key = 'z';
					break;
				default:
					break;
			}
			break;
		}
		case (7):  // Processing Transaction
			{
			printf("i'm in case 7\n");

			switch (key)
			{
			case ' ':
			{
				if(0)//good code
				{
					gFp->setuiPageNum(gFp->drawSuccessPage());
					key = 'z';
				}
				else//bad code
				{
					gFp->setuiPageNum(gFp->drawFailurePage());
					key = 'z';
				}
				break;
			}
			default:
				break;
			}
			break;
			}
		case (8): // Transaction Failure
		{
			switch (key)
			{
				case 'd':
				{
					gFp->setuiPageNum(gFp->drawRentPage());
            		key = 'z';
					break;
				}
				default:
					break;
		}
		break;
		default:
			break;
		}
	}
}
*/


#endif
