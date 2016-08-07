#ifndef GTK_NETWORKCONNECTIVITYTHREAD_H_
#define GTK_NETWORKCONNECTIVITYTHREAD_H_

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "consoleColor.h"
#include <unistd.h>

#define INTERNET_TIMEOUT_MS 5000


std::string getDNSPing();

void updateInternetConnectionStatus();
//bool *getConnectedInternetStatus();
bool getConnectedInternetStatus();
void* internetConnectionStatusUpdateThreadRoutine(void* nullPointer);
void registerInternetConnectionStatusUpdateThread();

#endif  /* GTK_NETWORKCONNECTIVITYTHREAD_H_ */

