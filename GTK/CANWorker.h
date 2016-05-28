/*
 * CANWorker.h
 *
 *  Created on: Mar 4, 2016
 *      Author: snelso
 */

#ifndef GTK_CANWORKER_H_
#define GTK_CANWORKER_H_

#include <gtk/gtk.h>
#include "MCP25625.h"
#include "ABRSMsgs.h"
#include "queueTypes.h"
//#include <queue>
#include "backendCommunicator.h"
#include "CANThread.h"

#include "ABRSDebug.h"


#define ACK_ITERATIONS_BEFORE_TIMEOUT 20
#define ITERATIONS_BEFORE_STATUS_PING 20
#define NUM_RACKS 5


enum CANMsgIdentifier{
	CANMsgNone = 0,
	UnlockBike,
	UnlockBikeAck,
	ReturnBikeReq,
	ReturnBikeAck,
	BikeReturnedNotif,
	BikeReturnedAck,
	StatusReq,
	StatusResp
};

struct RackStatus{
	int ackPhase = 0;
	CANMsgIdentifier ackType = CANMsgNone;
	int statusPhase = 0;
	int batLevel = 0;
	bool bikePresent = false;
	int heldBikeId = 0;
	void clearAckPhase(){
		ackPhase = 0;
		ackType = CANMsgNone;
	}
	void clearStatusPhase(){
		statusPhase = 0;
	}
};

struct CANStatus{
	RackStatus rackStatus[NUM_RACKS];
	int statusPing = 0;
	void updateStatus(RackStatus stat, int rackNum){
		rackStatus[rackNum] = stat;
	}
	void resetAllStatusPhases(){
		int i;
		for (i = 1; i <= NUM_RACKS; i++){
			rackStatus[i].clearStatusPhase();
		}
	}
	bool needsAck(int rackNum){
		if(rackStatus[rackNum].ackPhase) {return true;}
		else {return false;}
	}
	bool needsStatus(int rackNum){
		if(rackStatus[rackNum].statusPhase) {return true;}
		else {return false;}
	}
	RackStatus * getRack(int rackID){
		return &rackStatus[rackID-1];
	}
};

extern CANStatus *globalCANStat;

class CANWorker {

private:
	GAsyncQueue *CANQ;
	GAsyncQueue *navQ;
	CANStatus *CANStat;
//	std::queue<CANMsg> *rxMsgs;

	//functions
	CANQData tryPopCANQ();
	void pushToNavQ(char key, unsigned int bikeID);
	void processTasks();
	void processCANMessages();
	void processInternalMessages();
	void processUnlockBikeAck(CANMsg msg);
	void processReturnBikeAck(CANMsg msg);
	void processBikeReturnedNotif(CANMsg msg);
	void processStatusResponse(CANMsg msg);
	void manageAcks();
//	void manageRXBuffer();
	void pingStatus();


public:
//	void runRXBufferManager();
	void runWorker();
	CANWorker(GAsyncQueue *CANQ, GAsyncQueue *navQ);
	~CANWorker();
};

#endif /* GTK_CANWORKER_H_ */
