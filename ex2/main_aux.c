#include "main_aux.h"
#include <stdio.h>

void get_point_input(double* in_data, int dim)
{
	for (int i = 0; i < dim; ++i)
	{
		scanf("%lf", in_data+i);
	}
}