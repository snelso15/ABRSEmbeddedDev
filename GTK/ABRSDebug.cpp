/*
 * ABRSDebug.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: snelso
 */

#include "ABRSDebug.h"
#include "CommandLineUtils.h"

std::string logText;
std::string dateText;
std::string logFileName;
unsigned long numBytesWritten;

#include <stdio.h>      /* puts */
#include <time.h>       /* time_t, struct tm, time, localtime, strftime */

void prepareDateTimeTag()
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer [80];

	time (&rawtime);
	timeinfo = localtime (&rawtime);

	strftime (buffer,80,"%c -- ",timeinfo);

	dateText.clear();
	dateText.append(buffer);
}

void initLog(){
	clearLogs();

	numBytesWritten = 0;

	time_t rawtime;
	struct tm * timeinfo;
	char buffer [80];

	time (&rawtime);
	timeinfo = localtime (&rawtime);

	strftime (buffer,80,"/mytmp/ABRS-%F-hr-%I-min-%M.log",timeinfo);

	logFileName.clear();
	logFileName.append(buffer);
}

void appendInt(int value){
	char buff[20];
	sprintf(buff, "%d", value);
	logText.append(buff);
}

void appendChar(char value){
	std::string charString;
	charString = std::string(1, value);
	logText.append(charString);
}


#ifdef ABRS_DEBUG
void LOG(){
	numBytesWritten+= logText.size() + dateText.size() + 1;

	std::ofstream myfile;
	if(numBytesWritten > 4500000000){
		numBytesWritten = 0;
		myfile.open (logFileName.c_str());
	}else{
		myfile.open (logFileName.c_str() , std::ofstream::out | std::ofstream::app);
	}
	prepareDateTimeTag();
	myfile << dateText.c_str() << logText.c_str() <<"\n";
	myfile.close();
	logText.clear();
}
#else
void LOG(){
	//do nothing if debug is turned off
}
#endif
