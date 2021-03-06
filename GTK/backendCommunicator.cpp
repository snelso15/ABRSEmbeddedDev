#include "backendCommunicator.h"

char availableBicycles[500][30] = {"0012", "a2", "a3", "a4", "a5"};
int availableBicycleLength = 5;

// Buffers for safe integer getters
char line[256];
int isint;

int doRent() {
  int i;
  while(1) {
    system("clear");
    printf("%s \n", "ABRS Bike Rental Test");
    printf("Available Bicycles: ");
    for(i = 0; i < availableBicycleLength; i++) {
      if( (i+1) != availableBicycleLength ) {
	printf("%s,", availableBicycles[i]);
      } else {
	printf("%s \n", availableBicycles[i]);
      }
    }

    int task;
    while (1) {
      printf("\nTask (1-Rent|2-Return): ");

      fgets(line, sizeof line, stdin);
      isint = sscanf(line, "%d",&task);
      if (isint && ((task == 1 && availableBicycleLength > 0) || task == 2)) break;
    }

    if(task == 1) {
      beginRental();
    } else {
      beginReturn();
    }


    printf("Press Enter to Return to Main Screen.");
    fgets(line, sizeof line, stdin);
  }


  return 0;
}

bool is_transaction_complete() {
  return false;
}

void beginRental() {
    int one_time_code;
    while (1) {
      printf("\nEnter One-Time Use Code: ");

      fgets(line, sizeof line, stdin);
      isint = sscanf(line, "%d",&one_time_code);
      if (isint) break;

    }


    int total_bicycles;
    while (1) {
      printf("\nHow many bicycles would you like to rent: ");

      fgets(line, sizeof line, stdin);
      isint = sscanf(line, "%d",&total_bicycles);
      if (isint && total_bicycles > 0 && total_bicycles < (availableBicycleLength+1)) break;
    }

    system("clear");
    printf("%s \n", "Processing rental\n");

    char bike_id_buffer[1000] = "";
    int i;
    for(i = 0; i < total_bicycles; i++) {
      if( (i+1) == total_bicycles ) {
	sprintf(bike_id_buffer, "%s%s", bike_id_buffer, availableBicycles[availableBicycleLength-1-i]);
      } else {
	sprintf(bike_id_buffer, "%s%s,", bike_id_buffer, availableBicycles[availableBicycleLength-1-i]);
      }
    }

    rental_response re = attemptRental(one_time_code, bike_id_buffer);

    switch(re) {
      case BAD_CODE:
	printf("The one-time use code provided was invalid.\n");
	break;

      case SUCCESS:
	printf("Rental successful.\n");
	availableBicycleLength += (0-total_bicycles);
	break;

      default:
	printf("An unknown error has occurred. Please try again.\n");
	break;
    }

    return;
}

void beginReturn() {
  printf("Please enter the bike ID: ");
  fgets(line, sizeof line, stdin);
  sscanf(line, "%s", availableBicycles[availableBicycleLength]);
  availableBicycleLength++;

  system("clear");
  printf("%s \n", "Processing return\n");

  rental_response re = attemptReturn(availableBicycles[availableBicycleLength-1]);

  switch(re) {
      case SUCCESS:
	printf("Return successful.\n");
	break;

      default:
	printf("An unknown error has occurred. Please try again.\n");
	availableBicycleLength--;
	break;
    }

  return;
}


int kioskBeginRental(int one_time_code, unsigned int bikeId) {

	bikeId = bikeId & 0xFF;

	char bikeToRent[5];
	bikeToRent[5];
	sprintf(bikeToRent, "A00%u", bikeId);

    printf("Processing rental, renting bike: %s\n", bikeToRent);

    rental_response re = attemptRental(one_time_code, bikeToRent);
    int successfullRent = 1;

    switch(re) {
    case BAD_CODE:
	printf("The one-time use code provided was invalid.\n");
	successfullRent = 2;
	break;

    case SUCCESS:
	printf("Rental successful.\n");
	successfullRent = 1;
	break;

    default:
	printf("An unknown error has occurred. Please try again.\n");
	successfullRent = 0;
	break;
    }

    return successfullRent;
}

bool kioskBeginReturn(unsigned int bikeId) {


	bikeId = bikeId & 0xFF;

	char bikeToReturn[5];
	sprintf(bikeToReturn, "A00%u", bikeId);

	bool successfullReturn = true;

	//sscanf(bikeToReturn, "%s", availableBicycles[availableBicycleLength]);

    printf("Processing rental, returning bike: %s\n", bikeToReturn);

	rental_response re = attemptReturn(bikeToReturn);

	switch(re) {
	  case SUCCESS:
		  printf("Return successful.\n");
		  successfullReturn = true;
		  break;

	  default:
		  printf("An unknown error has occurred. Please try again.\n");
		  availableBicycleLength--;
		  successfullReturn = false;
		  break;
	}

	return successfullReturn;
}

