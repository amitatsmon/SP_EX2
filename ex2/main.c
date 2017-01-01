#include "main_aux.h"
#include "SPBPriorityQueue.h"
#include "SPPoint.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

int main()
{
	int i, in_total_num_of_points, in_dim, in_num_of_points_to_print, tempSize;
	double* current_input_data;
	double cur_dist;
	SPPoint** in_points_array;
	SPPoint* in_point_q;
	SPBPQueue* square_distense_bqueue;
	BPQueueElement* out_of_queue = NULL;

	scanf("%d %d %d", &in_total_num_of_points, &in_dim, &in_num_of_points_to_print); //We assume that the input is valid

	in_points_array = (SPPoint**)malloc(sizeof(SPPoint*)*in_total_num_of_points);

	//Checking that malloc worked
	if (NULL == in_points_array)
	{
		printf("Error allocating memory: %s\n", strerror(errno));
		return -1;
	}

	//Reading the first n points;
	current_input_data = (double*)malloc(sizeof(double) * in_dim);
	for (i = 0; i < in_total_num_of_points; ++i)
	{
		get_point_input(current_input_data, in_dim);
		in_points_array[i] = spPointCreate(current_input_data, in_dim, i);
	}
	//Reading point q
	get_point_input(current_input_data, in_dim);
	in_point_q = spPointCreate(current_input_data, in_dim, -1);


	square_distense_bqueue = spBPQueueCreate(in_num_of_points_to_print);

	for (i = 0; i < in_total_num_of_points; ++i)
	{
		cur_dist = spPointL2SquaredDistance(in_point_q, in_points_array[i]);
		spBPQueueEnqueue(square_distense_bqueue, i + 1, cur_dist); //Check return value??
	}

	out_of_queue = (BPQueueElement*)malloc(sizeof(BPQueueElement));
	//Checking that malloc worked
	if (NULL == out_of_queue)
	{
		printf("Error allocating memory: %s\n", strerror(errno));
		return -1;
	}

	tempSize = spBPQueueSize(square_distense_bqueue); //Need to save the size of the queue to know how much time the loop should run
	for (i = 0; i < tempSize-1; ++i)
	{
		spBPQueuePeek(square_distense_bqueue, out_of_queue);
		spBPQueueDequeue(square_distense_bqueue); //Check return value??
		printf("%d, ", out_of_queue->index);
	}

	spBPQueuePeek(square_distense_bqueue, out_of_queue);
	spBPQueueDequeue(square_distense_bqueue); //Check return value??
	printf("%d\n", out_of_queue->index);

	//free all memory
	free(out_of_queue);
	spBPQueueDestroy(square_distense_bqueue);
	spPointDestroy(in_point_q);
	for (i = 0; i < in_total_num_of_points; ++i)
	{
		spPointDestroy(in_points_array[i]);
	}
	free(in_points_array);
	free(current_input_data);

	//Exit
	return 0;
}