#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#define SIZE_ARR 100
#define DEBUG 0

unsigned int lfsr = 0xECAACE1u;
unsigned bit;
int array[SIZE_ARR][SIZE_ARR];


float Fnrand(int n, int seed)
{
	lfsr = seed;

	for(int i = 0; i < n; i++)
	{
		bit  = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5) ) & 1;
		lfsr =  (lfsr >> 1) | (bit << 15);
	}
	return (float)lfsr;//100000;
}

int intRand(int max)
{
	float rn = 0;
	//srand(time(NULL));

	rn = (float)rand()/(float)RAND_MAX;
	rn *= (float)max;
	return (int)rn;
}

int main(void)
{
	int x = 0;
	int y = 0;
	int nbShoot = 500000;
	int nbCircle = 0;
	int nbCircleInt = 0;
	int area = 0;
	float approx = 0;

	srand(time(NULL));

	//for(int nbShoot = 2;nbShoot<1000;nbShoot++) {
	for(int i=0; i <= SIZE_ARR; i++)
	{
		for(int k=0; k <= SIZE_ARR; k++)
		{
			array[i][k] = 0;
		}
	}
	
	for(int i=0; i < nbShoot; i++)
	{
		x = intRand(SIZE_ARR);
		y = intRand(SIZE_ARR);

		//printf("x: %d, y:%d \r\n", x, y);

		array[x][y] = 1;
	}

	for(int i=0; i < SIZE_ARR; i++)
	{
		for(int k=0; k < SIZE_ARR; k++)
		{
			if(sqrtf((float)(i*i) + (float)(k*k)) < (float)SIZE_ARR)
			{
				if(array[i][k] == 1)
				{
					array[i][k] = 2;
					nbCircle++;
					if(i == 0 || k == 0)
					{
						array[i][k] = 3;
						nbCircleInt++;
					}
				}
			}
			if(sqrtf((float)(i*i) + (float)(k*k)) == (float)SIZE_ARR)
			{
				//printf("x:%d - y:%d \r\n", i, k);
				if(array[i][k] == 1)
				{
					array[i][k] = 2;
					nbCircle++;
				}
			}
		}
	}

	area = 4*(nbCircle - nbCircleInt) + 2 * nbCircleInt + 3;

	approx = (float)(area) / (float)(SIZE_ARR * SIZE_ARR);

	//printf("area= %d \r\n", area);
	//printf("nbCircle= %d \r\n", nbCircle);
	printf("approx = %f \r\n", approx);

	if(DEBUG)
	{
		for(int i=0; i < SIZE_ARR; i++)
		{
			for(int k=0; k < SIZE_ARR; k++)
			{
				printf(" %c", array[i][k] >= 1 ? array[i][k] >= 2 ? array[i][k] == 2 ? '*':'o':'.':' ');
			}
			printf(" \r\n");
		}
	}
	//}
	
	return 0;
}
