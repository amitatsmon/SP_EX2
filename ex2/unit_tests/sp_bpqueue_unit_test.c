#include "../SPBPriorityQueue.h"
#include "unit_test_util.h"
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

// Help function
SPBPQueue* randomQueue()
{
	int i;
	int maxSize;
	int index;
	double value;
	double value2;
	SPBPQueue*  q;

	while (!(maxSize = rand() % 1000)) ; //Makes sure maxSize != 0
	q = spBPQueueCreate(maxSize);
	for (i = 0; i < maxSize + 2; ++i)
	{
		value = (double)rand();
		while (!(value2 = rand()));//Makes sure we don't devide by zero
		value = value / value2;
		while (!(index = rand()));//Makes sure index != 0
		spBPQueueEnqueue(q, index, value);
	}
	return q;
}

//Checks if copy Works
bool BPQueueCopyTest()
{
	SPBPQueue*  q = spBPQueueCreate(5);
	spBPQueueEnqueue(q, 6, 3);
	spBPQueueEnqueue(q, 2, -1);
	spBPQueueEnqueue(q, 1, 2);
	SPBPQueue* copy_q = spBPQueueCopy(q);
	ASSERT_TRUE(spBPQueueSize(q) == spBPQueueSize(copy_q));
	ASSERT_TRUE(spBPQueueGetMaxSize(q) == spBPQueueGetMaxSize(copy_q));

	spBPQueueDestroy(q);
	spBPQueueDestroy(copy_q);
	return true;
}

//Checks if enqueue Works
bool BPQueueEnqueueTest()
{
	int i;
	SPBPQueue*  q = spBPQueueCreate(100);
	ASSERT_TRUE(0 == spBPQueueSize(q));
	for (i = 0; i < 50; i++)
	{
		spBPQueueEnqueue(q, 6, 6);
	}
	ASSERT_TRUE(50 == spBPQueueSize(q));
	for (i = 0; i < 50; i++)
	{
		spBPQueueEnqueue(q, 6, 6);
	}
	ASSERT_TRUE(100 == spBPQueueSize(q));
	for (i = 0; i < 50; i++)
	{
		spBPQueueEnqueue(q, 6, 6);
	}
	ASSERT_TRUE(100 == spBPQueueSize(q));
	spBPQueueDestroy(q);
	return true;
}

//Checks if clear Works
bool spBPQueueClearTest()
{
	SPBPQueue*  q = randomQueue();
	SPBPQueue* p = spBPQueueCreate(5);
	spBPQueueClear(q);
	ASSERT_TRUE(spBPQueueSize(q) == 0);
	spBPQueueDestroy(q);
	spBPQueueClear(p);
	ASSERT_TRUE(spBPQueueSize(p) == 0);
	spBPQueueDestroy(p);
	return true;
}

//Checks if empty Works
bool spBPQueueEmptyTest()
{
	int maxSize;
	SPBPQueue*  q;
	SPBPQueue*  p = randomQueue();
	while (!(maxSize = rand() % 1000)) ; //Makes sure maxSize != 0
	q = spBPQueueCreate(maxSize);
	ASSERT_TRUE(spBPQueueIsEmpty(q));
	spBPQueueDestroy(q);
	spBPQueueClear(p);
	ASSERT_TRUE(spBPQueueIsEmpty(p));
	spBPQueueDestroy(p);
	return true;
}

//Checks if full Works
bool spBPQueueFullTest()
{
	int maxSize;
	SPBPQueue*  q;
	SPBPQueue*  p = randomQueue();
	while (!(maxSize = rand() % 1000)) ; //Makes sure maxSize != 0
	q = spBPQueueCreate(maxSize);
	ASSERT_TRUE(!(spBPQueueIsFull(q)));
	ASSERT_TRUE(spBPQueueIsFull(p));
	spBPQueueDequeue(p);
	ASSERT_TRUE(!(spBPQueueIsFull(p)));
	spBPQueueClear(p);
	ASSERT_TRUE(!(spBPQueueIsFull(p)));
	spBPQueueDestroy(p);
	spBPQueueDestroy(q);
	return true;
}

//Checks if min value Works
bool spBPQueueMinValueTest()
{
	int i;
	double minimum;
	int maxSize;
	int index;
	double value;
	double value2;
	SPBPQueue*  q;

	while (!(maxSize = rand() % 1000)) ; //Makes sure maxSize != 0
	q = spBPQueueCreate(maxSize);
	for (i = 0; i < maxSize; ++i)
	{
		value = (double)rand();
		while (!(value2 = rand()));//Makes sure we don't devide by zero
		value = value / value2;
		while (!(index = rand()));//Makes sure index != 0
		spBPQueueEnqueue(q, index, value);
		if (i == 0)
		{
			minimum = value;
		}
		else if ( value < minimum)
		{
			minimum = value;
		}
	}
	ASSERT_TRUE(spBPQueueMinValue(q) == minimum);
	spBPQueueDestroy(q);
	return true;
}

//Checks if max value Works
bool spBPQueueMaxValueTest()
{
	int i;
	double maximum;
	int maxSize;
	int index;
	double value;
	double value2;
	SPBPQueue*  q;

	while (!(maxSize = rand() % 1000)) ; //Makes sure maxSize != 0
	q = spBPQueueCreate(maxSize);
	for (i = 0; i < maxSize; ++i)
	{
		value = (double)rand();
		while (!(value2 = rand())); //Makes sure we don't devide by zero
		value = value / value2;
		while (!(index = rand())); //Makes sure index != 0
		spBPQueueEnqueue(q, index, value);
		if (i == 0)
		{
			maximum = value;
		}
		else if ( value > maximum)
		{
			maximum = value;
		}
	}
	ASSERT_TRUE(spBPQueueMaxValue(q) == maximum);
	spBPQueueDestroy(q);
	return true;
}

//Checks if dequeue works
bool spBPQueueDequeueTest()
{
	int j;
	SPBPQueue*  q = randomQueue();
	SPBPQueue*  p = randomQueue();
	int maxSize = spBPQueueGetMaxSize(q);

	for (j = 0; j < maxSize; j++)
	{
		spBPQueueDequeue(q);
		ASSERT_TRUE(spBPQueueSize(q) == maxSize - j - 1);
	}
	
	spBPQueueDequeue(p);
	spBPQueueDestroy(p);
	spBPQueueDestroy(q);
	return true;
}

//Checks if peek works
bool spBPQueuePeekTest()
{
	int j;
	SPBPQueue*  q = randomQueue();
	int maxSize = spBPQueueGetMaxSize(q);
	BPQueueElement*  min = malloc(sizeof(int) + sizeof(double));
	BPQueueElement*  min2 = malloc(sizeof(int) + sizeof(double));
	spBPQueuePeek(q, min);
	for (j = 0; j < maxSize; j++)
	{
		spBPQueuePeek(q, min2);
		spBPQueueDequeue(q);
		ASSERT_TRUE(min->value <= min2->value);
		*min = *min2;
	}
	spBPQueuePeek(q, min2);
	free (min);
	free (min2);
	spBPQueueDestroy(q);
	return true;
}

//Checks if peek last Works
bool spBPQueuePeekLastTest()
{
	int i;
	double maximum;
	int maxSize;
	int index;
	double value;
	double value2;
	SPBPQueue*  q;
	BPQueueElement*  max = malloc(sizeof(int) + sizeof(double));

	while (!(maxSize = rand() % 1000)) ; //Makes sure maxSize != 0
	q = spBPQueueCreate(maxSize);
	for (i = 0; i < maxSize; ++i)
	{
		value = (double)rand();
		while (!(value2 = rand())); //Makes sure we don't devide by zero
		value = value / value2;
		while (!(index = rand())); //Makes sure index != 0
		spBPQueueEnqueue(q, index, value);
		if (i == 0)
		{
			maximum = value;
		}
		else if ( value > maximum)
		{
			maximum = value;
		}
	}
	spBPQueuePeekLast(q, max);
	ASSERT_TRUE(max->value == maximum);
	spBPQueueDestroy(q);
	free(max);
	return true;
}

int main()
{
	srand(time(NULL));
	RUN_TEST(BPQueueCopyTest);
	RUN_TEST(BPQueueEnqueueTest);
	RUN_TEST(spBPQueueClearTest);
	RUN_TEST(spBPQueueEmptyTest);
	RUN_TEST(spBPQueueFullTest);
	RUN_TEST(spBPQueueMinValueTest);
	RUN_TEST(spBPQueueMaxValueTest);
	RUN_TEST(spBPQueueDequeueTest);
	RUN_TEST(spBPQueuePeekTest);
	RUN_TEST(spBPQueuePeekLastTest);
	return 0;
}