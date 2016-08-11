
#include "timeThread.h"

pthread_t timeStatusThread;

kioskTimes kioskTimeData;

std::string getOpeningTime() {
        FILE *fp;
        char path[1035];

        /* Open the command for reading. */
        fp = popen("cat hoursOfOperation/openingTime.cfg", "r");
        if (fp == NULL) {
                printf("Failed to run command\n" );
                return "";
        }

        /* Read the output a line at a time - output it. */
        while (fgets(path, sizeof(path)-1, fp) != NULL) {
                printf("%s", path);
        }

        /* close */
        pclose(fp);

        return (std::string) path;
}

std::string getClosingTime() {
        FILE *fp;
        char path[1035];

        /* Open the command for reading. */
        fp = popen("cat hoursOfOperation/closingTime.cfg", "r");
        if (fp == NULL) {
                printf("Failed to run command\n" );
                return "";
        }

        /* Read the output a line at a time - output it. */
        while (fgets(path, sizeof(path)-1, fp) != NULL) {
                printf("%s", path);
        }

        /* close */
        pclose(fp);

        return (std::string) path;
}

std::string getCurrentSystemTimeString_Hours() {
        FILE *fp;
        char path[1035];

        /* Open the command for reading. */
        fp = popen("date +\"%H\"", "r");
        if (fp == NULL) {
                printf("Failed to run command\n" );
                return "";
        }

        /* Read the output a line at a time - output it. */
        while (fgets(path, sizeof(path)-1, fp) != NULL) {
                printf("%s", path);
        }

        /* close */
        pclose(fp);

        return (std::string) path;
}

std::string getCurrentSystemTimeString_Minutes() {
        FILE *fp;
        char path[1035];

        /* Open the command for reading. */
        fp = popen("date +\"%M\"", "r");
        if (fp == NULL) {
                printf("Failed to run command\n" );
                return "";
        }

        /* Read the output a line at a time - output it. */
        while (fgets(path, sizeof(path)-1, fp) != NULL) {
                printf("%s", path);
        }

        /* close */
        pclose(fp);

        return (std::string) path;
}

int convertStringToInteger(std::string const &stringString) {
//      return atoi(stringString.c_str());
        return (int)strtol(stringString.c_str(), NULL, 0);
}

int getIntOpeningTime_Hours(std::string const &timeString) {
        std::string delimiter = ":";
        return convertStringToInteger(timeString.substr(0, timeString.find(delimiter)));
}

int getIntOpeningTime_Minutes(std::string const &timeString) {
        std::string delimiter = ":";
        return convertStringToInteger(timeString.substr(1 + timeString.find(delimiter), timeString.length()));
}

int getIntClosingTime_Hours(std::string const &timeString) {
        std::string delimiter = ":";
        return convertStringToInteger(timeString.substr(0, timeString.find(delimiter)));
}

int getIntClosingTime_Minutes(std::string const &timeString) {
        std::string delimiter = ":";
        return convertStringToInteger(timeString.substr(1 + timeString.find(delimiter), timeString.length()));
}

std::string getCurrentSystemTime_Hour(std::string const &timeString) {
        std::string delimiter = " ";
        return timeString.substr(0, timeString.find(delimiter));
}

int getIntCurrentSystemTime_Hours(std::string const &timeString) {
        return convertStringToInteger(timeString);
}

int getIntCurrentSystemTime_Minutes(std::string const &timeString) {
        return convertStringToInteger(timeString);
}

//std::string buildCurrentTime(int hours, int minutes) {
//
//}

void updateTimes() {
	//getOpeningTime();
	//getClosingTime();
	//getCurrentSystemTimeString_Hours();
	//getCurrentSystemTimeString_Minutes();
	kioskTimeData.openingTime = getOpeningTime();
	kioskTimeData.closingTime = getClosingTime();
	kioskTimeData.openingTime_Hours = getIntOpeningTime_Hours(kioskTimeData.openingTime);
	kioskTimeData.openingTime_Minutes = getIntOpeningTime_Minutes(kioskTimeData.openingTime);
	kioskTimeData.closingTime_Hours = getIntClosingTime_Hours(kioskTimeData.closingTime);
	kioskTimeData.closingTime_Minutes = getIntClosingTime_Minutes(kioskTimeData.closingTime);
	kioskTimeData.currentTime_Hours = getIntCurrentSystemTime_Hours(getCurrentSystemTimeString_Hours());
	kioskTimeData.currentTime_Minutes = getIntCurrentSystemTime_Minutes(getCurrentSystemTimeString_Minutes());
}

//returns void* so that you can pass data back to calling function if necessary
void* timeStatusThreadUpdateThreadRoutine(void* nullPointer){
	while(1){
		updateTimes();
		sleep (20); //update every minute
	}
	return NULL ;
}

void registerTimeStatusThreadUpdateThread() {
	if (0 != pthread_create(&timeStatusThread, NULL, &timeStatusThreadUpdateThreadRoutine, NULL)){
		printf("something went wrong with creating registerTimeStatusThreadUpdateThread\n");
	} else {
		printf("registerTimeStatusThreadUpdateThread registered correctly\n");
	}

}
