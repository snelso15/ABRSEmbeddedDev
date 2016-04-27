#include <stdio.h>
#include "MCP25625.h"
#include "utils.h"
#include "CANConstants.h"

int main(void){
	while(1){
		printf("Main running...\n");
		int err = initializeCAN( MASTER_ID);
		printf("ERR on init?...%i\n", err);
		setCANMode(MODE_LOOPBACK);
		uint8_t ret = readReg(REG_CANSTAT);
		printf("read val...%i\n", ret);
		busyWait(100000000);
	}
}
