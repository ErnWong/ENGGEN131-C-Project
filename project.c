/* ENGGEN131, Semester Two, 2017 */
/* PROJECT SOLUTION BY: Ernest Wong <ewon746> */


#include "project.h"


/* MAGIC NUMBERS */


#define SHEEP_TERMINATOR 9999
#define SHEEP_IGNORE -1
#define MAZE_SIZE 10
#define COMPRESSION_TERMINATOR -1
#define GOLD 9

// PADGET fetches an element in the 2d array
// with padding corrections
#define PADDED_SIZE (MAX_MAP_SIZE + 2)
#define PADGET(sets, r, c) ((sets)[(r)+1][(c)+1])


/* HELPER FUNCTIONS */


/*
 * Computes the GCD of two positive integers using the Euclidean algorithm.
 * Tasks: (1) No Remainders.
 *
 * This uses the fact that:
 *   GCD(x,y) = GCD(x,y-x),   and
 *   GCD(x,y) = GCD(y,x).
 *
 * Thus, the Gcd of x and y can be reduced to a simpler problem of x, y-x
 * if y is greater than x, and can be repetitively reduced until y becomes
 * less than x. This repetitive subtraction can be computed in one go using
 * the modulo remainder operator.
 *
 * Note that the recursive call arguments are swapped around so that upon each
 * "iteration", the larger number is always modulo-remaindered with the smaller
 * number.
 *
 * The base case is when there is no remainder left.
 */
int Gcd(int x, int y)
{
	if (y == 0) return x;
	return Gcd(y, x % y);
}

/*
 * Simple helper to check if charcter is a lowercase alphabetic character.
 * This is to clarify the intention of the code.
 * Tasks: (3) Emphasise.
 *
 * Exploits the fact that the lowercase alphabetic characters lie consecutively
 * on the ASCII table.
 */
int IsLowerAlphabetic(char c)
{
	return 'a' <= c && c <= 'z';
}

/*
 * Returns uppercase version of the character if such exists.
 * Otherwise, returns the orginal character unaltered.
 * Tasks: (3) Emphasise.
 *
 * Exploits the fact that the numeric distance between the lowercase
 * and uppercase variant of a letter is the same for all alphabetic characters.
 */
char ToUpperCase(char c)
{
	if (!IsLowerAlphabetic(c)) return c;
	return c - 'a' + 'A';
}

/*
 * Given a maze, searches for the locations '1' and '2' and
 * stores them into the respective integer via pointers using the
 * (row,column) coordinates.
 * Tasks: (5) Connect Two.
 *
 * Implementation: a simple linear search.
 * By looping through all possible coordinates, the contents of the
 * 2d int array `maze` at the coordinates is checked for the appropriate
 * values. When found, the appropriate variables are set.
 */
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

/*
 * Calculates the sign of an integer.
 * 1 and -1 for positive and negative numbers respectively,
 * 0 for x = 0.
 * Tasks: (5) ConnectTwo
 *
 * Helps clarify the intention of the code and reduce visual clutter.
 */
int Signum(int x)
{
	if (x > 0) return 1;
	if (x < 0) return -1;
	return 0;
}

/*
 * Returns the maximum value in an array of given size.
 * Tasks: (9) Textual Histogram.
 *
 * Implementation: Simple linear search where the maximum
 * value bubbles its way up using a "running-max" variable.
 */
int IntMax(int * values, int size)
{
	int max = values[0];
	for (int i = 1; i < size; i++)
	{
		if (values[i] > max) max = values[i];
	}
	return max;
}

/*
 * Fills a char array with `count` instances of the given character c.
 * Note: the string is not terminated with a null character.
 * Returns a pointer to the string just after the last `c` character appended.
 * Tasks: (9) Textual Histogram.
 *
 * Implementation: A simple loop to iterate given number of times. The
 * position in the string is remembered and incremented using
 * pointer arithmetic, so every iteration through the loop, the character
 * `c` is assigned to an incremented position each time.
 */
char * CharRepeat(char * string, char c, int count)
{
	for (int i = 0; i < count; i++)
	{
		*string = c;
		string++;
	}
	return string;
}

/*
 * Simple helper to check whether a cell is considered gold.
 * This is to separate implementation from intention, in case
 * it requires changing.
 * Tasks: (10) Gold Rush.
 */
int IsGold(int r, int c, int map[MAX_MAP_SIZE][MAX_MAP_SIZE])
{
	return map[r][c] == GOLD;
}

/*
 * Simple helper to check whether a cell is considered pure gold.
 * This is to separate implementation from intention, in case
 * it requires changing.
 * Note: assumes that the cell (r, c) is not an edge cell.
 * Tasks: (10) Gold Rush.
 *
 * Implementation: Simple linear loop, and returns early upon
 * detecting the first non-gold neighbour/cell. Note that its
 * own cell is also checked in the process. The only way it can
 * return truthy is for all of the 8 neighbouring cells to have
 * the value GOLD.
 */
int IsPure(int r, int c, int rows, int cols, int map[MAX_MAP_SIZE][MAX_MAP_SIZE])
{
	if (r < 1 || r >= rows - 1) return 0;
	if (c < 1 || c >= cols - 1) return 0;
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

/*
 * This structure represents a node within the Disjoint-Set data structure
 * (aka Union-Find data structure).
 *
 * Each DisjointSet represents a single cell in the mining map. The
 * way in which the DisjointSets are connected (via the .parent pointer)
 * forms multiple unconnected trees in a jungle, and as the mining map
 * is scanned, neighbouring cells are merged together by connecting
 * and compressing the trees associated with the pair of cells.
 *
 * The .rank property is a measure of the size of the associated tree below
 * the node.
 *
 * Note in terminology:
 *   A single DisjointSet structure = a mining map cell = a node in the jungle.
 *   A jungle = a collection of trees formed by the nodes.
 *
 * The .goldCount property keeps track of the amount of cells in the
 * associated region. Note: it is only accurate for the top-most nodes.
 */
typedef struct DisjointSet DisjointSet;
struct DisjointSet
{
	DisjointSet * parent;
	int rank;
	int goldCount;
	int isGold;
};

/*
 * Initializes a DisjointSet structure for a cell containing
 * the desired gold content.
 *
 * Its parent is set to point to itself as a method of identifying
 * the root of the tree of DisjointSets. It points to itself rather
 * than a special value to simplify the logic for SetFind.
 *
 * Note that the goldCount is sest to 1. This is later set to zero
 * while extracting the DisjointSets jungle into an array, to avoid
 * duplicate counting. I.e., each region is only added once into the
 * results array.
 */
void SetInit(DisjointSet * set, int isWanted)
{
	set->parent = set;
	set->rank = 0;

	set->isGold = 1;

	// Each set initially represents a single disjoint cell of one gold
	set->goldCount = isWanted;
}

/*
 * Sometimes you just need a function to swap two pointers around.
 * Allows writing beautiful DRY code by reusing logic.
 */
void SetSwap(DisjointSet ** setA, DisjointSet ** setB)
{
	DisjointSet * setTemp = *setA;
	*setA = *setB;
	*setB = setTemp;
}

/*
 * Recursively follows the parent nodes until reaching to top-most node.
 * In addition, compresses the tree at the node so that this node
 * directly points to the top-most parent.
 *
 * Base case: the top-most parent itself, which is pointing to itself.
 *
 * Eventually, the SetFind calls reach the top-most root node, and
 * the pointer to itself is returned.
 *
 * As the SetFind calls exit one by one, the pointer to the top-most root node
 * bubbles its way down the call stack.
 */
DisjointSet * SetFind(DisjointSet * set)
{
	if (set->parent != set)
	{
		set->parent = SetFind(set->parent);
	}
	return set->parent;
}

/*
 * Merges two sets together.
 *
 * This finds the top-most root nodes of the two input nodes,
 * and set the parent of the smaller tree root to the larger tree root.
 *
 * The .goldCount tally is also updated in the new root node.
 */
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

	if (rootA->rank == rootB->rank)
	{
		rootB->rank = rootA->rank + 1;
	}

	rootB->goldCount += rootA->goldCount;
}

/*
 * Given a DisjointSet that represents a mining-map cell, if the cell
 * contains the desired gold, then the function explores the cell's top
 * and sideways neighbours and attempts to connect with them to form a
 * single region if such neighbours are also gold-containing.
 *
 * Implementation: a two-level deep nested loop iterates through the
 * possible coordinates of the neighbours relative to the current cell.
 * The relative coordinates of dr = 0 and dc = 0 refers back to the
 * current cell, and so is skipped (it does not make sense to merge itself
 * with itself). The absolute coordinates are then resolved, and
 * if it is found that the cell contains the desired gold, SetMerge
 * is called.
 *
 * Note the use of PADGET, a custom macro function that converts the standard
 * row/col coordinates used in the mining map 2d array, into corresponding
 * coordinates in the padded array (which will be the original coordinates
 * plus an offset of 1 cell in both direction). The corresponding cell
 * is returned/substituted in place by the macro.
 */
void ConnectCell(int r, int c, DisjointSet sets[PADDED_SIZE][PADDED_SIZE])
{
	if (!PADGET(sets,r,c).isGold) return;

	for (int dr = -1; dr <= 0; dr++)
	{
		for (int dc = -1; dc <= 1; dc++)
		{
			if (dr == 0 && dc == 0) continue;

			int r2 = r + dr;
			int c2 = c + dc;

			if (PADGET(sets,r2,c2).isGold)
			{
				SetMerge(&PADGET(sets,r,c), &PADGET(sets,r2,c2));
			}
		}
	}
}

/*
 * Takes unconnected cells of gold represented by the DisjointSets,
 * and connect continuous regions of gold.
 *
 * Implementation: using simple, double-nested for loops,
 * calls the ConnectCell function for every DisjointSet in the 2d array.
 *
 * The primary purposes of pulling this code into this function are:
 * (1) clarify intention of code, and
 * (2) isolate code units for unit testing.
 */
void ConnectAllCells(int rows, int cols,
		DisjointSet sets[PADDED_SIZE][PADDED_SIZE])
{
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			ConnectCell(r, c, sets);
		}
	}
}

/*
 * Sometimes you just want a function that swaps two integer variables
 * for you.
 */
void IntSwap(int * a, int * b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

/*
 * Sorts the input array of size `size` in place.
 * The array after the function exits will be ordered smallest to largest.
 *
 * Implementation: recursive quick sort algorithm.
 * With this partitioning scheme, there are two pointers: left and right.
 * A pivot value is chosen as the middle element's value.
 * The left and right pointers start at the leftmost element and rightmost
 * element respectively, and they slowly sweep towards the middle until
 * they meet.
 *
 * The left pointer moves until it sees a number greater or
 * equal to the pivot, and similarly with the right pointer, it moves until
 * it sees a number less than or equal to the pivot. Once that is found,
 * the left and right numbers are swapped. This process is repeated until
 * the left pointer meets the right pointer, so that at the end of this
 * process, it is guaranteed that everything to the left of the pivot
 * is less than or equal to the pivot, and everything to the right of
 * the pivot is greater than or equal to the pivot. This procedure is known
 * as "partitioning".
 *
 * Note that this means the pivot is now at the correct location, and that
 * throughout the process, the pivot value is always inclusively between
 * the left and right pointers. Thus, when the pointers meet, one of
 * them will contain the pivot value.
 *
 * Once the partitioning is done, the left half and right half of the
 * array is sorted by calling QuickSort recursively.
 *
 * Base case: an array of size 1 or less is already "sorted" by nature.
 */
void QuickSort(int * array, int size)
{
	if (size <= 1) return;

	int * left = array;
	int * right = array + size - 1;
	int pivot = *(right - size / 2);

	// Partition
	while (1)
	{
		while (*left < pivot) left++;
		while (*right > pivot) right--;
		if (left >= right) break;

		IntSwap(left, right);

		left++;
		right--;
	}

	QuickSort(array, (right + 1) - array);
	QuickSort(right + 1, array + size - (right + 1));
}

/*
 * Finds and initializes the DisjointSet structures that correspond
 * to the mining-map cells that contain the desired gold type.
 *
 * Implementation: depending on the value of `bonus`, either
 * iterates through all cells and uses IsGold to check,
 * OR
 * iterates through all non-edge cells and uses IsPure to check.
 *
 * If check passes for a given cell, the corresponding DisjointSet is initialized
 * via the SetInit function.
 */
void GoldRushInitSets(DisjointSet sets[PADDED_SIZE][PADDED_SIZE],
		int rows, int cols, int map[MAX_MAP_SIZE][MAX_MAP_SIZE], int bonus)
{
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			if (IsGold(r, c, map))
			{
				int isDesired = (bonus == 1) || IsPure(r, c, rows, cols, map);
				SetInit(&PADGET(sets,r,c), isDesired);
			}
		}
	}
}

/*
 * For use after connecting all the required DisjointSets,
 * this function scans through all the DisjointSet nodes, and for every
 * separate region of gold, the amount of gold in that region is appended
 * to the `results` array. To keep track of which region has already been
 * processed, the goldCount property of the root of the region is overwritten
 * to zero.
 *
 * Note: a terminating zero value is NOT appended to the end of this array.
 *
 * As non-gold cells are not initialized, they are checked before
 * calling SetFind (or else null pointers are dereferenced).
 *
 * Then, if the root->goldCount is zero, then it implies that the region
 * has been visited before, and so the iteration is skipped.
 *
 * Returns the number of regions.
 */
int ExtractRegions(int * results, DisjointSet sets[PADDED_SIZE][PADDED_SIZE],
		int rows, int cols)
{
	int regionCount = 0;
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			DisjointSet * node = &PADGET(sets,r,c);
			if (!node->goldCount) continue;

			DisjointSet * root = SetFind(node);
			if (!root->goldCount) continue;

			results[regionCount] = root->goldCount;
			root->goldCount = 0;

			regionCount++;
		}
	}
	return regionCount;
}

/*
 * BONUS TASKS.
 *
 * Given a mining map `map` of size `rows` and `cols`, records
 * the amount of the desired gold in each region in the map, ordered from
 * the largest region to the smallest, into the `results` array.
 *
 * Desired gold:
 * if bonus = 1, then this represents cells with value GOLD.
 * if bonus = 2, then this represents cells with value GOLD and with
 * all 8 neighbours with value GOLD.
 *
 * The `results` array is terminated with a zero value.
 *
 * Implementation:
 * This uses a disjoint-set data structure to represent the
 * regions of gold.
 * (1) Initially, each cell is represented by an isolated DisjointSet.
 * (2) The DisjointSets that correspond to the cells with the desired type
 *     of gold are then initialized.
 * (3) The initialized but still isolated DisjointSets are checked one
 *     by one with the neighbours, and any gold-containing neighbour is
 *     merged with the DisjointSet to form regions of gold. The amount
 *     of gold in each region is also counted by the representative DisjointSet
 *     of each region (i.e. the topmost root node of the tree).
 * (4) Each region's gold count is extracted into the results array.
 * (5) The results array is sorted using quick sort algorithm.
 * (6) As quicksort leaves the results array arranged smallest to largest,
 *     the array is then reversed to arrange it largest to smallest.
 * (7) A terminating zero value is appended to the results array.
 */
void GoldRush12(int * results, int rows, int cols,
		int map[MAX_MAP_SIZE][MAX_MAP_SIZE], int bonus)
{
	DisjointSet sets[PADDED_SIZE][PADDED_SIZE] = { 0 };

	GoldRushInitSets(sets, rows, cols, map, bonus);

	ConnectAllCells(rows, cols, sets);

	int regionCount = ExtractRegions(results, sets, rows, cols);
	QuickSort(results, regionCount);

	for (int i = 0; i < regionCount / 2; i++)
	{
		IntSwap(&results[i], &results[regionCount-i-1]);
	}

	results[regionCount] = 0;
}






/* REQUIRED FUNCTIONS */






/*
 * TASK 1. NO REMAINDERS
 *
 * Returns the greatest common divisor of three integers.
 * Returns -1 if any integer is not strictly positive.
 *
 * Implementation:
 * The special case of having any zeros is handled first, and in that case
 * the function returns early.
 *
 * The GCD is the number composed of the largest combination of prime factors
 * that are shared between the three numbers.
 * Thus, as GCD(b, c) finds the largest combination of prime factors shared by
 * b and c, the GCD of a and (GCD(b,c)) finds the largest combination of
 * prime factors shared by all three integers.
 *
 * The GCD function computes using a recursive form of the Euclidean algorithm.
 * See the corresponding helper function for more information.
 */
int DivisorOfThree(int a, int b, int c)
{
	if (a <= 0 || b <= 0 || c <= 0) return -1;
	return Gcd(a, Gcd(b, c));
}

/*
 * TASK 2. COUNTING SHEEP
 *
 * Computes the average sheep count per hour given an array of
 * sheep counts at every given hour. Error values of (-1) are ignored.
 * The array is expected to terminate with the value SHEEP_TERMINATOR = 9999.
 * If there are no valid data, 0.0 is returned.
 *
 * Implementation:
 * A running sum and running count of the non-error values are stored,
 * as the array values are iterated through one by one.
 * The array element of interest is lookedup and incremented using
 * pointer arithmetic.
 */
double AverageSheep(int * counts)
{
	unsigned long sum = 0;
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
	if (!validCount) return 0.0;
	return (double)sum / validCount;
}

/*
 * TASK 3. EMPHASISE
 *
 * Modifies the given string in-place such that the text grouped by a pair
 * of underscores are replaced with an uppercase variant of the inner text.
 * The underscores are also removed.
 *
 * Note: This function assumes the presence of two underscores in the string.
 *
 * Example: abc_de 123fg _2 ----> abcDE 123FG 2
 *
 * Implementation:
 * (1) Fast forward until an underscore is found.
 * (2) Increment to the character after the underscore.
 * (3) Iterate until the next underscore, and overwrite the uppercase
 *     version of the current character into the previous character's location.
 *     That way, the underscore is overwritten and the remaining string is
 *     effectively "collapsed" into the vacant '_' hole.
 * (4) Increment to the character after the underscore.
 * (5) Iterate until the end of the word, and shift the character by two spaces
 *     to the left.
 * (6) Append a null terminator to the word.
 */
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

/*
 * TASK 4. PRIME FACTORS
 *
 * Computes the prime factors of a number, and stores them in the given
 * `factors` array. The number of factors is returned.
 *
 * Implementation:
 * Repetitively divides the number n by p until n no longer contains p as
 * a factor. After the `p` factor is exhausted from the number `n`, the number
 * `p` is incremented and the process continues.
 *
 * Each time n is divisible by p, it means that p is a factor of n, and so
 * the number `p` is appended to the factors array, and the factorCount is
 * incremented. To remove the factor `p` from further consideration,
 * n is divided by p.
 *
 * Note: Prime number testing is not necessary, as each factor p consumes
 * all multiples of itself. Thus, n will not be divisible by any
 * composite number. Prime number testing will not provide any
 * performance gain.
 */
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

/*
 * TASK 5. CONNECT TWO
 *
 * Modifies the 2d array `maze` such that a trail of `3`s is written along
 * the "shortest path" between the cell that contains `1` and the cell that
 * contains `2`.
 *
 * The shortest path defined in this context refers to the path that
 * (1) starts from `1`,
 * (2) always approaches `2` in terms of row/col coordinates, and
 * (3) initially only moves diagonal, then carries on in a straight line.
 *
 * Implementation:
 * After extracting the coordinates for the `1` and `2` using the
 * MazeInitLocations function, the shortest path is generated by always
 * incrementing the row and column number by the Signum of the remaining
 * differences along each coordinates.
 *
 * To prevent overwriting the '1' with the path, the path's coordinates
 * start one iteration closer to '2'.
 */
void ConnectTwo(int maze[MAZE_SIZE][MAZE_SIZE])
{
	int r1 = -1;
	int c1 = -1;
	int r2 = -1;
	int c2 = -1;

	MazeInitLocations(maze, &r1, &c1, &r2, &c2);

	int r = r1 + Signum(r2 - r1);
	int c = c1 + Signum(c2 - c1);
	while (r != r2 || c != c2)
	{
		maze[r][c] = 3;
		r += Signum(r2 - r);
		c += Signum(c2 - c);
	}
}

/*
 * TASK 6. THE WOLF OF WALL STREET
 *
 * Finds the longest sequence of strictly increasing integers in the prices
 * array. The resulting length and starting position of this sequence is
 * stored into the integers bestRun and bestRunIndex.
 *
 * Note that the length of the sequence is defined as the number of additional
 * elements in the sequence after the starting element.
 *
 * Implementation:
 * The default case is when the bestRun is of zero length and starts at
 * index 0. The loop then iteratively attempts to improve this bestRun.
 *
 * The values in the array are iterated from left to right.
 * If the end of the array is reached,
 * OR if the strictly-increasing-condition no longer applies, then
 * it implies that the previous increasing sequence has just ended.
 *
 * At this situation, the length of the currentRun is calculated,
 * and if it improves the "bestRun", it is overwritten into "bestRun".
 *
 * The end of a run also marks the beginning of a new run, and so the
 * currentRunIndex is updated to the current position.
 */
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

/*
 * TASK 7. COMPRESSION
 *
 * Generates a compressed version of an input integer array by
 * replacing every sequentially repeating integer with the pair
 * (repeat count, integer value).
 *
 * The input array is expected to be terminated by the
 * value COMPRESSION_TERMINATOR = -1. The output array is also terminated by
 * COMPRESSION_TERMINATOR.
 *
 * Implementation:
 * Iterating through the array from left to right until the terminator
 * is found, the current integer value is stored and the input pointer
 * advances until the integer value no longer equals the original integer.
 *
 * The repeat count is calculated using pointer arithmetic.
 */
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

/*
 * TASK 8. ARBITRARY INCREMENTING
 *
 * This function increments a number by one, where the input number and output
 * number is an arbitrary precision integer represented by a string array
 * or corresponding numeric characters.
 *
 * Implementation:
 * (1) The length of the input string is determined by advancing until
 *     the null terminator is found. At the same time, the input is checked
 *     for the special case where all digits are '9's, which is the only
 *     situation where the length of the output is different to the length
 *     of the input and all characters require shifting.
 * (2) The special all '9's case is handled first, and returned early.
 * (3) The initial carry is set to 1 to represent the initial increment.
 * (4) The digits are processed from LSB (right) to MSB (left).
 *      - The corresponding output digit is computed as the sum with the
 *        carry.
 *	    - If the output digit exceeds '9',
 *	      carry for the next digit is set to 1,
 *	      and 10 is subtracted away from the "overflowing" output digit.
 * (5) String null terminator character is appended on.
 */
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

	char carry = 1;
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

/*
 * TASK 9. TEXTUAL HISTOGRAM
 *
 * Plots the integer values into a textual histogram (stored into
 * the result character array).
 *
 * Specifications:
 *
 *   ********   - Border
 *   *    X *   - No newlines at the end
 *   *X   X *   - No additional spaces than required
 *   *X X X *
 *   *XXX XX*
 *   ********
 *
 * Implementation:
 * The largest value is calculated for the values array. This determines
 * how high the histogram is and is a necessary piece of information used
 * to determine what height value each row corresponds to.
 *
 * The borders for the top and bottom row is generated using the CharRepeat
 * helper function.
 *
 * Each 'data' row is then iterated through:
 * Each column is checked to see if there should be an 'X' there,
 * in which case an 'X' is appended on.
 * Else, a space is appended on.
 *
 * Because all histogram bars extend from (height=1) to the height
 * of the corresponding frequency value, whenever the frequency value is at
 * above the current height, an 'X' should be inserted.
 */
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

/*
 * TASK 10. GOLD RUSH
 *
 * For bonus tasks, refer to GoldRush12().
 *
 * This function counts the amount of gold and pure gold cells
 * in the 2d array `map`, and stores the counts in
 * results[0] and results[1] respectively.
 *
 * Implementation: simple nested loops are employed to iterate through all
 * possible coordinates (and all possible non-edge coordinates for pure
 * gold counting), and uses the respective helper functions to check
 * if the current cell is gold/pure gold or not.
 */
void GoldRush(int * results, int rows, int cols,
		int map[MAX_MAP_SIZE][MAX_MAP_SIZE], int bonus)
{
	if (bonus)
	{
		GoldRush12(results, rows, cols, map, bonus);
		return;
	}

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
			results[1] += IsPure(r, c, rows, cols, map);
		}
	}
}
