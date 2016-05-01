/*
 * teensyCommunicator.cpp
 *
 *  Created on: Feb 19, 2016
 *      Author: tj
 */
//#define DEBUG
#include "teensyCommunicator.h"

uint8_t ACK[4] = {0xFF, 0xAA, 0x01, 0xAA};
uint8_t NACK[4] = {0xFF, 0xBB, 0x01, 0xBB};
uint8_t MPTY[4] = {0xFF, 0xAB, 0x01, 0xAB};
uint8_t LCDON[4] = {0xFF,0xCC, 0x01, 0xCC};
uint8_t LCDOFF[4] = {0xFF, 0xDD, 0x01, 0xDD};
uint8_t READ[4] = {0xFF, 0xEE, 0x01, 0xEE};
uint8_t NUM0[4] = {0xFF, 0x30, 0x01, 0x30};
uint8_t NUM1[4] = {0xFF, 0x31, 0x01, 0x31};
uint8_t NUM2[4] = {0xFF, 0x32, 0x01, 0x32};
uint8_t NUM3[4] = {0xFF, 0x33, 0x01, 0x33};
uint8_t NUM4[4] = {0xFF, 0x34, 0x01, 0x34};
uint8_t NUM5[4] = {0xFF, 0x35, 0x01, 0x35};
uint8_t NUM6[4] = {0xFF, 0x36, 0x01, 0x36};
uint8_t NUM7[4] = {0xFF, 0x37, 0x01, 0x37};
uint8_t NUM8[4] = {0xFF, 0x38, 0x01, 0x38};
uint8_t NUM9[4] = {0xFF, 0x39, 0x01, 0x39};
uint8_t LETA[4] = {0xFF, 0x41, 0x01, 0x41};
uint8_t LETB[4] = {0xFF, 0x42, 0x01, 0x42};
uint8_t LETC[4] = {0xFF, 0x43, 0x01, 0x43};
uint8_t LETD[4] = {0xFF, 0x44, 0x01, 0x44};
uint8_t LETE[4] = {0xFF, 0x45, 0x01, 0x45};
uint8_t LETF[4] = {0xFF, 0x46, 0x01, 0x46};
uint8_t LETG[4] = {0xFF, 0x47, 0x01, 0x47};
uint8_t LETH[4] = {0xFF, 0x48, 0x01, 0x48};

// channel is the wiringPi name for the chip select (or chip enable) pin.
// Set this to 0 or 1, depending on how it's connected.
static const int CHANNEL = 1;

teensyCommunicator::teensyCommunicator() {
	wiringPiSPISetup(CHANNEL, 1000000);//cutting speed in half seemed to keep the teensy from crashing

}

teensyCommunicator::~teensyCommunicator() {
	// TODO Auto-generated destructor stub
}


// perform the actual transfer of bytes
uint8_t teensyCommunicator::processByte(uint8_t value)
{
   unsigned char buffer[1];
   buffer[0] = value;
   wiringPiSPIDataRW(CHANNEL, buffer, 1);
   #ifdef DEBUG
   printf ("debug: in uint8_t processByte(uint8_t value) buffer = %c\n" ,(int)buffer[0]);
   #endif
   //usleep(50000);
   usleep(500);
   return buffer[0];
}

// send/receive the packet
void  teensyCommunicator::processPacket(uint8_t *packet)
{
   for (int i = 0; i < 4; i++)
   {
      packet[i] = processByte(packet[i]);
   }
}

// give a packet ACK,NACK,Read,LCDON/OFF
void teensyCommunicator::initializePacket(uint8_t *packet, uint8_t *packetArray)
{
   for (int i = 0; i < 4; i++)
   {
      packetArray[i] = packet[i];
   }
}

// print the 4 bytes of a packet -- for debugging
void teensyCommunicator::printPacket(uint8_t *packet)
{
   for (int i = 0; i < 4; i++)
   {
	  #ifdef DEBUG
      printf("%d\n", (int)(packet[i]));
	  #endif
   }
}

char* teensyCommunicator::identifyPacket(uint8_t *packet)
{
   char *name;
   if (((int)packet[0] != 0xFF)
    && ((int)packet[2] != 0x01)
    && ((int)packet[1] != (int)packet[3]))
   {
      name = "ERR";
   }
   else
   {
      switch((int)packet[1])
      {
         case 0xAA:
	 {
	    name = "ACK";
            break;
	 }
         case 0xBB:
         {
            name = "NACK";
            break;
         }
	 case 0xAB:
	 {
	    name = "MPTY";
	    break;
	 }
         case 0xCC:
         {
            name = "LCDON";
            break;
         }
         case 0xDD:
         {
            name = "LCDOFF";
            break;
         }
         case 0xEE:
         {
            name = "READ";
            break;
         }
         case 0x30:
         {
            name = "NUM0";
            break;
         }
         case 0x31:
         {
            name = "NUM1";
            break;
         }
         case 0x32:
         {
            name = "NUM2";
            break;
         }
         case 0x33:
         {
            name = "NUM3";
            break;
         }
         case 0x34:
         {
            name = "NUM4";
            break;
         }
         case 0x35:
         {
            name = "NUM5";
            break;
         }
         case 0x36:
         {
            name = "NUM6";
            break;
         }
         case 0x37:
         {
            name = "NUM7";
            break;
         }
         case 0x38:
         {
            name = "NUM8";
            break;
         }
         case 0x39:
         {
            name = "NUM9";
            break;
         }
         case 0x41:
         {
            name = "LETA";
            break;
         }
         case 0x42:
         {
            name = "LETB";
            break;
         }
         case 0x43:
         {
            name = "LETC";
            break;
         }
         case 0x44:
         {
            name = "LETD";
            break;
         }
         case 0x45:
         {
            name = "LETE";
            break;
         }
         case 0x46:
         {
            name = "LETF";
            break;
         }
         case 0x47:
         {
            name = "LETG";
            break;
         }
         case 0x48:
         {
            name = "LETH";
            break;
         }
	 default:
            break;
      }
   }
   return name;
}

char teensyCommunicator::checkButtonPress(void)
{
	uint8_t final = 0;
	int fd, result;
	   uint8_t i = 255;
	   uint8_t SPIRxVal = 0;
	   unsigned char buffer[1];

	   uint8_t thisPacket[4];

	   #ifdef DEBUG
	   printf("Initializing SPI to Teensy\n");
	   #endif

	   // Configure the interface.
	   // CHANNEL indicates chip select,
	   // 500000 indicates bus speed.
//	   fd = wiringPiSPISetup(CHANNEL, 1000000);//2000000);  should only do this once - check constructor

	   #ifdef DEBUG
	   printf("Init result: %d\n", fd);
	   #endif

	   processByte(0);
	   processByte(0);


	  // while(1)
	   {
	      //buffer[0] = i;
	      //wiringPiSPIDataRW(CHANNEL, buffer, sizeof(buffer));
	      //SPIRxVal = buffer[0];


	      //SPIRxVal = processByte(i);
	      // result = (int)SPIRxVal;

	      //cout << "buffer :" << result << endl;
	      i--;
	      if (i == 0) {i = 255;}
	      //usleep(500000);



	      // initialize packet
	      uint8_t packetArray[4] = {0x00, 0x00, 0x00, 0x00};
	      initializePacket(READ, packetArray);
	      printPacket(packetArray);

	      // process packet -- i.e. send and receive bytes
	      processPacket(packetArray);
	      //printPacket(packetArray);

	      processByte(0);
	      usleep(100000);
	      initializePacket(READ, packetArray);
	      printPacket(packetArray);

	      // process packet -- i.e. send and receive bytes
	      processPacket(packetArray);
	      //printPacket(packetArray);
	      processByte(0);



		  #ifdef DEBUG
	      printf("ID: %s\n", identifyPacket(packetArray));
		  #endif
	      if(identifyPacket(packetArray) != "ERR")
	      {
	    	  final = packetArray[1];
			  #ifdef DEBUG
	          printf("send a ACK\n");
			  #endif
	          initializePacket(ACK, packetArray);
	          printPacket(packetArray);
	          processPacket(packetArray);
	          processByte(0);
	      }
	      else
	      {
			  #ifdef DEBUG
	          printf("send a NACK of zeros\n");
			  #endif
			  processByte(0);
			  processByte(0);
			  processByte(0);
			  processByte(0);
	      }
		  #ifdef DEBUG
	      printf("ID: %s\n", identifyPacket(packetArray));
		  #endif
	      if(identifyPacket(packetArray) != "ERR")
	      {
			  #ifdef DEBUG
	          printf("send a ACK\n");
			  #endif
	          initializePacket(ACK, packetArray);
	          printPacket(packetArray);
	          processPacket(packetArray);
	          processByte(0);
	      }
	      else
	      {
			  #ifdef DEBUG
	          printf("send a NACK of zeros\n");
			  #endif
			  processByte(0);
			  processByte(0);
			  processByte(0);
			  processByte(0);
	      }
		  #ifdef DEBUG
	      printf("\n");
		  #endif
	      //cout << endl;
	//      sleep(3);


	     // (processPacket(ACK));


	   }
	   return final;
}


int teensyCommunicator::activateLCDBoard(void)
{
    // initialize packet
    uint8_t packetArray[4] = {0x00, 0x00, 0x00, 0x00};
    initializePacket(LCDON, packetArray);
    printPacket(packetArray);

    // process packet -- i.e. send and receive bytes
    processPacket(packetArray);
    //printPacket(packetArray);

    processByte(0);
    usleep(100000);
    initializePacket(LCDON, packetArray);
    printPacket(packetArray);

    // process packet -- i.e. send and receive bytes
    processPacket(packetArray);
    //printPacket(packetArray);
    processByte(0);

	  if(identifyPacket(packetArray) != "ERR")
	  {
		  initializePacket(ACK, packetArray);
		  printPacket(packetArray);
		  processPacket(packetArray);
		  processByte(0);

	  }
	  else
	  {
	  processByte(0);
	  processByte(0);
	  processByte(0);
	  processByte(0);

	  }

		if(identifyPacket(packetArray) != "ERR")
		{
			initializePacket(ACK, packetArray);
			printPacket(packetArray);
			processPacket(packetArray);
			processByte(0);

		}
		else
		{
		processByte(0);
		processByte(0);
		processByte(0);
		processByte(0);

		}
		return 1;

}

int teensyCommunicator::deactivateLCDBoard(void)
{
    // initialize packet
    uint8_t packetArray[4] = {0x00, 0x00, 0x00, 0x00};
    initializePacket(LCDOFF, packetArray);
    printPacket(packetArray);

    // process packet -- i.e. send and receive bytes
    processPacket(packetArray);
    //printPacket(packetArray);

    processByte(0);
    usleep(100000);
    initializePacket(LCDOFF, packetArray);
    printPacket(packetArray);

    // process packet -- i.e. send and receive bytes
    processPacket(packetArray);
    //printPacket(packetArray);
    processByte(0);

	  if(identifyPacket(packetArray) != "ERR")
	  {
		  initializePacket(ACK, packetArray);
		  printPacket(packetArray);
		  processPacket(packetArray);
		  processByte(0);

	  }
	  else
	  {
	  processByte(0);
	  processByte(0);
	  processByte(0);
	  processByte(0);

	  }

		if(identifyPacket(packetArray) != "ERR")
		{
			initializePacket(ACK, packetArray);
			printPacket(packetArray);
			processPacket(packetArray);
			processByte(0);

		}
		else
		{
		processByte(0);
		processByte(0);
		processByte(0);
		processByte(0);

		}
		return 1;

}
