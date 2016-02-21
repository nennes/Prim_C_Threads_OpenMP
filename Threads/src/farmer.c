int min(int x, int y)
{
	return ( x > y ) ? y : x;
}

void *farmer(void *args) 
{
	int *data=(int *)args;
	int number=*data;
	
	int tempCounter1, tempCounter2, tempCounter3;
	int globalMinValue, globalMinNode, globalMinNodeFather;
	int nodesPerThread, extraNodesPerThread;
	

	
	
	if(number== numberThreads -1)
	{
		/*
		--Init--
		The last thread will determine the node 
		that will be the root of the tree.
		The initialization of the workload follows.
		*/
		
		finishFlag=0;
		/*
		This allows the calculations to start.
		*/
		
		globalWeight=0;
		/*
		Initialize the globalWeight of the 
		tree by setting it to zero.
		*/
		
		srand ( time(NULL) );
		/* 
		The random numbers will be based on the current time.
		*/
		
		randomNode = rand() % nodeNumber;
		
		nodeData[randomNode][1]=1;

		/*
		The last thread will check the random node.
		The rest of the threads are not needed right now.
		*/	
	}
	
	pthread_barrier_wait(&barrier);
	/*
	All the threads wait until the initial schedule data is calculated.
	*/
	
	
	while(!finishFlag)
	{
		
		for( tempCounter1=(((nodeNumber/numberThreads)*number) + min(number, nodeNumber%numberThreads)); tempCounter1<(((nodeNumber/numberThreads)*(number+1)) + min((number+1), nodeNumber%numberThreads)); tempCounter1++ )
		{
			/*
			Every thread scans the nodes assigned to it calculating an optimal linkage for each node
			*/
			nodeData[tempCounter1][2]=maxWeight+1;
			/*
			Set the "minimum value found" to the maximum possible
			*/
			for( tempCounter2=0; tempCounter2<nodeNumber; tempCounter2++ )
			{
				/*
				Scan the current node in the graph Table for the minimum 
				linkage value. The linkages that will be tested will not
				already belong to the tree.
				*/
				
				if( (graphTable[tempCounter1][tempCounter2] > 0) && (graphTable[tempCounter1][tempCounter2] < nodeData[tempCounter1][2]) && (nodeData[tempCounter2][1]==0))
				{
					/*
					If this linkage has optimal weight and is not already in the tree
					*/
					nodeData[tempCounter1][2] = graphTable[tempCounter1][tempCounter2];
					/*
					Minimum Value
					*/
					nodeData[tempCounter1][3] = tempCounter2;
					/*
					Minimum Value Node
					*/
					nodeData[tempCounter1][4] = tempCounter1;
					/*
					Minimum Value Node's father
					*/

				}
			}
			/*
			At this point there can be only two outcomes:
			- An optimal new linkage has been discovered
			- This node has no possible linkages
			*/
		}
		
		pthread_barrier_wait(&barrier);
		
		if(number == numberThreads-1)
		{
			/*
			Schedule the workload of each thread dynamicallly.
			This is performed by the last thread.
			*/
			tempCounter2=0;
			globalMinValue = maxWeight+1;
			
			for( tempCounter1=0; tempCounter1<nodeNumber; tempCounter1++ )
			{
				if(nodeData[tempCounter1][1]==1)
				{
					/*
					For each node of the tree...
					*/
					tempCounter2++;
										
					if ((nodeData[tempCounter1][2] < globalMinValue) && (nodeData[tempCounter1][2] > 0))
					{
						/*
						If the minimum distance column contains a positive value
						compare it with to rest to find the minimum.
						After the check reset it to 0 for the next round.
						*/
						globalMinValue = nodeData[tempCounter1][2];
						globalMinNode = nodeData[tempCounter1][3];
						globalMinNodeFather = nodeData[tempCounter1][4];
						
						nodeData[tempCounter1][2] = 0;
					}
				}
				/*
				Determine the number of nodes in the spanning tree.
				Also find the linkage with the least weight.
				*/
			}
			if(globalMinValue < maxWeight+1)
			{
				/*
				Add the node with the best linkage to the spanning tree.
				*/
				nodeData[globalMinNode][1] = 1;
				tempCounter2++;
				/*
				Increase the number of nodes in the tree.
				*/
				globalWeight += globalMinValue;
				
				
				graphTree[globalMinNode][globalMinNodeFather]=1;
				graphTree[globalMinNodeFather][globalMinNode]=1;
				/*
				 Update the adjacency matrix
				 */
			}
			
			if(tempCounter2 == nodeNumber)
			{
				finishFlag=1;
			}
			/*
			All the nodes exist in the tree.
			The calculations are complete.
			*/
		}
	pthread_barrier_wait(&barrier);
	
	}
	/*
	The calculation is complete.
	The results can now be extracted.
	*/
	if(number == numberThreads-1)
	{	
		printf("GlobalWeight: %d\n", globalWeight);
	}
	
	

}
