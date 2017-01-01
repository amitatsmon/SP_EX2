#ifndef MAIN_AUX_H
#define MAIN_AUX_H
#include "SPBPriorityQueue.h"

/**
 * The function prints all indexes in the queue and clears the queue
 *
 * @param queue - The queue to be printed and cleared
 * 
 * @return
 * return -1 on error and 0 if everything was printed and the queue was cleared
 */
int printIndexesAndClearQueue(SPBPQueue* queue);

/**
 * The function reads doubles from the user and stores them in a given array
 *
 * @param in_data - A pointer to where to put the input array
 * @param dim - The number of doubles to read into in_data
 * 
 */
void get_point_input(double* in_data, int dim);

#endif	
