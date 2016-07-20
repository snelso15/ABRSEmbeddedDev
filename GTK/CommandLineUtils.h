/*
 * CommandLineUtils.h
 *
 *  Created on: Mar 20, 2016
 *      Author: snelso
 */

#ifndef GTK_COMMANDLINEUTILS_H_
#define GTK_COMMANDLINEUTILS_H_
#include <stdio.h>
#include <stdlib.h>
#include <string>


std::string getWifiIP();
std::string get3gIP();
//std::string getWeatherJSON();
//std::string getTemperature();
//std::string getWeatherForecast(std::string weatherJSON);
//std::string getHighTemperature();
//std::string getLowTemperature();
//std::string getWeatherIcon();
std::string clearLogs();
std::string getPing();
std::string reConnectToNetwork();

#endif /* GTK_COMMANDLINEUTILS_H_ */
