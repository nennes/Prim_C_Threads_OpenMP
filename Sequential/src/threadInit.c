int threadInit()
{
	int tempI,tempJ, temp;
	int returnCode =0;
	
	nodeData=malloc(nodeNumber * sizeof(*nodeData));
	for (temp=0; temp<nodeNumber; temp++) 
	{
		nodeData[temp] = malloc(5 * sizeof(int));
	}
	/*
	This table will be used during the calculations to hold
	temporary data.
	*/
	
		
	for(tempI=0;tempI<nodeNumber;tempI++)
	{
		for(tempJ=0;tempJ<5;tempJ++)
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
	*/
	for(tempI=0;tempI<nodeNumber;tempI++)
	{
		for(tempJ=0;tempJ<nodeNumber;tempJ++)
		{
			graphTree[tempI][tempJ]=0;
		}
	}
	
	gettimeofday(&time1,NULL);
		
	
	farmer();

	gettimeofday(&time2,NULL);
	printf("Calculation complete.\n");


	printf("Total computation time: %ld microsecs.\n", ((time2.tv_sec * 1000000 + time2.tv_usec) - (time1.tv_sec * 1000000 + time1.tv_usec)));
	for( tempI=0; tempI<nodeNumber; tempI++ )
		{
			for( tempJ=0; tempJ<nodeNumber; tempJ++ )
			{
				printf("%d ",graphTree[tempI][tempJ]);
			}
			printf("\n");
			
		}

	return returnCode;

}
