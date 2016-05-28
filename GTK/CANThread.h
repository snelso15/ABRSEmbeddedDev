/*
 * CANThread.h
 *
 *  Created on: May 27, 2016
 *      Author: snelso
 */

#ifndef GTK_CANTHREAD_H_
#define GTK_CANTHREAD_H_

#include "MCP25625.h"
#include "ABRSMsgs.h"
#include "queueTypes.h"
#include <queue>
#include <semaphore.h>

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void registerCanThread();

#endif /* GTK_CANTHREAD_H_ */
