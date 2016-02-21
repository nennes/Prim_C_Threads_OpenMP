#ifndef GLOBALVARS_H
#define GLOBALVARS_H


pthread_mutex_t mt;

pthread_barrier_t barrier;
/*
This barrier pauses the thread execution
until all threads have reached the barrier.
*/

struct timeval time1, time2;
/*
Variables used to measure the execution time of 
the program.
*/

int nodeNumber = 0;
/*
Number of nodes in the graph. Determined by the
size of the adjacency matrix stored in the file.
*/

int randomNode;
/*
Root node of the generated tree
*/

int **graphTable;
/*
Table that will store the data in the file.
Over time its contents will change, depending
on the calculation. The generated tree will be
stored in another table.
*/

int **graphTree;
/*
This table will hold the constructed tree.
It will not contain all the linkages found 
in the original graph, only the ones used
in the tree.
*/

int **nodeData;
/*
This table will hold data generated during the 
calculations. Each thread will write in a part
of this table.
*/

pthread_t *idThreads;
/*
 Table that stores the thread ids.
 */
 
int *nameThreads;
/*
 Table that stores the thread names.
 */

int maxWeight;
/*
This is the maximum linkage value (weight) found
in the original graph. Any value higher that that 
can be considered as "infinite".
*/

int globalWeight;
/*
The total sum of all the linkages
in the generated tree.
*/

int finishFlag;

int numberThreads;
/*
The number of threads to be created.
Given as argument to the program.
*/

#endif
