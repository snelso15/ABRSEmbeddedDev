/*
 * CommandLineUtils.cpp
 *
 *  Created on: Mar 20, 2016
 *      Author: snelso
 */

#include "CommandLineUtils.h"
std::string getIP(){
	FILE *fp;
	char path[1035];

	/* Open the command for reading. */
	fp = popen("/sbin/ifconfig wlan0 | grep \"inet addr\" | awk -F: '{print $2}' | awk '{print $1}'", "r");
	if (fp == NULL) {
		printf("Failed to run command\n" );
		exit(1);
	}

	/* Read the output a line at a time - output it. */
	while (fgets(path, sizeof(path)-1, fp) != NULL) {
		printf("%s", path);
	}

	/* close */
	pclose(fp);

	return (std::string) path;
}

