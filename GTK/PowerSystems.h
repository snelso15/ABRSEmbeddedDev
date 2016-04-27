/*
 * PowerSystems.h
 *
 *  Created on: Apr 3, 2016
 *      Author: snelso
 */

#ifndef POWERSYSTEMS_H_
#define POWERSYSTEMS_H_

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <wiringPi.h>
#include <time.h>

int getBatteryPercentage();
void periodic_battery_checkup();
void init_battery_comms();


#endif /* POWERSYSTEMS_H_ */
