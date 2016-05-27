#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>


std::string getABRS_Occurances()
{
	FILE *fp;
	char path[1035];

	/* Open the command for reading. */
//	fp = popen("ps aux | grep foobar | wc -l" , "r");
	fp = popen("ps aux | grep ABRSEmbeddedDevTest | wc -l" , "r");

	if (fp == NULL) {
		printf("Failed to run command\n" );
		return "";
	}

	/* Read the output a line at a time - output it. */
	while (fgets(path, sizeof(path)-1, fp) != NULL) {
		//printf("%s", path);
	}

	/* close */
	pclose(fp);

	return (std::string) path;
}


std::string start_ABRS()
{
        FILE *fp;
        char path[1035];

        /* Open the command for reading. */
        fp = popen("/home/pi/ABRSEmbeddedDevTest &" , "r");
//	 fp = popen("/home/tj/c/foobar &" , "r");

        if (fp == NULL) {
                printf("Failed to run command\n" );
                return "";
        }

        /* Read the output a line at a time - output it. */
//        while (fgets(path, sizeof(path)-1, fp) != NULL) {
//                printf("%s", path);
//        }

        /* close */
        pclose(fp);

        return "";
}



int main (void)
{
	while (1) {
		std::string numABRS_String;	
		numABRS_String = getABRS_Occurances();

	//	printf("%s\n", numABRS_String.data());
	
		int i_dec = atoi (numABRS_String.data());
		printf("%d\n", i_dec - 2);

		int actualOccurances = i_dec - 2;
	
	
	
		if (actualOccurances < 1)
		{
			printf("Start the Program\n");
			start_ABRS();
			printf("Sleeping 10 seconds\n");
			sleep (10);
		}
		else
		{
			sleep (1);
		}
	}

	return 1;
}
