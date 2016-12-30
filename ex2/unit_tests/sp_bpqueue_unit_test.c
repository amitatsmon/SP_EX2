#include "../SPBPriorityQueue.h"
#include "unit_test_util.h"
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

#include <stdio.h>

bool BasicTest()
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

bool BPQueueCopyTest()
{
	SPBPQueue*  q = spBPQueueCreate(5);
	spBPQueueEnqueue(q,6,3);
	spBPQueueEnqueue(q,2,-1);
	spBPQueueEnqueue(q,1,2);
	SPBPQueue* copy_q = spBPQueueCopy(q);
	ASSERT_TRUE(spBPQueueSize(q)==spBPQueueSize(copy_q));
	ASSERT_TRUE(spBPQueueGetMaxSize(q)==spBPQueueGetMaxSize(copy_q));

	spBPQueueDestroy(q);
	spBPQueueDestroy(copy_q);
	return true;
}

int main() 
{
	RUN_TEST(BPQueueCopyTest);
	return 0;
}
