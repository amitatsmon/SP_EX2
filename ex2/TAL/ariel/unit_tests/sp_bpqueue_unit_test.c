#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "unit_test_util.h" //SUPPORTING MACROS ASSERT_TRUE/ASSERT_FALSE etc..
#include "../SPBPriorityQueue.h"

bool BPQueueStructureTest() {
	// Initialize values
	int maxSize = 10, index = 17;
	double value = 8.5;
	SPBPQueue q = spBPQueueCreate(maxSize), p;
	SPListElement data = spListElementCreate(index, value);

	// Check normal behaviour
	ASSERT_TRUE(q != NULL);
	spBPQueueClear(q);

	// Check more normal behaviour
	p = spBPQueueCopy(q);
	ASSERT_TRUE(spBPQueueSize(p) == 0);
	spBPQueueDestroy(p);
	p = NULL;

	// Insert
	ASSERT_TRUE(spBPQueueEnqueue(q, data) == SP_BPQUEUE_SUCCESS);
	p = spBPQueueCopy(q);
	spBPQueueClear(q); // More normal behaviour
	ASSERT_TRUE(spBPQueueSize(q) == 0);
	ASSERT_TRUE(spBPQueueSize(p) == 1);

	// All done, destroy everything
	spBPQueueDestroy(p);
	spBPQueueDestroy(q);
	spListElementDestroy(data);

	return true;
}

bool BPQueueInvalidTest() {
	// Initialize values
	int maxSize = 10, index = 17;
	double value = 8.5;
	SPBPQueue q = spBPQueueCreate(maxSize);
	SPListElement data = spListElementCreate(index, value);

	// Give everything all of its edge cases
	ASSERT_TRUE(spBPQueueCreate(0) == NULL);
	ASSERT_TRUE(spBPQueueCreate(-1) == NULL);
	ASSERT_TRUE(spBPQueueCreate(-1000) == NULL);

	ASSERT_TRUE(spBPQueueCopy(NULL) == NULL);
	spBPQueueDestroy(NULL);
	spBPQueueClear(NULL);

	ASSERT_TRUE(spBPQueueSize(NULL) == -1);
	ASSERT_TRUE(spBPQueueGetMaxSize(NULL) == -1);

	ASSERT_TRUE(spBPQueueEnqueue(NULL, data) == SP_BPQUEUE_INVALID_ARGUMENT);
	ASSERT_TRUE(spBPQueueEnqueue(q, NULL) == SP_BPQUEUE_INVALID_ARGUMENT);
	ASSERT_TRUE(spBPQueueDequeue(NULL) == SP_BPQUEUE_INVALID_ARGUMENT);

	ASSERT_TRUE(spBPQueuePeek(NULL) == NULL);
	ASSERT_TRUE(spBPQueuePeekLast(NULL) == NULL);

	ASSERT_TRUE(spBPQueueMinValue(NULL) == -1.0);
	ASSERT_TRUE(spBPQueueMaxValue(NULL) == -1.0);
	ASSERT_TRUE(spBPQueueMinValue(q) == -1.0);
	ASSERT_TRUE(spBPQueueMaxValue(q) == -1.0);

	// We're done tormenting the functions, destroy it all
	spBPQueueDestroy(q);
	spListElementDestroy(data);

	return true;
}

bool BPQueueEnqueueDequeueTest() {
	// Initialize values
	int maxSize = 2;
	int index1 = 1, index2 = 2, index3 = 3, index4 = 4;
	double value1 = 5, value2 = 10, value3 = 15, value4 = 20;
	SPListElement data1 = spListElementCreate(index1, value1);
	SPListElement data2 = spListElementCreate(index2, value2);
	SPListElement data3 = spListElementCreate(index3, value3);
	SPListElement data4 = spListElementCreate(index4, value4);
	SPBPQueue q = spBPQueueCreate(maxSize);
	SPListElement peek, peekLast;

	ASSERT_TRUE(spBPQueueEnqueue(q, data2) == SP_BPQUEUE_SUCCESS); // 1 element
	ASSERT_TRUE(spBPQueueEnqueue(q, data3) == SP_BPQUEUE_SUCCESS); // 2 elements
	ASSERT_TRUE(spBPQueueEnqueue(q, data1) == SP_BPQUEUE_SUCCESS); // new element is smaller than maximum, queue full
	ASSERT_TRUE(spBPQueueEnqueue(q, data4) == SP_BPQUEUE_FULL); // new element is larger than maximum, queue full

	// Check insertions went right
	peek = spBPQueuePeek(q);
	peekLast = spBPQueuePeekLast(q);
	ASSERT_TRUE(peek != NULL);
	ASSERT_TRUE(peekLast != NULL);
	ASSERT_TRUE(spListElementCompare(peek, data1) == 0);
	ASSERT_TRUE(spListElementCompare(peekLast, data2) == 0);
	spListElementDestroy(peek);
	spListElementDestroy(peekLast);

	// Check that copies were inserted (and not actual pointers)
	spListElementSetIndex(data1, 0);
	spListElementSetValue(data1, 0.0);
	spListElementDestroy(data2);
	peek = spBPQueuePeek(q);
	peekLast = spBPQueuePeekLast(q);
	ASSERT_TRUE(peek != NULL);
	ASSERT_TRUE(peekLast != NULL);
	ASSERT_TRUE(spListElementGetIndex(peek) == index1);
	ASSERT_TRUE(spListElementGetValue(peek) == value1);
	ASSERT_TRUE(spListElementGetIndex(peekLast) == index2);
	ASSERT_TRUE(spListElementGetValue(peekLast) == value2);

	ASSERT_TRUE(spBPQueueDequeue(q) == SP_BPQUEUE_SUCCESS); // Delete first element
	ASSERT_TRUE(spBPQueueDequeue(q) == SP_BPQUEUE_SUCCESS); // Delete other element
	ASSERT_TRUE(spBPQueueDequeue(q) == SP_BPQUEUE_EMPTY); // Queue is empty

	// All done, usual destruction routine
	spBPQueueDestroy(q);
	spListElementDestroy(data1);
	spListElementDestroy(data3);
	spListElementDestroy(data4);
	spListElementDestroy(peek);
	spListElementDestroy(peekLast);

	return true;
}

bool BPQueuePeekTest() {
	// Initialize values
	int maxSize = 10, index1 = 17, index2 = 561;
	double maxValue = 8.5, minValue = 3.14159;
	SPListElement data1 = spListElementCreate(index1, maxValue);
	SPListElement data2 = spListElementCreate(index2, minValue);
	SPListElement peek = NULL, peekLast = NULL;
	SPBPQueue q = spBPQueueCreate(maxSize);

	 // insert elements
	ASSERT_TRUE(spBPQueueEnqueue(q, data1) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueEnqueue(q, data2) == SP_BPQUEUE_SUCCESS);

	// Check peek works correctly
	ASSERT_TRUE((peek = spBPQueuePeek(q)) != NULL);
	ASSERT_TRUE((peekLast = spBPQueuePeekLast(q)) != NULL);
	ASSERT_TRUE(spListElementCompare(peek, data2) == 0);
	ASSERT_TRUE(spListElementCompare(peekLast, data1) == 0);

	// Check copies were returned (and not acutal pointers)
	spListElementSetValue(peek, -2.872878);
	spListElementSetIndex(peek, 2);
	spListElementDestroy(peek);
	spListElementDestroy(peekLast);
	ASSERT_TRUE((peek = spBPQueuePeek(q)) != NULL);
	ASSERT_TRUE((peekLast = spBPQueuePeekLast(q)) != NULL);
	ASSERT_TRUE(spListElementCompare(peek, data2) == 0);
	ASSERT_TRUE(spListElementCompare(peekLast, data1) == 0);

	// All done, you know what happens next
	spBPQueueDestroy(q);
	spListElementDestroy(data1);
	spListElementDestroy(data2);
	spListElementDestroy(peek);
	spListElementDestroy(peekLast);

	return true;
}

bool BPQueuePropertyTest() {
	// Initialize values
	int maxSize = 2, index1 = 17, index2 = 561;
	double maxValue = 8.5, minValue = 3.1415926535897232;
	SPListElement data1 = spListElementCreate(index1, maxValue);
	SPListElement data2 = spListElementCreate(index2, minValue);
	SPBPQueue q = spBPQueueCreate(maxSize);

	// Check various properties of the queue (size, maxsize, min, max, empty, full)
	ASSERT_TRUE(spBPQueueSize(q) == 0);
	ASSERT_TRUE(spBPQueueIsEmpty(q));
	ASSERT_FALSE(spBPQueueIsFull(q));
	ASSERT_TRUE(spBPQueueMinValue(q) == -1.0);
	ASSERT_TRUE(spBPQueueMaxValue(q) == -1.0);

	ASSERT_TRUE(spBPQueueEnqueue(q, data1) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueSize(q) == 1);
	ASSERT_FALSE(spBPQueueIsEmpty(q));
	ASSERT_FALSE(spBPQueueIsFull(q));

	ASSERT_TRUE(spBPQueueEnqueue(q, data2) == SP_BPQUEUE_SUCCESS);
	ASSERT_TRUE(spBPQueueSize(q) == 2);
	ASSERT_FALSE(spBPQueueIsEmpty(q));
	ASSERT_TRUE(spBPQueueIsFull(q));
	ASSERT_TRUE(spBPQueueMinValue(q) == minValue);
	ASSERT_TRUE(spBPQueueMaxValue(q) == maxValue);

	// For the last time, kill it all
	spBPQueueDestroy(q);
	spListElementDestroy(data1);
	spListElementDestroy(data2);

	return true;
}

int main() {
	RUN_TEST(BPQueueStructureTest);
	RUN_TEST(BPQueueInvalidTest);
	RUN_TEST(BPQueueEnqueueDequeueTest);
	RUN_TEST(BPQueuePeekTest);
	RUN_TEST(BPQueuePropertyTest);
	return 0;
}
