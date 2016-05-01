/*
 * queueTypes.h
 *
 *  Created on: Mar 3, 2016
 *      Author: snelso
 */

#ifndef GTK_QUEUETYPES_H_
#define GTK_QUEUETYPES_H_

struct navQData{
	char key;
	int UIScreenWhenRegistered;
	bool dataAvailable = false;
};

struct numQData{
	int key;
	int UIScreenWhenRegistered;
	bool dataAvailable = false;
};

struct CANQData{
	int idToUnlock = 0;
	bool dataAvailable = false;
};

struct backendQData{
	bool dataAvailable = false;
};




#endif /* GTK_QUEUETYPES_H_ */
