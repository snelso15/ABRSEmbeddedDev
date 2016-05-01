#ifndef BACKENDCOMMUNICATOR_H
#define BACKENDCOMMUNICATOR_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <curl/curl.h>


#include "backendFunctionality.h"

extern char availableBicycles[500][30];
extern int availableBicycleLength;

// Buffers for safe int getters
extern char line[256];
extern int isint;

int doRent();
void beginRental();
void beginReturn();
bool kioskBeginRental();
bool kioskBeginReturn();

bool is_transaction_complete();

#endif
