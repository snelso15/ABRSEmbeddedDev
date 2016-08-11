// networkConnectivityThread.cpp

#include "networkConnectivityThread.h"

pthread_t internetConnectionStatusThread;
extern bool connectedInternet = false;

void updateInternetConnectionStatus()
{
	std::string internetUpDown;
	std::string internetUp = "1\n";
	internetUpDown = getDNSPing();

	connectedInternet = (internetUpDown.compare(internetUp) == 0) ? true : false;
	if(connectedInternet) {
		printf("INTERNET " ANSI_COLOR_GREEN "UP" ANSI_COLOR_RESET "\n");
	} else {
		printf("INTERNET " ANSI_COLOR_RED "DOWN" ANSI_COLOR_RESET "\n");
	}
}

//bool *getConnectedInternetStatus() {
//	return &connectedInternet;
//}

bool getConnectedInternetStatus() {
	return connectedInternet;
}

std::string getDNSPing()
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

//returns void* so that you can pass data back to calling function if necessary
void* internetConnectionStatusUpdateThreadRoutine(void* nullPointer){
	while(1){
		//manageRxBuffer();
		updateInternetConnectionStatus();
		sleep (1); //update every second
	}
	return NULL ;
}

void registerInternetConnectionStatusUpdateThread() {
	if (0 != pthread_create(&internetConnectionStatusThread, NULL, &internetConnectionStatusUpdateThreadRoutine, NULL)){
		printf("something went wrong with creating internetConnectionStatusThread\n");
	} else {
		printf("internetConnectionStatusThread registered correctly\n");
	}
}
