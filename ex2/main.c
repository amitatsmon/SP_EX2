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
	int i, in_total_num_of_points, in_dim, in_num_of_points_to_print;
	double* current_input_data;
	double cur_dist;
	SPPoint** in_points_array;
	SPPoint* in_point_q;
	SPBPQueue* square_distense_bqueue;

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

	//Creates the queue and insert all distances from the point q
	square_distense_bqueue = spBPQueueCreate(in_num_of_points_to_print);

	for (i = 0; i < in_total_num_of_points; ++i)
	{
		cur_dist = spPointL2SquaredDistance(in_point_q, in_points_array[i]);
		spBPQueueEnqueue(square_distense_bqueue, i + 1, cur_dist); 
	}

	//Print output and clear the queue
	if (-1 == printIndexesAndClearQueue(square_distense_bqueue))
	{
		return -1;
	}

	//free all memory
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