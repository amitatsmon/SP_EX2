#include "../SPPoint.h"
#include "unit_test_util.h"
#include <stdbool.h>
#include <stdlib.h>

//Checks if copy Works
bool pointBasicCopyTest() {
	int i;
	double data[2] = { 1.0, 1.0 };
	int dim = 2;
	int index = 1;
	SPPoint p = spPointCreate(data, dim, index);
	SPPoint q = spPointCopy(p);
	ASSERT_TRUE(spPointGetIndex(p) == spPointGetIndex(q));
	ASSERT_TRUE(spPointGetDimension(p) == spPointGetDimension(q));
	for (i = 0; i < spPointGetDimension(p); i++) {
		ASSERT_TRUE(spPointGetAxisCoor(p, i) == spPointGetAxisCoor(q, i));
	}
	spPointDestroy(p);
	spPointDestroy(q);
	return true;
}
bool pointBasicL2Distance() {
	double data1[2] = { 1.0, 1.0 };
	double data2[2] = { 1.0, 0.0 };
	int dim1 = 2;
	int dim2 = 2;
	int index1 = 1;
	int index2 = 1;
	SPPoint p = spPointCreate((double *)data1, dim1, index1);
	SPPoint q = spPointCreate((double *)data2, dim2, index2);
	ASSERT_TRUE(spPointL2SquaredDistance(p,p) == 0.0);
	ASSERT_TRUE(spPointL2SquaredDistance(q,q) == 0.0);
	ASSERT_FALSE(spPointL2SquaredDistance(p,q) == 0.0);
	spPointDestroy(p);
	spPointDestroy(q);
	return true;
}

/**
 * creates a random point and copies it, checking all
 * values were copied correctly, then destroys both copies.
 * repeats 10 times.
 */
bool pointCreateAndCopyTest() {
	int i;
	int j;
	int dim;
	int index;
	double* data;
	SPPoint p, q;
	for (i = 0; i < 10; i++) {
		// randomize values
		dim = rand() % 1000;
		dim = (dim == 0 ? 1 : dim); // make sure dim > 0
		index = rand();
		data = (double*) malloc(dim * sizeof(double));
		if (data == NULL) {
			return false;
		}
		for (j = 0; j < dim; j++) {
			data[j] = ((double) rand() / (double) RAND_MAX);
		}
		p = spPointCreate(data, dim, index); // create first point
		if (p == NULL) {
			return false;
		}
		q = spPointCopy(p); // copy point
		if (q == NULL) {
			return false;
		}
		// assert indentical values
		ASSERT_TRUE(spPointGetIndex(p) == spPointGetIndex(q));
		ASSERT_TRUE(spPointGetDimension(p) == spPointGetDimension(q));
		for (j = 0; j < spPointGetDimension(p); j++) {
			ASSERT_TRUE(spPointGetAxisCoor(p, j) == spPointGetAxisCoor(q, j));
		}
		// destroy
		spPointDestroy(p);
		spPointDestroy(q);
		free(data);
		// on to the next one
	}
	return true; // all done
}

/**
 * creates a random point, checking all values were
 * initialized correctly, then destroys it.
 * repeats 10 times.
 */
bool pointGetterTest() {
	int i;
	int j;
	int dim;
	int index;
	double* data;
	SPPoint p;
	for (i = 0; i < 10; i++) {
		// randomize values
		dim = rand() % 1000;
		dim = (dim == 0 ? 1 : dim); // make sure dim > 0
		index = rand();
		data = (double*) malloc(dim * sizeof(double));
		if (data == NULL) {
			return false;
		}
		for (j = 0; j < dim; j++) {
			data[j] = ((double) rand() / (double) RAND_MAX);
		}
		p = spPointCreate(data, dim, index); // create point
		if (p == NULL) {
			return false;
		}
		// assert correct values
		ASSERT_TRUE(spPointGetIndex(p) == index);
		ASSERT_TRUE(spPointGetDimension(p) == dim);
		for (j = 0; j < spPointGetDimension(p); j++) {
			ASSERT_TRUE(spPointGetAxisCoor(p, j) == data[j]);
		}
		// destroy
		spPointDestroy(p);
		free(data);
		// on to the next one
	}
	return true; // all done
}
/**
 * creates three certain points and makes sure
 * all distances between them are as they should be
 */
bool pointDistanceTest() {
	// set values
	double data1[4] = {4.0, 3.0, 2.0, 5.0};
	double data2[4] = {5.0, 7.0, 1.0, 2.0};
	double data3[4] = {3.0, 5.0, 4.0, 3.0};
	int dim = 4;
	int index = 2;
	// create point
	SPPoint p1 = spPointCreate((double*)data1, dim, index);
	SPPoint p2 = spPointCreate((double*)data2, dim, index);
	SPPoint p3 = spPointCreate((double*)data3, dim, index);
	// assert values
	ASSERT_TRUE(spPointL2SquaredDistance(p1, p2) == 27.0);
	ASSERT_TRUE(spPointL2SquaredDistance(p3, p2) == 18.0);
	ASSERT_TRUE(spPointL2SquaredDistance(p1, p3) == 13.0);
	//all done
	spPointDestroy(p1);
	spPointDestroy(p2);
	spPointDestroy(p3);
	return true;
}
int main() {
	RUN_TEST(pointBasicCopyTest);
	RUN_TEST(pointBasicL2Distance);
	RUN_TEST(pointCreateAndCopyTest);
	RUN_TEST(pointGetterTest);
	RUN_TEST(pointDistanceTest);
	return 0;
}
