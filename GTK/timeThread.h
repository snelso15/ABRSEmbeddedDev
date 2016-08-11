#ifndef GTK_TIMETHREAD_H_
#define GTK_TIMETHREAD_H_

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "consoleColor.h"
#include <unistd.h>

struct kioskTimes{
	std::string openingTime;
	std::string closingTime;
	int openingTime_Hours;
	int closingTime_Hours;
	int openingTime_Minutes;
	int closingTime_Minutes;
	int currentTime_Hours;
	int currentTime_Minutes;
};

extern kioskTimes kioskTimeData;

std::string getOpeningTime();
std::string getClosingTime();
std::string getCurrentSystemTimeString_Hours();
std::string getCurrentSystemTimeString_Minutes();
int convertStringToInteger(std::string const &stringString);
int getIntOpeningTime_Hours(std::string const &timeString);
int getIntOpeningTime_Minutes(std::string const &timeString);
int getIntClosingTime_Hours(std::string const &timeString);
int getIntClosingTime_Minutes(std::string const &timeString);
std::string getCurrentSystemTime_Hour(std::string const &timeString);
int getIntCurrentSystemTime_Hours(std::string const &timeString);
int getIntCurrentSystemTime_Minutes(std::string const &timeString);
void updateTimes();

void* timeStatusThreadUpdateThreadRoutine(void* nullPointer);
void registerTimeStatusThreadUpdateThread();

#endif
