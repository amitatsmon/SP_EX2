#include "main_aux.h"
#include "SPBPriorityQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int printIndexesAndClearQueue(SPBPQueue* queue)
{
	int tempSize, i;
	BPQueueElement* out_of_queue = NULL;

	out_of_queue = (BPQueueElement*)malloc(sizeof(BPQueueElement));
	
	//Checking that malloc worked
	if (NULL == out_of_queue)
	{
		printf("Error allocating memory: %s\n", strerror(errno));
		return -1;
	}

	tempSize = spBPQueueSize(queue); //Need to save the size of the queue to know how much time the loop should run
	for (i = 0; i < tempSize-1; ++i)
	{
		spBPQueuePeek(queue, out_of_queue);
		spBPQueueDequeue(queue);
		printf("%d, ", out_of_queue->index);
	}

	spBPQueuePeek(queue, out_of_queue);
	spBPQueueDequeue(queue);
	printf("%d\n", out_of_queue->index);

	free(out_of_queue);
	return 0;
}

void get_point_input(double* in_data, int dim)
{
	for (int i = 0; i < dim; ++i)
	{
		scanf("%lf", in_data+i);
	}
}