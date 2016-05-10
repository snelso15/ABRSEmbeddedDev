/*
 * CommandLineUtils.cpp
 *
 *  Created on: Mar 20, 2016
 *      Author: snelso
 */

#include "CommandLineUtils.h"
std::string getWifiIP(){
	FILE *fp;
	char path[1035];

	/* Open the command for reading. */
	fp = popen("/sbin/ifconfig wlan0 | grep \"inet addr\" | awk -F: '{print $2}' | awk '{print $1}'", "r");
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

std::string get3gIP(){
	FILE *fp;
	char path[1035];

	/* Open the command for reading. */
	fp = popen("/sbin/ifconfig wwan0 | grep \"inet addr\" | awk -F: '{print $2}' | awk '{print $1}'", "r");
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

std::string getPing()
{
	FILE *fp;
	char path[1035];

	/* Open the command for reading. */
	fp = popen("python pi/python/ping.py" , "r");
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

std::string reConnectToNetwork()
{
	FILE *fp;
	char path[1035];
	char command[1000];

	sprintf(command, "echo raspberry | sudo -S ./start_wifi.sh &");

	/* Open the command for reading. */
	//fp = popen("echo raspberry | sudo -S ./start_wifi.sh &" , "r");
	fp = popen(command, "r");
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

	return "";
}

std::string clearLogs()
{
	FILE *fp;
	char path[1035];

	/* Open the command for reading. */
	fp = popen("rm /mytmp/*.log" , "r");
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
