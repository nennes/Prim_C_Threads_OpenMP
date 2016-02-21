#include <stdio.h>
#include <unistd.h>
/*
Used also for parapeter passing with getopt
*/
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
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
	
	if(returnCode=readAdjacencyMatrix())
		return returnCode;
	
	if(returnCode=threadInit())
		return returnCode;			
				
}

