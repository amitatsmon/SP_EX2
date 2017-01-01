#include "../SPBPriorityQueue.h"
#include "unit_test_util.h"
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

/* Helper function
 * creates a queue with random maximal size and random elements
 */
SPBPQueue* randomQueue()
{
	int i;
	int maxSize;
	int index;
	double value;
	double value2;
	SPBPQueue*  random_queue;

	while (!(maxSize = rand() % 1000)) ; //Makes sure maxSize != 0
	random_queue = spBPQueueCreate(maxSize);
	for (i = 0; i < maxSize + 2; ++i)
	{
		value = (double)rand();
		while (!(value2 = rand()));//Makes sure we don't devide by zero
		value = value / value2;
		while (!(index = rand()));//Makes sure index != 0
		spBPQueueEnqueue(random_queue, index, value);
	}
	return random_queue;
}

/* Checks if copy Works
 * creates a queue, copies it and checks that the size
 * and the max size of the copy and the original are the same
 */
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

/* Checks if enqueue Works
 * creates a queue and checks its size,
 * enqueues 50 elements and checks the queue's size,
 * repeats 3 times
 */
bool BPQueueEnqueueTest()
{
	int i;
	SPBPQueue*  q = spBPQueueCreate(100);
	ASSERT_TRUE(0 == spBPQueueSize(q));
	ASSERT_TRUE(SP_BPQUEUE_INVALID_ARGUMENT == spBPQueueEnqueue(NULL, 1, 1.0));
	for (i = 0; i < 50; i++)
	{
		ASSERT_TRUE(SP_BPQUEUE_SUCCESS == spBPQueueEnqueue(q, 6, 6));
	}
	ASSERT_TRUE(50 == spBPQueueSize(q));
	for (i = 0; i < 50; i++)
	{
		spBPQueueEnqueue(q, 6, 6);
	}
	ASSERT_TRUE(100 == spBPQueueSize(q));
	for (i = 0; i < 50; i++)
	{
		ASSERT_TRUE(SP_BPQUEUE_FULL == spBPQueueEnqueue(q, 6, 6));
	}
	ASSERT_TRUE(100 == spBPQueueSize(q));
	spBPQueueDestroy(q);
	return true;
}

/* Checks if clear Works
 * creates a random queue, clears it and check its size
 * creates an empty queue, clears it and checks its size
 */
bool spBPQueueClearTest()
{
	SPBPQueue*  random_queue = randomQueue();
	SPBPQueue* empty_queue = spBPQueueCreate(5);
	spBPQueueClear(random_queue);
	ASSERT_TRUE(spBPQueueSize(random_queue) == 0);
	spBPQueueDestroy(random_queue);
	spBPQueueClear(empty_queue);
	ASSERT_TRUE(spBPQueueSize(empty_queue) == 0);
	spBPQueueDestroy(empty_queue);
	return true;
}

/* Checks if empty Works
 * creates an empty queue, checks if it is empty
 * creates a random queue, clears it and check if it is empty
 */
bool spBPQueueEmptyTest()
{
	int maxSize;
	SPBPQueue*  empty_queue;
	SPBPQueue*  random_queue = randomQueue();
	while (!(maxSize = rand() % 1000)) ; //Makes sure maxSize != 0
	empty_queue = spBPQueueCreate(maxSize);
	ASSERT_TRUE(spBPQueueIsEmpty(empty_queue));

	ASSERT_FALSE(spBPQueueIsEmpty(random_queue));
	spBPQueueClear(random_queue);
	ASSERT_TRUE(spBPQueueIsEmpty(random_queue));

	spBPQueueDestroy(empty_queue);
	spBPQueueDestroy(random_queue);
	return true;
}

/* Checks if full Works
 * creates an empty queue and checks that it is not full
 * creates a random queue and checks that it is full
 * dequeues from the random queue and checks that it is not full
 * clears the random queue and checks that it is not full
 */
bool spBPQueueFullTest()
{
	int maxSize;
	SPBPQueue*  empty_queue;
	SPBPQueue*  random_queue = randomQueue();
	while (!(maxSize = rand() % 1000)) ; //Makes sure maxSize != 0
	empty_queue = spBPQueueCreate(maxSize);
	ASSERT_FALSE(spBPQueueIsFull(empty_queue));
	ASSERT_TRUE(spBPQueueIsFull(random_queue));
	spBPQueueDequeue(random_queue);
	ASSERT_FALSE(spBPQueueIsFull(random_queue));
	spBPQueueClear(random_queue);
	ASSERT_FALSE(spBPQueueIsFull(random_queue));

	spBPQueueDestroy(random_queue);
	spBPQueueDestroy(empty_queue);
	return true;
}

/* Checks if min value Works
 * creates a random queue and saves its minimal value
 * checks that the value that returns from the function is the minimal value
 */
bool spBPQueueMinValueTest()
{
	int i;
	double minimum;
	int maxSize;
	int index;
	double value;
	double value2;
	SPBPQueue*  random_queue;

	while (!(maxSize = rand() % 1000)) ; //Makes sure maxSize != 0
	random_queue = spBPQueueCreate(maxSize);
	for (i = 0; i < maxSize; ++i)
	{
		value = (double)rand();
		while (!(value2 = rand()));//Makes sure we don't devide by zero
		value = value / value2;
		while (!(index = rand()));//Makes sure index != 0
		spBPQueueEnqueue(random_queue, index, value);
		if (i == 0)
		{
			minimum = value;
		}
		else if ( value < minimum)
		{
			minimum = value;
		}
	}
	ASSERT_TRUE(spBPQueueMinValue(random_queue) == minimum);
	spBPQueueDestroy(random_queue);
	return true;
}

/* Checks if max value Works
 * creates a random queue and saves its maximal value
 * checks that the value that returns from the function is the maximal value
 */
bool spBPQueueMaxValueTest()
{
	int i;
	double maximum;
	int maxSize;
	int index;
	double value;
	double value2;
	SPBPQueue*  random_queue;

	while (!(maxSize = rand() % 1000)) ; //Makes sure maxSize != 0
	random_queue = spBPQueueCreate(maxSize);
	for (i = 0; i < maxSize; ++i)
	{
		value = (double)rand();
		while (!(value2 = rand())); //Makes sure we don't devide by zero
		value = value / value2;
		while (!(index = rand())); //Makes sure index != 0
		spBPQueueEnqueue(random_queue, index, value);
		if (i == 0)
		{
			maximum = value;
		}
		else if ( value > maximum)
		{
			maximum = value;
		}
	}
	ASSERT_TRUE(spBPQueueMaxValue(random_queue) == maximum);
	spBPQueueDestroy(random_queue);
	return true;
}

/* Checks if dequeue works
 * creates a random queue dequeues the elements and check its size every time
 * creates an empty queue and tries do dequeues from it
 */
bool spBPQueueDequeueTest()
{
	int j;
	SPBPQueue*  random_queue = randomQueue();
	SPBPQueue*  empty_queue = spBPQueueCreate(7);
	ASSERT_TRUE(SP_BPQUEUE_INVALID_ARGUMENT == spBPQueueDequeue(NULL));
	int maxSize = spBPQueueGetMaxSize(random_queue);

	for (j = 0; j < maxSize; j++)
	{
		ASSERT_TRUE(SP_BPQUEUE_SUCCESS == spBPQueueDequeue(random_queue));
		ASSERT_TRUE(spBPQueueSize(random_queue) == maxSize - j - 1);
	}

	ASSERT_TRUE(SP_BPQUEUE_EMPTY == spBPQueueDequeue(empty_queue));
	spBPQueueDestroy(empty_queue);
	spBPQueueDestroy(random_queue);
	return true;
}

/* Checks if peek works
 * creates a random queue, uses peek to check what is the value of the next element one by one
 * checks that the value of the element is bigger than the value of the previous element
 */
bool spBPQueuePeekTest()
{
	int j;
	SPBPQueue*  random_queue = randomQueue();
	int maxSize = spBPQueueGetMaxSize(random_queue);

	ASSERT_TRUE(SP_BPQUEUE_INVALID_ARGUMENT == spBPQueuePeek(NULL, NULL));
	BPQueueElement*  min = malloc(sizeof(int) + sizeof(double));
	BPQueueElement*  min2 = malloc(sizeof(int) + sizeof(double));
	spBPQueuePeek(random_queue, min);
	for (j = 0; j < maxSize; j++)
	{
		ASSERT_TRUE(SP_BPQUEUE_SUCCESS == spBPQueuePeek(random_queue, min2));
		spBPQueueDequeue(random_queue);
		ASSERT_TRUE(min->value <= min2->value);
		*min = *min2;
	}
	ASSERT_TRUE(SP_BPQUEUE_EMPTY == spBPQueuePeek(random_queue, min2));
	free (min);
	free (min2);
	spBPQueueDestroy(random_queue);
	return true;
}

/* Checks if peek last works
 * creates an empty queue, checks that peek last works with an empty queue
 * creates a random queue, save its maximal value
 * peek last and checks if the element's value is equal to the maximal value
 */
bool spBPQueuePeekLastTest()
{
	int i;
	double maximum;
	int maxSize;
	int index;
	double value;
	double value2;
	SPBPQueue*  random_queue;
	SPBPQueue*  empty_queue = spBPQueueCreate(666);

	BPQueueElement*  max = malloc(sizeof(int) + sizeof(double));
	ASSERT_TRUE(SP_BPQUEUE_EMPTY == spBPQueuePeekLast(empty_queue, max));
	ASSERT_TRUE(SP_BPQUEUE_INVALID_ARGUMENT == spBPQueuePeek(NULL, NULL));

	while (!(maxSize = rand() % 1000)) ; //Makes sure maxSize != 0
	random_queue = spBPQueueCreate(maxSize);
	for (i = 0; i < maxSize; ++i)
	{
		value = (double)rand();
		while (!(value2 = rand())); //Makes sure we don't devide by zero
		value = value / value2;
		while (!(index = rand())); //Makes sure index != 0
		spBPQueueEnqueue(random_queue, index, value);
		if (i == 0)
		{
			maximum = value;
		}
		else if ( value > maximum)
		{
			maximum = value;
		}
	}

	ASSERT_TRUE(SP_BPQUEUE_SUCCESS == spBPQueuePeekLast(random_queue, max));
	ASSERT_TRUE(max->value == maximum);
	spBPQueueDestroy(random_queue);
	spBPQueueDestroy(empty_queue);
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