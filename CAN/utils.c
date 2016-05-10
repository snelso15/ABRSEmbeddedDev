/*
 * utils.c
 *
 *  Created on: Jul 18, 2015
 *      Author: abrs-team-2
 */

#include "utils.h"

void busyWait(int cycles){
	volatile int dummy = 0;
	int i = 0;
	for(i = 0; i < cycles; i++) {
		dummy++;
	}
}
