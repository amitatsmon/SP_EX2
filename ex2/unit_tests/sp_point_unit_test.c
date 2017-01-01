#include "../SPPoint.h"
#include "unit_test_util.h"
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

/**
 * Creates a random point, copies it and checks that the 2 points are the same.
 */
bool pointCopyTest() 
{
	int i, dim;
	int index = 1;
	double temp_double1, temp_double2;
	SPPoint *p, *q;

	while (!(dim = rand()%100001)) ; //Makes sure dim != 0

	double* data = (double*)malloc(sizeof(double)*dim);

	for (i = 0; i < dim; ++i)
	{
		temp_double1 = (double)rand();
		while (!(temp_double2 = rand())); //Makes sure we don't devide by zero
		data[i] = temp_double1/temp_double2;
	}

	p = spPointCreate(data, dim, index);
	q = spPointCopy(p);

	ASSERT_TRUE(spPointGetDimension(p) == spPointGetDimension(q));
	ASSERT_TRUE(spPointGetIndex(p) == spPointGetIndex(q));

	for (int i = 0; i < dim; ++i) 
	{
		ASSERT_TRUE(spPointGetAxisCoor(p, i) == spPointGetAxisCoor(q, i));
	}
	free(data);
	spPointDestroy(p);
	spPointDestroy(q);
	return true;
}

/**
 * Creates 2 random points with the same dimension, checks that their squared distance is correct.
 * Repeats 10 times.
 */
bool pointL2Distance() 
{
	int i, k, dim;
	int index = 1;
	double temp_double1, temp_double2, *data1, *data2, square_dist;
	SPPoint *p, *q;
	for (k = 0; k < 10; ++k)
	{
		while (!(dim = rand()%100001)); //Makes sure dim != 0

		//Create point p
		data1 = (double*)malloc(sizeof(double)*dim);
		data2 = (double*)malloc(sizeof(double)*dim);
		for (i = 0; i < dim; ++i)
		{
			temp_double1 = (double)rand();
			while (!(temp_double2 = rand())); //Makes sure we don't devide by zero
			data1[i] = temp_double1/temp_double2;
		}
		p = spPointCreate(data1, dim, index);

		//Create point q
		for (i = 0; i < dim; ++i)
		{
			temp_double1 = (double)rand();
			while (!(temp_double2 = rand()));
			data2[i] = temp_double1/temp_double2;
		}
		q = spPointCreate(data2, dim, index);

		square_dist = 0.0;
		for (int i = 0; i < dim; ++i)
		{
			square_dist += (data1[i]-data2[i])*(data1[i]-data2[i]);
		}

		ASSERT_TRUE(square_dist == spPointL2SquaredDistance(p,q));

		free(data1);
		free(data2);
		spPointDestroy(p);
		spPointDestroy(q);
	}
	return true;
}

/**
 * Creates a random point, checks that its dimension is correct.
 * Repeats 10 times.
 */
bool pointGetDimensionTest() 
{
	int i, k, dim;
	int index = 1;
	double temp_double1, temp_double2;
	SPPoint* p;

	for (k = 0; k < 10; ++k)
	{
		while (!(dim = rand()%100001)) ; //Makes sure dim != 0

		double* data = (double*)malloc(sizeof(double)*dim);
		for (i = 0; i < dim; ++i)
		{
			temp_double1 = (double)rand();
			while (!(temp_double2 = rand())); //Makes sure we don't devide by zero
			data[i] = temp_double1/temp_double2;
		}

		p = spPointCreate(data, dim, index);
		ASSERT_TRUE(spPointGetDimension(p)==dim);
		free(data);
		spPointDestroy(p);
	}

	return true;
}

/**
 * Creates 3 points, and checks their indexes.
 */
bool pointGetIndexTest() 
{
	double data1[2] = { 5.0, 6.0 };
	double data2[2] = { 1.0, 0.2 };
	double data3[2] = { -3.2, 7.0 };
	int dim1 = 2;
	int dim2 = 2;
	int dim3 = 2;
	int index1 = 1;
	int index2 = 1;
	int index3 = 2;
	SPPoint* p = spPointCreate(data1, dim1, index1);
	SPPoint* q = spPointCreate(data2, dim2, index2);
	SPPoint* r = spPointCreate(data3, dim3, index3);
	ASSERT_TRUE(spPointGetIndex(p)==spPointGetIndex(q));
	ASSERT_FALSE(spPointGetIndex(p)==spPointGetIndex(r));
	spPointDestroy(p);
	spPointDestroy(q);
	spPointDestroy(r);
	return true;
}

/**
 * Creates a random point, checks that its axis coordinations are correct.
 */
bool pointGetAxisCoorTest() 
{
	int i, dim;
	int index = 1;
	double temp_double1, temp_double2;

	while (!(dim = rand()%100001)) ; //Makes sure dim != 0

	double* data = (double*)malloc(sizeof(double)*dim);
	for (i = 0; i < dim; ++i)
	{
		temp_double1 = (double)rand();
		while (!(temp_double2 = rand())); //Makes sure we don't devide by zero
		data[i] = temp_double1/temp_double2;
	}

	SPPoint* p = spPointCreate(data, dim, index);

	for (i = 0; i < dim; ++i)
	{
		ASSERT_TRUE(data[i]==spPointGetAxisCoor(p,i));
	}
	free(data);
	spPointDestroy(p);
	return true;
}

int main() 
{
	srand(time(NULL));
	RUN_TEST(pointGetDimensionTest);
	RUN_TEST(pointGetIndexTest);
	RUN_TEST(pointGetAxisCoorTest);
	RUN_TEST(pointCopyTest);
	RUN_TEST(pointL2Distance);
	return 0;
}

