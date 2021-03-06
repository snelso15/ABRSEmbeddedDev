/*
 * ABRSDebug.h
 *
 *  Created on: Apr 23, 2016
 *      Author: snelso
 */

#ifndef GTK_ABRSDEBUG_H_
#define GTK_ABRSDEBUG_H_

#include <iostream>
#include <fstream>
#include <string>


#include <stdio.h>      /* puts */
#include <time.h>       /* time_t, struct tm, time, localtime, strftime */

#define ABRS_DEBUG 1

extern std::string logText;

void LOG ();
void initLog();
void appendInt(int value);
void appendChar(char value);


#endif /* GTK_ABRSDEBUG_H_ */
