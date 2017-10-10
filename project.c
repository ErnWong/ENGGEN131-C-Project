/* ENGGEN131, Semester Two, 2017 */

/* PROJECT SOLUTION BY: Ernest Wong <ewon746> */

#include "project.h"

/* HELPER FUNCTIONS */
/* If you have defined any "helper" functions, which you call from the required */
/* functions, you should place them here, at the top of the source file.  This will */
/* make it easier for the markers to locate them.  You should also include a */
/* comment at the top of each of the "helper" functions you define which clearly */
/* describes their purpose, and which of the tasks they support. */

#define SHEEP_TERMINATOR 9999
#define SHEEP_IGNORE -1
#define MAZE_SIZE 10
#define COMPRESSION_TERMINATOR -1
#define GOLD 9
#define PADDED_SIZE MAX_ARRAY_SIZE + 2
#define PADGET(sets, r, c) ((sets)[(r)+1][(c)+1])


/* Computes the GCD of two positive integers using the Euclidean algorithm */
/* in recursive form.                                                      */
/* Used in: DivisorOfThree()                                               */
int Gcd(int x, int y)
{
	if (y == 0) return x;
	return Gcd(y, x % y);
}

/* Simple check to see if character is a lowercase alphabetic character */
/* Used in: Emphasise()                                                 */
int IsLowerAlphabetic(char c)
{
	return 'a' <= c && c <= 'z';
}

/* Uses the numeric difference between 'a' and 'A' to shift lowercase */
/* letters to uppercase.                                              */
/* Used in: Emphasise()                                               */
char ToUpperCase(char c)
{
	if (!IsLowerAlphabetic(c)) return c;
	return c - 'a' + 'A';
}

void MazeInitLocations(int maze[MAZE_SIZE][MAZE_SIZE], int * r1, int * c1,
		int * r2, int * c2)
{
	for (int r = 0; r < MAZE_SIZE; r++)
	{
		for (int c = 0; c < MAZE_SIZE; c++)
		{
			switch (maze[r][c])
			{
			case 1:
				*r1 = r;
				*c1 = c;
				break;
			case 2:
				*r2 = r;
				*c2 = c;
				break;
			}
		}
	}
}

/* Simple function calculates sign of an integer */
/* Used in: ConnectTwo()                         */
int Signum(int x)
{
	if (x > 0) return 1;
	if (x < 0) return -1;
	return 0;
}

int IntMax(int * values, int size)
{
	int max = 0;
	for (int i = 0; i < size; i++)
	{
		if (values[i] > max)
		{
			max = values[i];
		}
	}
	return max;
}

char * CharRepeat(char * string, char c, int count)
{
	for (int i = 0; i < count; i++)
	{
		*string = c;
		string++;
	}
	return string;
}

/* Hides implementation to check whether cell contains gold */
/* Used in: GoldRush()                                      */
int IsGold(int r, int c, int map[MAX_MAP_SIZE][MAX_MAP_SIZE])
{
	return map[r][c] == GOLD;
}

/* Hides implementation to check if cell contains pure gold*/
/* Used in: GoldRush()                                     */
int IsPure(int r, int c, int map[MAX_MAP_SIZE][MAX_MAP_SIZE])
{
	for (int dr = -1; dr <= 1; dr++)
	{
		for (int dc = -1; dc <= 1; dc++)
		{
			if (map[r+dr][c+dc] != GOLD)
			{
				return 0;
			}
		}
	}
	return 1;
}

void GoldRush0(int * results, int rows, int cols,
		int map[MAX_MAP_SIZE][MAX_MAP_SIZE])
{
	results[0] = 0;
	results[1] = 0;

	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			results[0] += IsGold(r, c, map);
		}
	}

	for (int r = 1; r < rows - 1; r++)
	{
		for (int c = 1; c < cols - 1; c++)
		{
			results[1] += IsPure(r, c, map);
		}
	}
}

typedef struct DisjointSet DisjointSet;

struct DisjointSet
{
	DisjointSet * parent;
	int rank;
	int goldCount;
	int seen;
};

// Initialize a gold cell
void SetInit(DisjointSet * set)
{
	set->parent = set;
	set->rank = 0;

	// Each set initially represents a single disjoint cell of one gold
	set->goldCount = 1;

	// "seen" is used when creating the array of region sizes
	// to avoid duplicates in the array
	set->seen = 0;
}

void SetSwap(DisjointSet ** setA, DisjointSet ** setB)
{
	DisjointSet * setTemp = *setA;
	*setA = *setB;
	*setB = setTemp;
}

DisjointSet * SetFind(DisjointSet * set)
{
	if (set->parent != set)
	{
		set->parent = SetFind(set->parent);
	}
	return set->parent;
}

void SetMerge(DisjointSet * setA, DisjointSet * setB)
{
	DisjointSet * rootA = SetFind(setA);
	DisjointSet * rootB = SetFind(setB);

	// Don't merge twice
	if (rootA == rootB) return;

	// Make sure rank of A is < rank of B
	if (rootB->rank < rootA->rank)
	{
		SetSwap(&rootA, &rootB);
	}

	// That way, the smaller set is attached to larger
	rootA->parent = rootB;

	// Update their ranks
	if (rootA->rank == rootB->rank)
	{
		rootB->rank = rootA->rank + 1;
	}

	// Combine the gold count and update the new root
	rootB->goldCount += rootA->goldCount;
}

void ConnectCell(int r, int c, DisjointSet sets[PADDED_SIZE][PADDED_SIZE])
{
	// Only consider cells with desired gold type
	// Only those are initialized
	if (!PADGET(sets,r,c).goldCount) return;

	for (int dr = -1; dr <= 0; dr++)
	{
		for (int dc = -1; dc <= 1; dc++)
		{
			if (dr == 0 && dc == 0) continue;

			int r2 = r + dr;
			int c2 = c + dc;

			if (PADGET(sets,r2,c2).goldCount)
			{
				SetMerge(&PADGET(sets,r,c), &PADGET(sets,r2,c2));
			}
		}
	}
}

void IntSwap(int * a, int * b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void QuickSort(int * array, int size)
{
	if (size <= 1) return;

	int * left = array;
	int * right = array + size - 1;
	int * pivot = right;

	// Partition
	while (1)
	{
		while (*left < *pivot && left < right) left++;
		while (*right > *pivot && left < right) right--;
		if (left >= right) break;
		IntSwap(left, right);
	}

	QuickSort(array, pivot - array);
	QuickSort(pivot + 1, array + size - (pivot + 1));
}

void GoldRushInitSets(DisjointSet sets[PADDED_SIZE][PADDED_SIZE],
		int rows, int cols, int map[MAX_MAP_SIZE][MAX_MAP_SIZE], int bonus)
{
	if (bonus == 1)
	{
		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c < cols; c++)
			{
				if (IsGold(r, c, map)) SetInit(&PADGET(sets,r,c));
			}
		}
	}
	else
	{
		for (int r = 1; r < rows - 1; r++)
		{
			for (int c = 1; c < cols - 1; c++)
			{
				if (IsPure(r, c, map)) SetInit(&PADGET(sets,r,c));
			}
		}
	}
}

int ExtractRegions(int * results, DisjointSet sets[PADDED_SIZE][PADDED_SIZE],
		int rows, int cols)
{
	int regionCount = 0;
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			DisjointSet * root = SetFind(&PADGET(sets,r,c));
			if (root->seen) continue;
			root->seen = 1;

			results[regionCount] = root->goldCount;
			regionCount++;
		}
	}
	return regionCount;
}

void GoldRush12(int * results, int rows, int cols,
		int map[MAX_MAP_SIZE][MAX_MAP_SIZE], int bonus)
{
	DisjointSet sets[PADDED_SIZE][PADDED_SIZE] = { 0 };

	GoldRushInitSets(sets, rows, cols, map, bonus);

	// Connect connected regions
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			ConnectCell(r, c, sets);
		}
	}

	int regionCount = ExtractRegions(results, sets, rows, cols);
	QuickSort(results, regionCount);
}


/* REQUIRED FUNCTIONS */
/* Implement each of the required functions below.  The code that is provided initially */
/* for each function is incorrect - you should correct this! */

/* Your comment goes here*/
int DivisorOfThree(int a, int b, int c)
{
	if (a <= 0 || b <= 0 || c <= 0) return -1;
	return Gcd(a, Gcd(b, c));
}

/* Your comment goes here*/
double AverageSheep(int * counts)
{
	double sum = 0.0;
	int validCount = 0;
	while (*counts != SHEEP_TERMINATOR)
	{
		if (*counts != SHEEP_IGNORE)
		{
			sum += *counts;
			validCount++;
		}
		counts++;
	}
	return sum / validCount;
}

/* Your comment goes here*/
void Emphasise(char * word)
{
	// abcd_efg_hijk
	//   ^
	while (*word && *word != '_') word++;

	// abcd_efg_hijk
	//     ^
	word++;
	// abcd_efg_hijk
	//      ^

	while (*word && *word != '_')
	{
		*(word - 1) = ToUpperCase(*word);
		word++;
	}

	// abcdEFGg_hijk
	//         ^
	word++;
	// abcdEFGg_hijk
	//          ^

	while (*word)
	{
		*(word - 2) = *word;
		word++;
	}

	// abcdEFGhijkjk
	//              ^
	*(word - 2) = '\0';
	// abcdEFGhijk
	//              ^
}

/* Your comment goes here*/
int PrimeFactors(int n, int * factors)
{
	int factorCount = 0;
	for (int p = 2; p <= n; p++)
	{
		while (n % p == 0)
		{
			n /= p;
			factors[factorCount] = p;
			factorCount++;
		}
	}
	return factorCount;
}

/* Your comment goes here*/
void ConnectTwo(int maze[MAZE_SIZE][MAZE_SIZE])
{
	int r1 = -1;
	int c1 = -1;
	int r2 = -1;
	int c2 = -1;

	MazeInitLocations(maze, &r1, &c1, &r2, &c2);

	int directionRow = Signum(r2 - r1);
	int directionCol = Signum(c2 - c1);

	int r = r1;
	int c = c1;

	while (r + directionRow != r2 && c + directionCol != c2)
	{
		r += directionRow;
		c += directionCol;
		maze[r][c] = 3;
	}

	r += directionRow;
	c += directionCol;
	directionRow = Signum(r2 - r);
	directionCol = Signum(c2 - c);

	while (r != r2 || c != c2)
	{
		maze[r][c] = 3;
		r += directionRow;
		c += directionCol;
	}
}

/* Your comment goes here*/
void DayTrader(int * prices, int numPrices, int * bestRun, int * bestRunIndex)
{
	*bestRun = -1;
	int currentRunIndex = 0;
	for (int i = 1; i <= numPrices; i++)
	{
		if (i == numPrices || prices[i] <= prices[i - 1])
		{
			int currentRun = i - currentRunIndex - 1;
			if (*bestRun < currentRun)
			{
				*bestRun = currentRun;
				*bestRunIndex = currentRunIndex;
			}
			currentRunIndex = i;
		}
	}
}

/* Your comment goes here*/
void Compress(int * input, int * output)
{
	while (*input != COMPRESSION_TERMINATOR)
	{
		int data = *input;
		int * start = input;

		while (*input == data) input++;

		output[0] = input - start;
		output[1] = data;
		output += 2;
	}
	*output = COMPRESSION_TERMINATOR;
}

/* Your comment goes here*/
void AddOne(char * input, char * output)
{
	int digitCount = 0;
	int isAllNines = 1;
	while (input[digitCount])
	{
		isAllNines = isAllNines && input[digitCount] == '9';
		digitCount++;
	}

	if (isAllNines)
	{
		output[0] = '1';
		for (int i = 1; i <= digitCount; i++)
		{
			output[i] = '0';
		}
		output[digitCount + 1] = '\0';
		return;
	}

	char carry = 0;
	input[digitCount - 1]++;
	for (int i = digitCount - 1; i >= 0; i--)
	{
		output[i] = input[i] + carry;
		carry = 0;
		if (output[i] > '9')
		{
			output[i] -= 10;
			carry = 1;
		}
	}
	output[digitCount] = '\0';
}

/* Your comment goes here*/
void Histogram(char * result, int * values, int numValues)
{
	int max = IntMax(values, numValues);

	result = CharRepeat(result, '*', numValues + 2);

	*result = '\n';
	result++;

	for (int r = 0; r < max; r++)
	{
		*result = '*';
		result++;
		int currentHeight = max - r;
		for (int i = 0; i < numValues; i++)
		{
			if (values[i] >= currentHeight) *result = 'X';
			else *result = ' ';
			result++;
		}
		*result = '*';
		result++;
		*result = '\n';
		result++;
	}

	result = CharRepeat(result, '*', numValues + 2);
	*result = '\0';
}

/* Your comment goes here*/
void GoldRush(int * results, int rows, int cols,
		int map[MAX_MAP_SIZE][MAX_MAP_SIZE], int bonus)
{
	switch (bonus)
	{
	case 0:
		GoldRush0(results, rows, cols, map);
		break;
	case 1:
	case 2:
		GoldRush12(results, rows, cols, map, bonus);
		break;
	default:
		results[0] = 99993 + rows + cols + map[0][0] + bonus;
		break;
	}
}
