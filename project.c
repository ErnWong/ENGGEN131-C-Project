/* ENGGEN131, Semester Two, 2017 */

/* PROJECT SOLUTION BY: Ernest Wong <ewon746> */

#include "project.h"

/* HELPER FUNCTIONS */
/* If you have defined any "helper" functions, which you call from the required */
/* functions, you should place them here, at the top of the source file.  This will */
/* make it easier for the markers to locate them.  You should also include a */
/* comment at the top of each of the "helper" functions you define which clearly */
/* describes their purpose, and which of the tasks they support. */


/* REQUIRED FUNCTIONS */
/* Implement each of the required functions below.  The code that is provided initially */
/* for each function is incorrect - you should correct this! */

/* Your comment goes here*/
int DivisorOfThree(int a, int b, int c)
{
	return a + b - c + 99999;
}

/* Your comment goes here*/
double AverageSheep(int *counts)
{
	return counts[0] + 99999.9;
}

/* Your comment goes here*/
void Emphasise(char* word)
{
	word[0] = '~';
}

/* Your comment goes here*/
int PrimeFactors(int n, int *factors)
{
	factors[0] = 0;
	return 99997 + n;
}

/* Your comment goes here*/
void ConnectTwo(int maze[10][10])
{
	maze[0][0] = 99999;
}

/* Your comment goes here*/
void DayTrader(int *prices, int numPrices, int *bestRun, int *bestRunIndex)
{
	*bestRun = 99999 + prices[0];
	*bestRunIndex = 99999 + numPrices;
}

/* Your comment goes here*/
void Compress(int *input, int *output)
{
	output[0] = 99999 + input[0];
}

/* Your comment goes here*/
void AddOne(char *input, char *output)
{
	input[0] = '1';
	output[0] = '~';
}

/* Your comment goes here*/
void Histogram(char *result, int *values, int numValues)
{
	result[0] = (char)('~' + numValues + values[0]);
}

/* Your comment goes here*/
void GoldRush(int *results, int rows, int cols, int map[MAX_MAP_SIZE][MAX_MAP_SIZE], int bonus)
{
	results[0] = 99993 + rows + cols + map[0][0] + bonus;
}

