#include <stdio.h>
#include <stdlib.h>

#include "ratings.h"
#include "restaurant.h"
#include "utils.h"

void displayRatingAvg(int *numArr, int arrSize)	// num array, size of array
{
	float avg = 0.0f;		// average of numbers in array
	for (int i = 0; i < arrSize; i++)
	{
		avg = avg + numArr[i];
	}
	avg = avg / arrSize;
	
	printf("%.2f", avg);
}


void seeRatings()
{

}
