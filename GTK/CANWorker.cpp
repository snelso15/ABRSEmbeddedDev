/*
 * CANWorker.cpp
 *
 *  Created on: Mar 4, 2016
 *      Author: snelso
 */

#include "CANWorker.h"

CANStatus *globalCANStat = new CANStatus;

CANWorker::CANWorker(GAsyncQueue *CANQ, GAsyncQueue *navQ){
	this->CANQ =CANQ;
	this->navQ =navQ;
	this->CANStat = globalCANStat;
	this->rxMsgs = new std::queue <CANMsg>;

	initializeCAN(MASTER_ID, 1);
}

void CANWorker::processTasks() {

	///////////////
	//DEBUG
	logText.append("CW - process can");
	LOG();
	///////////////

	processCANMessages();

	///////////////
	//DEBUG
	logText.append("CW - process internal");
	LOG();
	///////////////

	processInternalMessages();

	///////////////
	//DEBUG
	logText.append("CW - ping stat");
	LOG();
	///////////////

	pingStatus();

	///////////////
	//DEBUG
	logText.append("CW - Manage Acks");
	LOG();
	///////////////

	manageAcks();

	///////////////
	//DEBUG
	logText.append("CW - Done Iteration");
	LOG();
	///////////////
}

void CANWorker::processUnlockBikeAck(CANMsg msg){
	if(CANStat->getRack(msg.senderId)->ackType == UnlockBikeAck){
		CANStat->getRack(msg.senderId)->clearAckPhase();
	}
}

void CANWorker::processReturnBikeAck(CANMsg msg){
	if(CANStat->getRack(msg.senderId)->ackType == ReturnBikeAck){
		CANStat->getRack(msg.senderId)->clearAckPhase();
	}
}

void CANWorker::pingStatus(){
	if(CANStat->statusPing >= ITERATIONS_BEFORE_STATUS_PING){
		CANStat->statusPing = 0;
		CANStat->resetAllStatusPhases();
		printf("Sending status ping to everyone...\n");
		sendStatusReq();
	} else {
		CANStat->statusPing++;
	}
}

void CANWorker::processStatusResponse(CANMsg msg){
	CANStat->getRack(msg.senderId)->clearStatusPhase();
	int bikeID = 0;

	//if bike present, set true and add id, else, set false and bikeID to 0
	if(msg.data[1]){
		CANStat->getRack(msg.senderId)->bikePresent = true;
		bikeID = (int)((msg.data[2] << 8) | msg.data[3]);
	} else {
		CANStat->getRack(msg.senderId)->bikePresent = false;
	}
	CANStat->getRack(msg.senderId)->heldBikeId = bikeID;

	CANStat->getRack(msg.senderId)->batLevel = msg.data[5];
}

void CANWorker::processBikeReturnedNotif(CANMsg msg) {
	CANStat->getRack(msg.senderId)->bikePresent = true;
	int bikeID = (int)(msg.data[1] << 8) | msg.data[2];
	CANStat->getRack(msg.senderId)->heldBikeId = bikeID;
	CANStat->getRack(msg.senderId)->batLevel = msg.data[3];
	printf("sending bike returned ack to: %i....bike ID that was returned: %i\n", msg.senderId, bikeID);
	sendBikeReturnedAck(msg.senderId);
	if(kioskBeginReturn(0xA000)){
		pushToNavQ('r', 0xA000);
	} else if(kioskBeginReturn(0xA001)){
		pushToNavQ('r', 0xA001);
	} else{
		//pushToNavQ('r', 0xA000); //for now, just pretend it worked anyway
	}
}

//TODO - add code to process any other internal messages sent to CAN worker... does a customer need to consult kiosk before return?
void CANWorker::processInternalMessages() {
	CANQData qMsg = tryPopCANQ();
	while(qMsg.dataAvailable){//TODO - add timeout to ensure this can't run forever
		printf("Sending bike unlock msg to %i...\n", qMsg.idToUnlock);
		sendUnlockBikeReq(qMsg.idToUnlock);
		CANStat->getRack(qMsg.idToUnlock)->ackPhase = 1;
		CANStat->getRack(qMsg.idToUnlock)->ackType = UnlockBikeAck;
		qMsg = tryPopCANQ();
	}
}

void CANWorker::manageAcks() {
	for(int i = 1; i <= NUM_RACKS; i++){
		RackStatus *rackStat = CANStat->getRack(i);
		if(rackStat->ackPhase){
			if(rackStat->ackPhase > ACK_ITERATIONS_BEFORE_TIMEOUT){
				//tried too many times to receive ack , time to resend the message
				if(rackStat->ackType == UnlockBikeAck){
					printf("ackPhase timed out, resending unlockbikereq to: %i\n", i);
					sendUnlockBikeReq(i);
					rackStat->ackPhase = 1;
				}
				if(rackStat->ackType == ReturnBikeAck){
					//TODO - add logic for bike return req if needed
				}
			} else{
				rackStat->ackPhase = rackStat->ackPhase + 1; //increment ack phase
			}
		}
		if(rackStat->statusPhase){
			if(rackStat->statusPhase > ACK_ITERATIONS_BEFORE_TIMEOUT){
				//tried too many times, time to resend the message
				printf("statusPhase timed out, resending indiv status req to: %i\n", i);
				sendIndivStatusReq(i);
				rackStat->statusPhase = 1;
			} else{
				rackStat->statusPhase = rackStat->statusPhase + 1; //increment ack phase
			}
		}
	}
}

CANWorker::~CANWorker() {
	delete this->CANStat;
	delete this->rxMsgs;
}

void CANWorker::processCANMessages() {
	while(!rxMsgs->empty()){//
		CANMsg msg = rxMsgs->front();
		rxMsgs->pop();
		if((int)msg.data[0] == UnlockBikeAck){
			printf("Received an unlock ack from: %i\n", msg.senderId);
			processUnlockBikeAck(msg);
		}
		if((int)msg.data[0] == ReturnBikeAck){

		}
		if((int)msg.data[0] == BikeReturnedNotif){
			printf("Received a bike returned notif from: %i\n", msg.senderId);
			processBikeReturnedNotif(msg);
		}
		if((int)msg.data[0] == StatusResp){
			printf("Received a status resp from: %i\n", msg.senderId);
			processStatusResponse(msg);
		}
	}
}

void CANWorker::manageRXBuffer() {
//	int maxPerIteration = 10;
//	int count = 0;

	///////////////
	//DEBUG
	logText.append("CW - Pulling buffer");
	LOG();
	///////////////

	CANMsg msg;

	int bufNum = isRxMsgPending();

	///////////////
	//DEBUG
	logText.append("CW - bufnum equals ");
	appendInt(bufNum);
	logText.append(".");
	LOG();
	///////////////

	while(bufNum){ //|| count < maxPerIteration){
		readCANMsg(bufNum-1, &msg);
		///////////////
		//DEBUG
		logText.append("CW - pushing msg: ");
		appendInt(msg.data[0]);
		logText.append(" ");
		appendInt(msg.data[1]);
		logText.append(" ");
		appendInt(msg.data[2]);
		logText.append(" ");
		appendInt(msg.data[3]);
		logText.append(" ");
		appendInt(msg.data[4]);
		logText.append(" ");
		appendInt(msg.data[5]);
		logText.append(" ");
		appendInt(msg.data[6]);
		logText.append(" ");
		appendInt(msg.data[7]);
		logText.append(".");
		LOG();
		///////////////
		//printf("rx manager got CAN msg!...data: %i, %i, %i, %i, %i, %i, %i, %i\n", msg.data[0], msg.data[1], msg.data[2], msg.data[3], msg.data[4], msg.data[5], msg.data[6], msg.data[7]);
		rxMsgs->push(msg);
		//count++;
		bufNum = isRxMsgPending();
	}

	///////////////
	//DEBUG
	logText.append("CW - done, leaving cb");
	LOG();
	///////////////
}

void CANWorker::runRXBufferManager() {
	manageRXBuffer();
}

void CANWorker::runWorker() {
	processTasks();
}

CANQData CANWorker::tryPopCANQ(){
	//create data wrapper
	CANQData CANQVal;
	gpointer data = g_async_queue_try_pop(CANQ);
	if(data == NULL){
		return CANQVal;
	} else{
		//create copy so you can deallocate memory on heap
		CANQVal = *(CANQData *) data;  //TODO - test this line, not sure if it will work
		delete data;
		return CANQVal;
	}
}

void CANWorker::pushToNavQ(char key, unsigned int bikeID){
	navQData *navQMsg = new navQData;
	navQMsg->key = key;
	navQMsg->bikeID = bikeID;
	navQMsg->dataAvailable = true;
	g_async_queue_push(navQ, (gpointer)navQMsg);
}
