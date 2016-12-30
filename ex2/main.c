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
	BPQueueElement* out_of_queue = NULL;

	scanf("%d %d %d", &in_total_num_of_points, &in_dim, &in_num_of_points_to_print); //We assume that the input is valid

	in_points_array = (SPPoint**)malloc(sizeof(SPPoint*)*in_total_num_of_points);

	//check that malloc worked
	if(NULL == in_points_array)
	{
		printf("Error allocating memory: %s\n", strerror(errno));
		return -1;
	}

	//Reading the first n points;
	current_input_data = (double*)malloc(sizeof(double)*in_dim);
	for (i=0; i<in_total_num_of_points; ++i)
	{
		get_point_input(current_input_data, in_dim);
		in_points_array[i] = spPointCreate(current_input_data, in_dim, i);
	}
	//Reading point q
	get_point_input(current_input_data, in_dim);
	in_point_q = spPointCreate(current_input_data, in_dim, -1);


	square_distense_bqueue = spBPQueueCreate(in_num_of_points_to_print);

	for (int i = 0; i < in_total_num_of_points; ++i)
	{
		cur_dist = spPointL2SquaredDistance(in_point_q, in_points_array[i]);
		//printf("%lf\n", cur_dist);
		spBPQueueEnqueue(square_distense_bqueue, i+1, cur_dist); //Check return value??
	}

	for (int i = 0; i < square_distense_bqueue->size; ++i)
	{
		printf("%4x\n", (int)&(square_distense_bqueue->data[i]));
		printf("%d, %lf\n",square_distense_bqueue->data[i].index, square_distense_bqueue->data[i].value);
	}

	for (int i = 0; i < spBPQueueSize(square_distense_bqueue)-1; ++i)
	{
		printf("1\n");
		printf("%4x\n", (int)square_distense_bqueue);
		spBPQueuePeek(square_distense_bqueue, out_of_queue);
		printf("2\n");
		spBPQueueDequeue(square_distense_bqueue); //Check return value??
		printf("3\n");
		printf("%d ", out_of_queue->index);
		printf("4\n");
	}
	
	spBPQueuePeek(square_distense_bqueue, out_of_queue);
	spBPQueueDequeue(square_distense_bqueue); //Check return value??
	printf("%d\n", out_of_queue->index);
	
	//free all memory
	spBPQueueDestroy(square_distense_bqueue);
	spPointDestroy(in_point_q);
	for (i=0; i<in_total_num_of_points; ++i)
	{
		spPointDestroy(in_points_array[i]);
	}
	free(in_points_array);
	free(current_input_data);

	//Exit
	return 0;
}