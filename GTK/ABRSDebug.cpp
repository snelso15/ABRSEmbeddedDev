/*
 * ABRSDebug.cpp
 *
 *  Created on: Apr 23, 2016
 *      Author: snelso
 */

#include "ABRSDebug.h"

std::string logText;
std::string dateText;

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


#ifdef ABRS_DEBUG
void LOG(){
  std::ofstream myfile;
  myfile.open ("ABRS.log");
  prepareDateTimeTag();
  myfile << dateText.c_str() << logText.c_str() <<"\n";
  myfile.close();
}
#else
void LOG(){
	//do nothing if debug is turned off
}
#endif
