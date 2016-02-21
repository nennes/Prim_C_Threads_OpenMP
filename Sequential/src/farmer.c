void farmer() 
{
	
	int tempCounter1, tempCounter2, tempCounter3;
	int minValue, minNode, minNodeFather;
	int globalMinValue, globalMinNode, globalMinNodeFather;
	int nodesPerThread, extraNodesPerThread;
	int globalWeight = 0;
	int randomNode;

/*
	The first thread will determine the node 
	that will be the root of the tree.
	The initialization of the workload follows.
	*/
	
	srand ( time(NULL) );
	/* 
	The random numbers will be based on the current time.
	*/
	
	randomNode = rand() % nodeNumber;
	/* 
	Generate number between 0 and nodeNumber-1.
	*/

	nodeData[randomNode][1]=1;

	finishFlag=0;
	
	
	while(!finishFlag)
	{
		
		/*
		All threads will wait for the results of the scheduler.
		*/
		for( tempCounter1=0; tempCounter1<nodeNumber; tempCounter1++ )
		{
			
			/*
			This node will be processed by this thread.
			*/
				
			minValue=maxWeight+1;
			for( tempCounter2=0; tempCounter2<nodeNumber; tempCounter2++ )
			{
				/*
				Scan the current node in the graph Table for the minimum 
				linkage value. The linkages that will be scanned will not
				already belong to the tree.
				*/
				
				
				if( (graphTable[tempCounter1][tempCounter2] > 0) && (graphTable[tempCounter1][tempCounter2] < minValue) && (nodeData[tempCounter2][1]==0))
				{
					minValue = graphTable[tempCounter1][tempCounter2];
					minNode = tempCounter2;
					minNodeFather = tempCounter1;
				}
			}
				/*
				At this point there can be only two outcomes:
				- A new linkage has been discovered
				- This node has no children (leaf)
				*/
				
			if ( minValue < (maxWeight+1) )
			{
				/*
				A new minimum linkage has been discovered for this node.
				Write it to the nodeData table to be compared with the rest.
				*/
				nodeData[tempCounter1][2] = minValue;
				nodeData[tempCounter1][3] = minNode;
				nodeData[tempCounter1][4] = minNodeFather;
			}			
	
		}
		
		
		
			
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
					/*
					Determine the number of nodes in the spanning tree.
					*/
					
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
	/*
	The calculation is complete.
	The results can now be extracted.
	*/
	
	printf("GlobalWeight: %d\n", globalWeight);

	

}
