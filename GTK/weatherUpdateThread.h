/*
 * weatherUpdateThread.h
 *
 *  Created on: Jul 18, 2016
 *      Author: snelso
 */

#ifndef GTK_WEATHERUPDATETHREAD_H_
#define GTK_WEATHERUPDATETHREAD_H_

#define WEATHER_TIMEOUT_MS 600000

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "consoleColor.h"
#include <unistd.h>

struct weather {
    std::string forecastPhrase[21];
    std::string forcastFileName[21];
};


struct parsedWeatherData {
	std::string weatherJSON;
	std::string currentWeatherTemperature;
	std::string currentWeatherForecast;
	std::string todaysHighTemperature;
	std::string todaysLowTemperature;
	std::string weatherIconName;
};

//	int numberOfWeatherIterations;
//	std::string weatherJSON;
//	std::string currentWeatherTemperature;
//	std::string currentWeatherForecast;
//	std::string todaysHighTemperature;
//	std::string todaysLowTemperature;
//	std::string weatherIconName;

	extern parsedWeatherData weatherData;

	void updateThreadWeather();
	void manageWeatherTimeout();
	std::string getWeatherFile(std::string const &conditionFromWeatherAPICall);
	int getStringSize(std::string const &inputString);
	std::string compareStrings(std::string const &inputStringA, std::string const &inputStringB);
	std::string getWeatherJSON();
	std::string getTemperature();
	std::string getWeatherForecast(std::string weatherJSON);
	std::string getHighTemperature();
	std::string getLowTemperature();
	std::string getWeatherIcon();
	struct parsedWeatherData* getWeatherDataStruct();
	void* weatherInfoUpdateThreadRoutine(void* nullPointer);
	void registerWeatherUpdateThread();

#endif /* GTK_WEATHERUPDATETHREAD_H_ */
