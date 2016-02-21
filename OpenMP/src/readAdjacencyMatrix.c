int readAdjacencyMatrix() {
	/*
	Function used to read the data from the input file.
	That data will determine the size of the graph and
	its linkages (including weight).
	The file format will be the same as in:
	http://en.wikipedia.org/wiki/Adjacency_matrix
	with the following variation:
	0: Signals there is no link between nodes i and j
	Number > 0: Value of the linkage between i and j
	where i and j correspont to line and column numbers.
	*/

	FILE *fp;
	/*
	file descriptor used to handle the open file
	*/
	int returnCode =0;
	int temp=0;
	int tempI, tempJ;
	int x,y;
	char *str;
	int lineNumber;


	char charRead='-';
	char *bufferLine;
	long int countChars = 0; 
	int length = 0;
	int allocSize;
	/*
	Buffer for each line of the file.
	*/

	char *token;
	char *delimiter = "\t";

	chdir("AdjacencyMatrix");
	/*
	Change the working directory to the one that contains the graph data file.
	*/

	if((fp=fopen("AdjacencyMatrix.txt","r"))==NULL)
	{
		/*
		open file for reading, handle the event of an error
		*/
		printf("Error, file cannot be opened.\n");
		returnCode = 110;
	}
	else
	{
		/*
		First we need to determine the number of vertices.
		We will count the number of lines, this will equal 
		the number of nodes.
		*/
		while(charRead!=EOF) 
		{

			charRead = fgetc(fp);

			if(charRead=='\n')  nodeNumber++;

		}
		
		if(nodeNumber < numberThreads)
		{	
			/*
			We will not create threads that cannot be utilized.
			*/
			numberThreads = nodeNumber;
		}

		printf("Nodes found: %d Threads used: %d\n", nodeNumber, numberThreads);

		graphTable=malloc(nodeNumber * sizeof(int *));
		for (temp=0; temp<nodeNumber; temp++) 
		{
			graphTable[temp] = malloc(nodeNumber * sizeof(int));
		}
		/*
		This table will be used to store the initial graph data 
		extracted from the ipnut file.
		*/
		
		graphTree=malloc(nodeNumber * sizeof(int *));
		for (temp=0; temp<nodeNumber; temp++) 
		{
			graphTree[temp] = malloc(nodeNumber * sizeof(int));
		}
		/*
		This table will be used to store the final graph that
		will be stored in a file.
		*/
		printf("Memory Allocation OK.\n");
			
		allocSize = 10 * nodeNumber;
		/*
		We assume an initial amound of memory needed for each line.
		If we run out, we will reallocate space while reading the file.
		*/

		bufferLine = malloc(allocSize * sizeof(char));
		/*
		Memory allocation can be performed now.
		*/

		fseek(fp,0,SEEK_SET);
		lineNumber=0;

		/*
		Now we return the the start of the file in order to populate
		the table with the graph data.
		*/
		while(lineNumber < nodeNumber)
		{
			charRead='-';
			length=0;
			countChars=0;

			while ( (charRead != '\n') && (charRead != EOF) ) 
			{
				if(countChars == (10*nodeNumber)) 
				{ 
					/*
					The line is longer than expected, expanding the buffer.
					*/
					allocSize *= 2;
					/*
					Double the available buffer size.
					*/
					countChars = 0;
					bufferLine = realloc(bufferLine, allocSize); // re allocate memory.
				}
				charRead = getc(fp); 
				/* 
				Read the next character from the stream.
				*/

				bufferLine[length] = charRead;
				/*
				Write the character in the buffer.
				*/

				length++;
				countChars++;
			}

			graphTable[lineNumber][0] = atoi( strtok(bufferLine, delimiter) );

			for (temp=1; temp<nodeNumber; temp++) 
			{
				graphTable[lineNumber][temp] = atoi( strtok(NULL, delimiter) );
			}

			lineNumber++;
		}
		/*
		The file has now been loaded to the memory.
		We can stop working with the file, we do not
		need it any more.
		*/
		fclose(fp);
		/*
		Close the file stream.
		*/
		printf("Data Load OK.\n");

		maxWeight=0;
		/*
		Determine the maximum weight of the linkages.
		We need this to be able to set "infinite" to a 
		number larger than maxWeight.
		*/

		for(tempI=0;tempI<nodeNumber;tempI++)
		{
			for(tempJ=0;tempJ<nodeNumber;tempJ++)
			{
				if (graphTable[tempI][tempJ] > maxWeight)
				{
					maxWeight = graphTable[tempI][tempJ];
				}
				if (graphTable[tempI][tempJ] != graphTable[tempJ][tempI])
				{
					printf("\nError at line: %d\n", tempI);
					printf("\nExpected: %d\n", graphTable[tempI][tempJ]);
					printf("\nFound: %d\n", graphTable[tempJ][tempI]);
					return 1010;
				}
			}
		}
		printf("The input data is valid.\n");
		/*
		Now the maximum linkage value is available.
		*/

		printf("Maximum weight: %d\n", maxWeight);

	}

	free(bufferLine);
	
	return returnCode;
	/*
	Completion of the file scan.
	*/


}
