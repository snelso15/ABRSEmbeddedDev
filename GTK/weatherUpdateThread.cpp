/*
 * weatherUpdateThread.cpp
 *
 *  Created on: Jul 18, 2016
 *      Author: snelso
 */

#include "weatherUpdateThread.h"

pthread_t weatherInfoUpdateThread;
//sem_t weatherInfoUpdateMutex;

//numberOfWeatherIterations = 0;
//
//weatherJSON = "";
//currentWeatherTemperature = "";
//currentWeatherForecast = "";
//todaysHighTemperature = "";
//todaysLowTemperature = "";
//weatherIconName = "";

//updateWeather();




//void manageWeatherTimeout(){
//	int elapsedWeatherTime = 0;
//	elapsedWeatherTime = (numberOfWeatherIterations * UI_WORKER_PERIOD_MS);
//	if (elapsedWeatherTime >= WEATHER_TIMEOUT_MS){
//		if (getPing()[0] == '1') {
//			updateWeather();
//			numberOfWeatherIterations = 0;
//		}
//		else {
//			numberOfWeatherIterations = numberOfWeatherIterations - 100;
//		}
//	} else {
//		numberOfWeatherIterations++;
//	}
//}

parsedWeatherData weatherData;

void updateThreadWeather() {
	weatherData.weatherJSON = getWeatherJSON();

	printf(ANSI_COLOR_YELLOW "From weatherUpdateThread -- weatherJSON is %s" ANSI_COLOR_RESET "\n",weatherData.weatherJSON.data());


	weatherData.currentWeatherTemperature = getTemperature();
	//gf->setCurrentTemp(currentWeatherTemperature);

	weatherData.currentWeatherForecast = getWeatherForecast(weatherData.weatherJSON);
	printf(ANSI_COLOR_YELLOW "From weatherUpdateThread:::%s" ANSI_COLOR_RESET "\n", weatherData.currentWeatherForecast.data());
	//gf->setcurrentWeatherForecast(currentWeatherForecast);

	weatherData.todaysHighTemperature = getHighTemperature();
	printf(ANSI_COLOR_YELLOW "From weatherUpdateThread:::%s" ANSI_COLOR_RESET "\n", weatherData.todaysHighTemperature.data());
	//gf->setHighTemp(todaysHighTemperature);

	weatherData.todaysLowTemperature = getLowTemperature();
	printf(ANSI_COLOR_YELLOW "From weatherUpdateThread:::%s" ANSI_COLOR_RESET "\n", weatherData.todaysLowTemperature.data());
	//gf->setLowTemp(todaysLowTemperature);

	std::string localWeatherIconName = getWeatherIcon();
	printf(ANSI_COLOR_YELLOW "From weatherUpdateThread:::%s" ANSI_COLOR_RESET "\n", localWeatherIconName.data());
	//gf->setWeatherIconName(weatherIconName);

	//gf->setWeatherIconName(getWeatherFile(weatherIconName));
	weatherData.weatherIconName = getWeatherFile(localWeatherIconName);

	//gf->setuiPageNum(gf->drawAdvertisementsPage());
	//return &weatherData;

	std::string errorConditionString = "error";
	if ((weatherData.weatherIconName).compare(errorConditionString) == 0) {   //(inputStringA.compare(inputStringB) == 0)
		printf(ANSI_COLOR_YELLOW "From weatherUpdateThread:::" ANSI_COLOR_RED "ERROR UPDATING WEATHER DATA " ANSI_COLOR_YELLOW "Retrying in 10 seconds..." ANSI_COLOR_RESET "\n");
		sleep(10);
		printf(ANSI_COLOR_YELLOW "Retrying..." ANSI_COLOR_RESET "\n");
		updateThreadWeather();
	}
}

//std::string updateWeatherJSON() {
//	return getWeatherJSON();
//}
//
//std::string udpateCurrentWeatherTemperature() {
//	return getTemperature();
//}
//
//std::string updateCurrentWeatherForecast() {
//	return getWeatherForecast(weatherData.weatherJSON);
//}
//
//std::string updateHighTemperature() {
//	return getHighTemperature();
//}
//
//std::string updateLowTemperature() {
//	return getLowTemperature();
//}
//
//std::string updateWeatherIconName() {
//	return getWeatherFile(getWeatherIcon());
//}


std::string getWeatherFile(std::string const &conditionFromWeatherAPICall) {

	printf("CONDITIONS = %s\n", conditionFromWeatherAPICall.data());

	struct weather Weather;

	  Weather.forecastPhrase[0] = "chanceflurries";
	  Weather.forecastPhrase[1] = "chancerain";
	  Weather.forecastPhrase[2] = "chancesleet";
	  Weather.forecastPhrase[3] = "chancesnow";
	  Weather.forecastPhrase[4] = "chancetstorms";
	  Weather.forecastPhrase[5] = "clear";
	  Weather.forecastPhrase[6] = "cloudy";
	  Weather.forecastPhrase[7] = "flurries";
	  Weather.forecastPhrase[8] = "fog";
	  Weather.forecastPhrase[9] = "hazy";
	  Weather.forecastPhrase[10] = "mostlycloudy";
	  Weather.forecastPhrase[11] = "mostlysunny";
	  Weather.forecastPhrase[12] = "overcast";
	  Weather.forecastPhrase[13] = "partlycloudy";
	  Weather.forecastPhrase[14] = "partlysunny";
	  Weather.forecastPhrase[15] = "sleet";
	  Weather.forecastPhrase[16] = "rain";
	  Weather.forecastPhrase[17] = "snow";
	  Weather.forecastPhrase[18] = "sunny";
	  Weather.forecastPhrase[19] = "tstorms";
	  Weather.forecastPhrase[20] = "unknown";

	  Weather.forcastFileName[0] = "chflurries.png";
	  Weather.forcastFileName[1] = "chrain.png";
	  Weather.forcastFileName[2] = "chsleet.png";
	  Weather.forcastFileName[3] = "chsnowy.png";
	  Weather.forcastFileName[4] = "chtstorms.png";
	  Weather.forcastFileName[5] = "sunny.png";
	  Weather.forcastFileName[6] = "cloudy.png";
	  Weather.forcastFileName[7] = "flurries.png";
	  Weather.forcastFileName[8] = "fog.png";
	  Weather.forcastFileName[9] = "haze.png";
	  Weather.forcastFileName[10] = "cloudy.png";
	  Weather.forcastFileName[11] = "sunny.png";
	  Weather.forcastFileName[12] = "overcast.png";
	  Weather.forcastFileName[13] = "partly.png";
	  Weather.forcastFileName[14] = "partly.png";
	  Weather.forcastFileName[15] = "sleet.png";
	  Weather.forcastFileName[16] = "rain.png";
	  Weather.forcastFileName[17] = "snowy.png";
	  Weather.forcastFileName[18] = "sunny.png";
	  Weather.forcastFileName[19] = "tstorms.png";
	  Weather.forcastFileName[20] = "unknown.png";

	  printf(ANSI_COLOR_YELLOW "%s size is %d" ANSI_COLOR_RESET "\n", conditionFromWeatherAPICall.c_str(), getStringSize(conditionFromWeatherAPICall));

	  std::string fileWithPath = "error";
	  std::string cleaned_conditionFromWeatherAPICall = "";

	  if (getStringSize(conditionFromWeatherAPICall) > 0){
		  cleaned_conditionFromWeatherAPICall = conditionFromWeatherAPICall.substr(0, getStringSize(conditionFromWeatherAPICall) - 1);

		  //printf("***%s***\n", conditionFromWeatherAPICall.c_str());
		  //std::string forecastCurrent = "chancetstorms";

		  for (int i = 0; i < 21; i++) {
			if (cleaned_conditionFromWeatherAPICall.compare(Weather.forecastPhrase[i]) == 0) {
			  //printf("%s\n", Weather.forcastFileName[i].c_str());
			  fileWithPath = "/home/pi/bike_project/weatherIcons/" + Weather.forcastFileName[i];
			  //printf("%s\n", fileWithPath.c_str());
			  break;
			}
		  }
	  }
	  return fileWithPath;
}

int getStringSize(std::string const &inputString){
  size_t sizeOfThisString = inputString.length();
  int bytesOfThisString = static_cast<int>(sizeOfThisString);
  return bytesOfThisString;
}

std::string compareStrings(std::string const &inputStringA, std::string const &inputStringB){
  std::string returnVal = (inputStringA.compare(inputStringB) == 0) ? "true" : "false";
  return returnVal;
}

std::string getWeatherJSON()
{
	FILE *fp;
	char path[1035000];

	/* Open the command for reading. */
	fp = popen("python weatherTools/getWeatherJSON.py > /mytmp/weatherJSON.txt" , "r");
	if (fp == NULL) {
		printf("Failed to run command\n" );
		return "";
	}

	/* Read the output a line at a time - output it. */
	while (fgets(path, sizeof(path)-1, fp) != NULL) {
		printf("%s", path);
	}

	/* close */
	pclose(fp);

	return (std::string) path;
}

std::string getTemperature()
{
	FILE *fp;
	char path[1035];

	/* Open the command for reading. */
	fp = popen("python weatherTools/getTemperature.py" , "r");
	if (fp == NULL) {
		printf("Failed to run command\n" );
		return "";
	}

	/* Read the output a line at a time - output it. */
	while (fgets(path, sizeof(path)-1, fp) != NULL) {
		printf("%s", path);
	}

	/* close */
	pclose(fp);

	return (std::string) path;
}

std::string getWeatherForecast(std::string weatherJSON)
{
	FILE *fp;
	char path[1035];
	//char command[1000];

	/* Open the command for reading. */
	fp = popen("cat /mytmp/weatherJSON.txt | python weatherTools/forecast.py" , "r");
	//printf("From std::string getWeatherForecast(std::string weatherJSON)\n");
	//printf("%s\n", weatherJSON.data());

	//sprintf(command, "'%s' | python weatherTools/forecast.py" , weatherJSON.data());

	//fp = popen(command, "r");
	if (fp == NULL) {
		printf("Failed to run command\n" );
		return "";
	}

	/* Read the output a line at a time - output it. */
	while (fgets(path, sizeof(path)-1, fp) != NULL) {
		printf("%s", path);
	}

	/* close */
	pclose(fp);

	return (std::string) path;
}

std::string getHighTemperature()
{
	FILE *fp;
	char path[1035];

	/* Open the command for reading. */
	fp = popen("cat /mytmp/weatherJSON.txt | python weatherTools/tempHigh.py" , "r");
	if (fp == NULL) {
		printf("Failed to run command\n" );
		return "";
	}

	/* Read the output a line at a time - output it. */
	while (fgets(path, sizeof(path)-1, fp) != NULL) {
		printf("%s", path);
	}

	/* close */
	pclose(fp);

	return (std::string) path;
}

std::string getLowTemperature()
{
	FILE *fp;
	char path[1035];

	/* Open the command for reading. */
	fp = popen("cat /mytmp/weatherJSON.txt | python weatherTools/tempLow.py" , "r");
	if (fp == NULL) {
		printf("Failed to run command\n" );
		return "";
	}

	/* Read the output a line at a time - output it. */
	while (fgets(path, sizeof(path)-1, fp) != NULL) {
		printf("%s", path);
	}

	/* close */
	pclose(fp);

	return (std::string) path;
}

std::string getWeatherIcon()
{
	FILE *fp;
	char path[1035];

	/* Open the command for reading. */
	fp = popen("cat /mytmp/weatherJSON.txt | python weatherTools/iconName.py" , "r");
	if (fp == NULL) {
		printf("Failed to run command\n" );
		return "";
	}

	/* Read the output a line at a time - output it. */
	while (fgets(path, sizeof(path)-1, fp) != NULL) {
		printf("%s", path);
	}

	/* close */
	pclose(fp);

	return (std::string) path;
}

struct parsedWeatherData* getWeatherDataStruct() {
	return &weatherData;
}

//returns void* so that you can pass data back to calling function if necessary
void* weatherInfoUpdateThreadRoutine(void* nullPointer){
	while(1){
		//manageRxBuffer();
		updateThreadWeather();
		sleep (900); //update weather data from Internet every 15 minutes
	}
	return NULL ;
}

void registerWeatherUpdateThread() {
//	if (0 != sem_init(&weatherInfoUpdateMutex, 0, 1)) {
//		printf("Something went wrong creating weather update semaphore\n");
//	} else {
//		printf("weather semaphore registered correctly\n");
//	}

	if (0 != pthread_create(&weatherInfoUpdateThread, NULL, &weatherInfoUpdateThreadRoutine, NULL)){
		printf("something went wrong with creating weatherInfoUpdateThread\n");
	} else{
		printf("weatherInfoUpdateThread registered correctly\n");
	}

}
