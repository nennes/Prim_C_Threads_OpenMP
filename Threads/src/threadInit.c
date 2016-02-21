int threadInit()
{
	int tempI,tempJ, temp;
	int returnCode =0;

	int rowsPerThread, extraRowsPerThread;
	
	nodeData=malloc(nodeNumber * sizeof(*nodeData));
	for (temp=0; temp<nodeNumber; temp++) 
	{
		nodeData[temp] = malloc(6 * sizeof(int));
	}
	/*
	This table will be used during the calculations to hold
	temporary data.
	*/
	
	pthread_setconcurrency(numberThreads);

	pthread_barrier_init( &barrier, NULL, numberThreads);

	idThreads=(pthread_t *)malloc(numberThreads*sizeof(pthread_t));
	/*
	Table that holds the thread ids
	*/
	
	nameThreads = malloc(numberThreads*sizeof(int));
	/*
	Table that holds the thread names, here represented by numbers.
	*/
		
	for(tempI=0;tempI<nodeNumber;tempI++)
	{
		for(tempJ=0;tempJ<6;tempJ++)
		{
			if (tempJ==0)
				nodeData[tempI][tempJ]=tempI;
			else
				nodeData[tempI][tempJ]=0;
			
		}
	}
	/*
	Initialization of the table used during the calculations.
	The columns used have the following meaning:
	Column 0: The number of the node.
	Column 1: 0 if it is not part of the graph, 1 if it is.
	Column 2: minValue of linkage at this node in the current round.
	Column 3: Node with which minValue is found.
	Column 4: Node that will be its father in the tree.
	Column 5: 0 if it has more potential children, 1 if we are done processing it.
	*/
	for(tempI=0;tempI<nodeNumber;tempI++)
	{
		for(tempJ=0;tempJ<nodeNumber;tempJ++)
		{
			graphTree[tempI][tempJ]=0;
		}
	}
	
	
	
	for(temp=0;temp<numberThreads;temp++)
	{
		nameThreads[temp]=temp;
	}

	

	/*
	--Timed Version--
	*/

	//gettimeofday(&time1,NULL);
	
	for ( temp=0; temp<numberThreads; temp++ ) 
	{	
		pthread_create(&idThreads[temp],NULL,farmer,(void *)&nameThreads[temp]);
	}

	for ( temp=0; temp<numberThreads; temp++ )
	{
		pthread_join(idThreads[temp],NULL);
	}
	//gettimeofday(&time2,NULL);
	
	printf("Calculation complete.\n");
	//printf("Total computation time: %4.3f milliseconds.\n", (double)(((double)(time2.tv_sec * 1000000 + time2.tv_usec) - (double)(time1.tv_sec * 1000000 + time1.tv_usec))/1000));

	
	 printf("Prim's Tree Adjacency matrix:\n");
		for( tempI=0; tempI<nodeNumber; tempI++ )
		{
			for( tempJ=0; tempJ<nodeNumber; tempJ++ )
			{
				printf("%d\t",graphTree[tempI][tempJ]);
			}
			printf("\n");
			
		}

	return returnCode;

}
