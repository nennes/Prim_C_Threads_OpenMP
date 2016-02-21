#include <stdio.h>
#include <unistd.h>
/*
Used also for parapeter passing with getopt
*/
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>


#include "lib/functionList.h"
#include "lib/globalVars.h"


#include "src/readAdjacencyMatrix.c"
#include "src/threadInit.c"
#include "src/farmer.c"

int main(int argc, char **argv)
{
	int returnCode =0;
	char argument;
	int argSize = 0;
	int temp;



	if ((argument = getopt (argc, argv, "t:")) != -1)
	{	
		if (argument == 't')
		{	
			/*
			If the user has typed -t as argument name.
			*/
			if(argSize=strlen(optarg))
			{
				/*
				If the user has typed a value for the argument t.
				*/
				for(temp=0;temp<argSize;temp++)
				{
					/*
					Check if the input is composed of digits.
					*/
					if (!isdigit(optarg[temp]))
					{
						/*
						Non digit character found.
						Invalid input.
						*/
						printf("The value for argument t is not non-negative digits.\n");
						printf("Please type -t [NUMBER] to set\n"); 
						printf("the desired number of threads.\n");
						returnCode = 100;
					}
				}
				
				if(!returnCode)
				{
					/*
					No error has been encountered. The input is in correct format.
					*/
					if(numberThreads = atoi(optarg))
					{
						/*
						Positive number of threads. All is well.
						*/
						printf("The desired number of threads is %d.\n", numberThreads);
					}
					else
					{
						/*
						Non-positive number of threads. Failure.
						*/
						printf("The number for argument t is not positive.\n");
						printf("Please type -t [POSITIVE NUMBER] to set\n"); 
						printf("the desired number of threads.\n");
						returnCode = 101;
					}
				}
			
			}
			else
			{
				/*
				The user has not specified a value for the argument t.
				*/
				printf("You have not inserted a value for argument t.\n");
				printf("Please type -t [NUMBER] to set\n"); 
				printf("the desired number of threads.\n");
				returnCode = 102;
			}
		}
		else
		{
			printf("You have typed an invalid argument.\n");
			printf("Please use option -t to set\n"); 
			printf("the desired number of threads.\n");
			returnCode = 103;
		}
	}
	else
	{
		printf("Thread number not specified.\n");
        printf("Please use option -t to set\n"); 
		printf("the desired number of threads.\n");
		returnCode = 104;
	}
	
	if(!returnCode)
				{
					/*
					No error has been encountered. The input data is correct..
					*/
					if(returnCode=readAdjacencyMatrix())
						return returnCode;
					
					if(returnCode=threadInit())
						return returnCode;
					
				}
	
	
	return returnCode;
	/*
	Return the proper code.
	0 for success, other for failure.
	*/
}

