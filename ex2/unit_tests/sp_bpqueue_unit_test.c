#include "../SPBPriorityQueue.h"
#include "unit_test_util.h"
#include <stdbool.h>

#include <stdio.h>

bool blabla()
{
	int i;
	SPBPQueue*  q = spBPQueueCreate(3);
	spBPQueueEnqueue(q,1,3);
	spBPQueueEnqueue(q,1,2);
	spBPQueueEnqueue(q,1,-2);
	spBPQueueEnqueue(q,1,-1);
	spBPQueueEnqueue(q,1,0);
	for (i = 0; i < 3; ++i)
	{
		printf("%d, index: %d, value: %f\n",i, q->data[i].index, q->data[i].value);
	}

	printf("size: %d\n",  spBPQueueSize(q));
	printf("is full: %d\n", spBPQueueIsFull(q));
	return 0;
}

int main() 
{
	blabla();
	return 0;
}
