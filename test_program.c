#include "project.h"
#include "helpers.h"
// #include "project.c"

#include <limits.h>

int testPlan = 0;
int testSuccess = 0;
int testFailure = 0;
int testTotalPlanned = 0;
int testTotalSuccess = 0;
int testTotalFailure = 0;

void TestPlan(int count)
{
	testPlan = count;
	testSuccess = 0;
	testFailure = 0;
	printf("\n1..%d\n", count);
}

void TestEnd(void)
{
	printf("\n# Summary: %d of %d passed\n", testSuccess, testPlan);
	if (testPlan == testSuccess)
	{
		puts("# All ok!");
	}
	testTotalPlanned += testPlan;
	testTotalSuccess += testSuccess;
	testTotalFailure += testFailure;
}

int TestOk(int testNumber, char * message, int condition)
{
	if (condition) printf("ok %d", testNumber);
	else printf("not ok %d", testNumber);
	printf(" - %s\n", message);
	testFailure += !condition;
	testSuccess += !!condition;
	return condition;
}

int TestEqualsInt(int testNumber, char * message, int actual, int desired)
{
	int condition = actual == desired;
	if (condition)
	{
		printf("ok %d - %s\n", testNumber, message);
		testSuccess++;
	}
	else
	{
		printf("not ok %d - %s\n", testNumber, message);
		printf("# expcted %d, but got %d\n", desired, actual);
		testFailure++;
	}
	return condition;
}

int TestEqualsDouble(int testNumber, char * message, double actual, double desired)
{
	double error = actual - desired;
	int condition = error <= 0.000001 && error >= -0.000001;
	if (condition)
	{
		printf("ok %d - %s\n", testNumber, message);
		testSuccess++;
	}
	else
	{
		printf("not ok %d - %s\n", testNumber, message);
		printf("# expcted %f, but got %f\n", desired, actual);
		testFailure++;
	}
	return condition;
}

int TestEqualsString(int testNumber, char * message, char * actual, char * desired)
{
	int condition = strcmp(actual, desired) == 0;
	if (condition)
	{
		printf("ok %d - %s\n", testNumber, message);
		testSuccess++;
	}
	else
	{
		printf("not ok %d - %s\n", testNumber, message);
		printf("# expcted \"%s\", but got \"%s\"\n", desired, actual);
		testFailure++;
	}
	return condition;
}

void TestGcd(void)
{
	printf("\n# Gcd\n");
	TestPlan(12);
	TestEqualsInt(1 , "Gcd(1, 1) - Lowest Equal"                       , Gcd(1, 1)                , 1);
	TestEqualsInt(2 , "Gcd(1, 2) - Lowest Different 1"                 , Gcd(1, 2)                , 1);
	TestEqualsInt(3 , "Gcd(2, 1) - Lowest Different 2"                 , Gcd(2, 1)                , 1);
	TestEqualsInt(4 , "Gcd(INT_MAX, INT_MAX) - Highest Equal"          , Gcd(INT_MAX, INT_MAX)    , INT_MAX);
	TestEqualsInt(5 , "Gcd(INT_MAX, INT_MAX - 1) - Highest Different 1", Gcd(INT_MAX, INT_MAX - 1), 1);
	TestEqualsInt(6 , "Gcd(INT_MAX - 1, INT_MAX) - Highest Different 2", Gcd(INT_MAX - 1, INT_MAX), 1);
	TestEqualsInt(7 , "Gcd(INT_MAX, 1) - Extremes 1"                   , Gcd(INT_MAX, 1)          , 1);
	TestEqualsInt(8 , "Gcd(1, INT_MAX) - Extremes 2"                   , Gcd(1, INT_MAX)          , 1);
	TestEqualsInt(9 , "Gcd(2, 4)"                                      , Gcd(2, 4)                , 2);
	TestEqualsInt(10, "Gcd(4, 2)"                                      , Gcd(4, 2)                , 2);
	TestEqualsInt(11, "Gcd(54, 24)"                                    , Gcd(54, 24)              , 6);
	TestEqualsInt(12, "Gcd(24, 54)"                                    , Gcd(24, 54)              , 6);
	TestEnd();
}

void TestIsLowerAlphabetic(void)
{
	printf("\n# IsLowerAlphabetic\n");
	TestPlan(1);
	int isOkay = 1;
	for (int i = 0; i < 256; i++)
	{
		int expected =
				i == 'a' ||
				i == 'b' ||
				i == 'c' ||
				i == 'd' ||
				i == 'e' ||
				i == 'f' ||
				i == 'g' ||
				i == 'h' ||
				i == 'i' ||
				i == 'j' ||
				i == 'k' ||
				i == 'l' ||
				i == 'm' ||
				i == 'n' ||
				i == 'o' ||
				i == 'p' ||
				i == 'q' ||
				i == 'r' ||
				i == 's' ||
				i == 't' ||
				i == 'u' ||
				i == 'v' ||
				i == 'w' ||
				i == 'x' ||
				i == 'y' ||
				i == 'z';
		if (expected != IsLowerAlphabetic((char)i))
		{
			isOkay = 0;
			break;
		}
	}
	TestOk(1, "Brute force", isOkay);
	TestEnd();
}

void TestToUpperCase(void)
{
	printf("\n# ToUpperCase\n");
	TestPlan(31);
	TestEqualsInt( 1, "a", ToUpperCase('a'), 'A');
	TestEqualsInt( 2, "b", ToUpperCase('b'), 'B');
	TestEqualsInt( 3, "c", ToUpperCase('c'), 'C');
	TestEqualsInt( 4, "d", ToUpperCase('d'), 'D');
	TestEqualsInt( 5, "e", ToUpperCase('e'), 'E');
	TestEqualsInt( 6, "f", ToUpperCase('f'), 'F');
	TestEqualsInt( 7, "g", ToUpperCase('g'), 'G');
	TestEqualsInt( 8, "h", ToUpperCase('h'), 'H');
	TestEqualsInt( 9, "i", ToUpperCase('i'), 'I');
	TestEqualsInt(10, "j", ToUpperCase('j'), 'J');
	TestEqualsInt(11, "k", ToUpperCase('k'), 'K');
	TestEqualsInt(12, "l", ToUpperCase('l'), 'L');
	TestEqualsInt(13, "m", ToUpperCase('m'), 'M');
	TestEqualsInt(14, "n", ToUpperCase('n'), 'N');
	TestEqualsInt(15, "o", ToUpperCase('o'), 'O');
	TestEqualsInt(16, "p", ToUpperCase('p'), 'P');
	TestEqualsInt(17, "q", ToUpperCase('q'), 'Q');
	TestEqualsInt(18, "r", ToUpperCase('r'), 'R');
	TestEqualsInt(19, "s", ToUpperCase('s'), 'S');
	TestEqualsInt(20, "t", ToUpperCase('t'), 'T');
	TestEqualsInt(21, "u", ToUpperCase('u'), 'U');
	TestEqualsInt(22, "v", ToUpperCase('v'), 'V');
	TestEqualsInt(23, "w", ToUpperCase('w'), 'W');
	TestEqualsInt(24, "x", ToUpperCase('x'), 'X');
	TestEqualsInt(25, "y", ToUpperCase('y'), 'Y');
	TestEqualsInt(26, "z", ToUpperCase('z'), 'Z');
	TestEqualsInt(27, "A - Should not change", ToUpperCase('A'), 'A');
	TestEqualsInt(28, "Z - Should not change", ToUpperCase('Z'), 'Z');
	TestEqualsInt(29, "2 - Should not change", ToUpperCase('2'), '2');
	TestEqualsInt(30, "'a'-1 - Should not change", ToUpperCase('a'-1), 'a'-1);
	TestEqualsInt(31, "'z'+1 - Should not change", ToUpperCase('z'+1), 'z'+1);
	TestEnd();
}

void TestMazeInitLocations(void)
{
	printf("\n# MazeInitLocations\n");
	TestPlan(1);

	int maze[MAZE_SIZE][MAZE_SIZE] =
	{
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};
	int pass = 1;
	for (int r1 = 0; r1 < MAZE_SIZE; r1++)
	{
		for (int c1 = 0; c1 < MAZE_SIZE; c1++)
		{
			for (int r2 = 0; r2 < MAZE_SIZE; r2++)
			{
				for (int c2 = 0; c2 < MAZE_SIZE; c2++)
				{
					if (r1 == r2 && c1 == c2) continue;
					maze[r1][c1] = 1;
					maze[r2][c2] = 2;
					int rr1, cc1, rr2, cc2;
					MazeInitLocations(maze, &rr1, &cc1, &rr2, &cc2);
					if (r1 != rr1 || r2 != rr2 || c1 != c1 || c2 != cc2)
					{
						printf("# Incorrect location - expected (%d,%d,%d,%d), got (%d,%d,%d,%d)\n", r1, c1, r2, c2, rr1, cc1, rr2, cc2);
						pass = 0;
					}
					maze[r1][c1] = 0;
					maze[r2][c2] = 0;
				}
			}
		}
	}
	TestOk(1, "brute force test", pass);
	TestEnd();
}

void TestSignum(void)
{
	printf("\n# Signum\n");
	TestPlan(6);
	TestEqualsInt(1, "Zero", Signum(0), 0);
	TestEqualsInt(2, "+1", Signum(1), 1);
	TestEqualsInt(3, "-1", Signum(-1), -1);
	TestEqualsInt(4, "INT_MAX", Signum(INT_MAX), 1);
	TestEqualsInt(5, "-INT_MAX", Signum(-INT_MAX), -1);
	TestEqualsInt(6, "3", Signum(3), 1);
	TestEnd();
}

void TestIntMax(void)
{
	TestPlan(15);

	int singleA[1] = { 0 };
	TestEqualsInt(1, "{ 0 }", IntMax(singleA, 1), 0);

	int singleB[1] = { 1 };
	TestEqualsInt(2, "{ 1 }", IntMax(singleB, 1), 1);

	int singleC[1] = { -1 };
	TestEqualsInt(3, "{ -1 }", IntMax(singleC, 1), -1);

	int singleD[1] = { INT_MAX };
	TestEqualsInt(4, "{ INT_MAX }", IntMax(singleD, 1), INT_MAX);

	int singleE[1] = { -INT_MAX };
	TestEqualsInt(5, "{ -INT_MAX }", IntMax(singleE, 1), -INT_MAX);

	int pass = 1;
	for (int i = -2; i <= 2; i++)
	{
		for (int j = -2; j <= 2; j++)
		{
			int x1 = i == -2? -INT_MAX : i == 2? INT_MAX : i;
			int x2 = j == -2? -INT_MAX : j == 2? INT_MAX : j;
			int max = x1 > x2 ? x1 : x2;
			int pair[2];
			pair[0] = x1;
			pair[1] = x2;
			int result = IntMax(pair, 2);
			if (result != max)
			{
				printf("# Incorrect max of %d and %d. Expected %d, got %d\n", x1, x2, max, result);
				pass = 0;
			}
		}
	}
	TestOk(6, "Important pairs (25 combinations)", pass);

	int oddStart[11] =     { 11, 5, 3, 1, 7 , 9 , 3, 3, 1, 7, 5 };
	int oddMid[11] =       { 1 , 5, 3, 1, 11, 9 , 3, 3, 1, 7, 5 };
	int oddEnd[11] =       { 1 , 5, 3, 1, 7 , 9 , 3, 3, 1, 7, 11 };
	int oddRepeated[12] =  { 1 , 5, 3, 1, 11, 9 , 3, 3, 1, 7, 11 };
	int evenStart[12] =    { 11, 5, 3, 3, 1 , 7 , 9, 3, 3, 1, 7, 5 };
	int evenMid[12] =      { 1 , 5, 3, 3, 1 , 11, 9, 3, 3, 1, 7, 5 };
	int evenEnd[12] =      { 1 , 5, 3, 3, 1 , 7 , 9, 3, 3, 1, 7, 11 };
	int evenRepeated[12] = { 1 , 5, 3, 3, 1 , 11, 9, 3, 3, 1, 7, 11 };
	int evenAllEqual[12] = { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };
	TestEqualsInt( 7, "Odd-sized array, max @ start"  , IntMax(oddStart    ,11), 11);
	TestEqualsInt( 8, "Odd-sized array, max @ mid"    , IntMax(oddMid      ,11), 11);
	TestEqualsInt( 9, "Odd-sized array, max @ end"    , IntMax(oddEnd      ,11), 11);
	TestEqualsInt(10, "Odd-sized array, max repeated" , IntMax(oddRepeated ,11), 11);
	TestEqualsInt(11, "Even-sized array, max @ start" , IntMax(evenStart   ,12), 11);
	TestEqualsInt(12, "Even-sized array, max @ mid"   , IntMax(evenMid     ,12), 11);
	TestEqualsInt(13, "Even-sized array, max @ end"   , IntMax(evenEnd     ,12), 11);
	TestEqualsInt(14, "Even-sized array, max repeated", IntMax(evenRepeated,12), 11);
	TestEqualsInt(15, "Even-sized array, all equal"   , IntMax(evenAllEqual,12), 3);

	TestEnd();
}

void TestIsPure(void)
{
	printf("\n# IsPure\n");
	TestPlan(5);

	int pass = 1;
	for (int i = 0; i < (1 << 8); i++)
	{
		int map[MAX_MAP_SIZE][MAX_MAP_SIZE] = { 0 };
		map[1][1] = GOLD * !!(i & (1 << 0));
		map[1][2] = GOLD * !!(i & (1 << 1));
		map[1][3] = GOLD * !!(i & (1 << 2));
		map[2][1] = GOLD * !!(i & (1 << 3));
		map[2][2] = 0;
		map[2][3] = GOLD * !!(i & (1 << 4));
		map[3][1] = GOLD * !!(i & (1 << 5));
		map[3][2] = GOLD * !!(i & (1 << 6));
		map[3][3] = GOLD * !!(i & (1 << 7));

		int result = IsPure(2, 2, 4, 4, map);
		if (result)
		{
			printf("# Incorrect - Subtest mask: %d\n", i);
			pass = 0;
		}
	}
	TestOk(1, "Brute force test - Nongold", pass);

	pass = 1;
	for (int i = 0; i < (1 << 8) - 1; i++)
	{
		int map[MAX_MAP_SIZE][MAX_MAP_SIZE] = { 0 };
		map[1][1] = GOLD * !!(i & (1 << 0));
		map[1][2] = GOLD * !!(i & (1 << 1));
		map[1][3] = GOLD * !!(i & (1 << 2));
		map[2][1] = GOLD * !!(i & (1 << 3));
		map[2][2] = GOLD;
		map[2][3] = GOLD * !!(i & (1 << 4));
		map[3][1] = GOLD * !!(i & (1 << 5));
		map[3][2] = GOLD * !!(i & (1 << 6));
		map[3][3] = GOLD * !!(i & (1 << 7));

		int result = IsPure(2, 2, 4, 4, map);
		if (result)
		{
			printf("# Incorrect - Subtest mask: %d\n", i);
			pass = 0;
		}
	}
	TestOk(2, "Brute force test - Gold", pass);

	int pureMap[MAX_MAP_SIZE][MAX_MAP_SIZE] = { 0 };
	pureMap[1][1] = GOLD;
	pureMap[1][2] = GOLD;
	pureMap[1][3] = GOLD;
	pureMap[2][1] = GOLD;
	pureMap[2][2] = GOLD;
	pureMap[2][3] = GOLD;
	pureMap[3][1] = GOLD;
	pureMap[3][2] = GOLD;
	pureMap[3][3] = GOLD;
	TestEqualsInt(3, "The only truthy input", IsPure(2, 2, 4, 4, pureMap), 1);

	pass = 1;
	for (int i = 0; i < 9; i++)
	{
		int map[MAX_MAP_SIZE][MAX_MAP_SIZE] = { 0 };
		map[1][1] = i;
		map[1][2] = i;
		map[1][3] = i;
		map[2][1] = i;
		map[2][2] = GOLD;
		map[2][3] = i;
		map[3][1] = i;
		map[3][2] = i;
		map[3][3] = i;

		int result = IsPure(2, 2, 4, 4, map);
		if (result)
		{
			printf("# Incorrect - Subtest mask: %d\n", i);
			pass = 0;
		}
	}
	TestOk(4, "Should not return true for non-gold neighbours", pass);

	int fullPureMap[MAX_MAP_SIZE][MAX_MAP_SIZE] = { 0 };
	fullPureMap[0][0] = GOLD;
	fullPureMap[0][1] = GOLD;
	fullPureMap[0][2] = GOLD;
	fullPureMap[1][0] = GOLD;
	fullPureMap[1][1] = GOLD;
	fullPureMap[1][2] = GOLD;
	fullPureMap[2][0] = GOLD;
	fullPureMap[2][1] = GOLD;
	fullPureMap[2][2] = GOLD;
	pass = 1
		&& !IsPure(0, 0, 3, 3, fullPureMap)
		&& !IsPure(0, 1, 3, 3, fullPureMap)
		&& !IsPure(0, 2, 3, 3, fullPureMap)
		&& !IsPure(1, 0, 3, 3, fullPureMap)
		&& !IsPure(1, 2, 3, 3, fullPureMap)
		&& !IsPure(2, 0, 3, 3, fullPureMap)
		&& !IsPure(2, 1, 3, 3, fullPureMap)
		&& !IsPure(2, 2, 3, 3, fullPureMap)
		&&  IsPure(1, 1, 3, 3, fullPureMap);
	TestOk(5, "Returns falsy for edges", pass);

	TestEnd();
}

void TestDisjointSet(void)
{
	printf("\n# DisjointSet Functions\n");
	TestPlan(17);

	DisjointSet setA, setB, setC, setD, setE, setF, setG, setH;

	SetInit(&setA);
	SetInit(&setB);
	DisjointSet * setpA = &setA;
	DisjointSet * setpB = &setB;
	SetSwap(&setpA, &setpB);
	TestOk(1, "Set swapping", setpA == &setB && setpB == &setA);

	TestOk(2, "New sets point to themselves", SetFind(&setA) == &setA);

	SetInit(&setA);
	SetInit(&setB);
	SetInit(&setC);
	SetInit(&setD);
	SetMerge(&setA, &setB);
	TestOk(3, "Merge on new sets", SetFind(&setA) == SetFind(&setB));
	TestOk(4, "Merge does not effect other sets", SetFind(&setA) != SetFind(&setC));
	TestOk(5, "Merge does not effect other sets", SetFind(&setD) != SetFind(&setC));

	SetInit(&setA);
	SetInit(&setB);
	SetInit(&setC);
	SetInit(&setD);
	TestOk(6, "SetInit resets any merges", SetFind(&setA) != SetFind(&setB));
	SetMerge(&setB, &setA);
	TestOk(7, "Merge on new sets - reverse order", SetFind(&setA) == SetFind(&setB));
	TestOk(8, "Merge does not effect other sets", SetFind(&setA) != SetFind(&setC));
	TestOk(9, "Merge does not effect other sets", SetFind(&setD) != SetFind(&setC));
	SetMerge(&setB, &setC);
	TestOk(10, "Merge in sequence - part 1", SetFind(&setA) == SetFind(&setC));
	SetMerge(&setC, &setD);
	TestOk(11, "Merge in sequence - part 2", SetFind(&setA) == SetFind(&setD));

	SetInit(&setA);
	SetInit(&setB);
	SetInit(&setC);
	SetInit(&setD);
	SetMerge(&setB, &setA);
	SetMerge(&setC, &setB);
	TestOk(12, "Merge in sequence - reversed 1", SetFind(&setA) == SetFind(&setC));
	SetMerge(&setD, &setC);
	TestOk(13, "Merge in sequence - reversed 2", SetFind(&setA) == SetFind(&setD));

	SetInit(&setA);
	SetInit(&setB);
	SetInit(&setC);
	SetInit(&setD);
	SetMerge(&setA, &setB);
	SetMerge(&setA, &setC);
	TestOk(14, "Merge in sequence - same first set 1", SetFind(&setA) == SetFind(&setC));
	SetMerge(&setA, &setD);
	TestOk(15, "Merge in sequence - same first set 2", SetFind(&setA) == SetFind(&setD));

	SetInit(&setA);
	SetInit(&setB);
	SetInit(&setC);
	SetInit(&setD);
	SetMerge(&setA, &setB);
	SetMerge(&setC, &setD);
	SetMerge(&setA, &setD);
	TestOk(16, "Merge two groups", SetFind(&setA) == SetFind(&setD));

	SetInit(&setA);
	SetInit(&setB);
	SetInit(&setC);
	SetInit(&setD);
	SetInit(&setE);
	SetInit(&setF);
	SetInit(&setG);
	SetInit(&setH);
	SetMerge(&setA, &setB);
	SetMerge(&setC, &setD);
	SetMerge(&setF, &setG);
	SetMerge(&setF, &setA);
	SetMerge(&setH, &setC);
	int isOkay = 1
		&& SetFind(&setA) == SetFind(&setB)
		&& SetFind(&setA) == SetFind(&setF)
		&& SetFind(&setA) == SetFind(&setG)
		&& SetFind(&setC) == SetFind(&setD)
		&& SetFind(&setC) == SetFind(&setH)
		&& SetFind(&setA) != SetFind(&setC)
		&& SetFind(&setA) != SetFind(&setE)
		&& SetFind(&setC) != SetFind(&setE);
	TestOk(17, "Larger example", isOkay);

	TestEnd();
}

void ResetSets(DisjointSet sets[PADDED_SIZE][PADDED_SIZE])
{
	for (int r = 0; r < PADDED_SIZE; r++)
	{
		for (int c = 0; c < PADDED_SIZE; c++)
		{
			sets[r][c].parent = NULL;
			sets[r][c].rank = 0;
			sets[r][c].goldCount = 0;
			sets[r][c].isGold = 0;
		}
	}
}

void ResetMap(int map[MAX_MAP_SIZE][MAX_MAP_SIZE])
{
	for (int r = 0; r < MAX_MAP_SIZE; r++)
	{
		for (int c = 0; c < MAX_MAP_SIZE; c++)
		{
			map[r][c] = 0;
		}
	}
}
void FillMap(int rows, int cols, int map[MAX_MAP_SIZE][MAX_MAP_SIZE], int value)
{
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			map[r][c] = value;
		}
	}
}

void VisualiseSets(int rows, int cols, DisjointSet sets[PADDED_SIZE][PADDED_SIZE])
{
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			DisjointSet * setA = &PADGET(sets,r,c);
			DisjointSet * setB = &sets[r][c];
			printf("# <%8ld>(%2d,%2d)[%8ld, %8d, %8d]{%8ld, %8d, %8d}\n", (long int)setB,r,c,(long int)setA->parent, setA->rank, setA->goldCount, (long int)setB->parent, setB->rank, setB->goldCount);
		}
	}
}

int TestSetConnections(int info[][5], DisjointSet sets[PADDED_SIZE][PADDED_SIZE])
{
	int pass = 1;
	for (int i = 0; info[i][0] != -1; i++)
	{
		DisjointSet * resultA = SetFind(&PADGET(sets, info[i][0], info[i][1]));
		DisjointSet * resultB = SetFind(&PADGET(sets, info[i][2], info[i][3]));

		if ((resultA == resultB) != info[i][4])
		{
			pass = 0;
			printf("# Incorrect: Expected ");
			switch (info[i][4])
			{
			case 1:
				printf("equal ");
				break;
			case 0:
				printf("different ");
				break;
			}
			printf("parents between (%2d, %2d)[%ld] and (%2d, %2d)[%ld]\n", info[i][0], info[i][1], (long int)resultA, info[i][2], info[i][3], (long int)resultB);
		}
	}
	return pass;
}

void TestConnectCell(void)
{
	printf("\n# ConnectCell and GoldRushInitSets\n");
	TestPlan(11);

	int map[MAX_MAP_SIZE][MAX_MAP_SIZE] =
	{
	//   0 1 2 3 4 5 6 7 8 9 1011121314
		{1,2,2,0,0,0,0,0,0,0,0,0,0,0,0}, //  0
		{0,4,3,0,0,0,0,9,9,8,0,0,0,0,0}, //  1
		{0,2,0,3,3,0,0,9,9,0,0,0,0,0,0}, //  2
		{0,0,0,0,0,4,6,9,9,6,0,0,0,0,0}, //  3
		{0,0,0,0,0,0,9,0,8,0,0,6,0,0,0}, //  4
		{0,0,9,9,9,9,0,0,0,0,7,7,8,8,0}, //  5
		{0,0,9,9,9,9,0,0,0,0,0,7,0,0,0}, //  6
		{0,0,9,9,9,9,0,1,1,1,2,2,2,2,2}, //  7
		{0,0,0,9,9,0,0,0,0,0,0,0,0,3,0}, //  8
		{0,0,0,4,4,0,0,0,0,0,0,0,5,6,0}, //  9
		{0,0,0,0,9,9,9,0,0,9,0,0,0,5,0}, // 10
		{0,0,1,2,9,9,9,0,0,0,9,0,0,4,2}, // 11
		{0,0,0,0,9,9,9,0,0,0,9,9,9,0,0}, // 12
		{9,9,0,0,0,0,1,0,0,0,0,9,0,0,0}, // 13
		{9,0,0,0,0,0,2,2,0,0,0,0,0,0,0}  // 14
	};
	DisjointSet sets[PADDED_SIZE][PADDED_SIZE] = { 0 };
	GoldRushInitSets(sets, 15, 15, map, 1);
	ConnectAllCells(15, 15, sets);

	int info1[][5] =
	{
		{  1, 7,  1,  8, 1 },
		{  1, 7,  2,  7, 1 },
		{  1, 7,  2,  8, 1 },
		{  1, 7,  3,  7, 1 },
		{  1, 7,  3,  8, 1 },
		{  1, 7,  4,  6, 1 },
		{  1, 7,  5,  2, 1 },
		{  1, 7,  5,  3, 1 },
		{  1, 7,  5,  4, 1 },
		{  1, 7,  5,  5, 1 },
		{  1, 7,  6,  2, 1 },
		{  1, 7,  6,  3, 1 },
		{  1, 7,  6,  4, 1 },
		{  1, 7,  6,  5, 1 },
		{  1, 7,  7,  2, 1 },
		{  1, 7,  7,  3, 1 },
		{  1, 7,  7,  4, 1 },
		{  1, 7,  7,  5, 1 },
		{  1, 7,  8,  3, 1 },
		{  1, 7,  8,  4, 1 },

		{ 10, 4, 10,  5, 1 },
		{ 10, 4, 10,  6, 1 },
		{ 10, 4, 11,  4, 1 },
		{ 10, 4, 11,  5, 1 },
		{ 10, 4, 11,  6, 1 },
		{ 10, 4, 12,  4, 1 },
		{ 10, 4, 12,  5, 1 },
		{ 10, 4, 12,  6, 1 },

		{ 10, 9, 11, 10, 1 },
		{ 10, 9, 12, 10, 1 },
		{ 10, 9, 12, 11, 1 },
		{ 10, 9, 12, 12, 1 },
		{ 10, 9, 13, 11, 1 },

		{ 13, 0, 13,  1, 1 },
		{ 13, 0, 14,  0, 1 },

		{  1, 7, 10,  4, 0 },
		{  1, 7, 10,  9, 0 },
		{  1, 7, 13,  0, 0 },
		{ 10, 4, 10,  9, 0 },
		{ 10, 4, 13,  0, 0 },
		{ 10, 9, 13,  0, 0 },

		{ -1 }
	};

	TestOk(1, "Moderately large example situation - bonus 1", TestSetConnections(info1, sets));

	ResetSets(sets);
	GoldRushInitSets(sets, 15, 15, map, 2);
	ConnectAllCells(15, 15, sets);

	int info2[][5] =
	{
		{  6, 3,  6,  4, 1 },
		{  6, 3, 11,  5, 0 },
		{ -1 }
	};

	TestOk(2, "Moderately large example situation - bonus 2", TestSetConnections(info2, sets));

	ResetMap(map);
	ResetSets(sets);
	GoldRushInitSets(sets, 8, 8, map, 1);
	ConnectAllCells(8, 8, sets);
	int pass = 1;
	for (int r = 0; r < 8; r++)
	{
		for (int c = 0; c < 8; c++)
		{
			pass &= 1
				&& PADGET(sets,r,c).parent == 0
				&& PADGET(sets,r,c).rank == 0
				&& PADGET(sets,r,c).goldCount == 0;
		}
	}
	ResetSets(sets);
	GoldRushInitSets(sets, 8, 8, map, 2);
	ConnectAllCells(8, 8, sets);
	for (int r = 0; r < 8; r++)
	{
		for (int c = 0; c < 8; c++)
		{
			pass &= 1
				&& PADGET(sets,r,c).parent == 0
				&& PADGET(sets,r,c).rank == 0
				&& PADGET(sets,r,c).goldCount == 0;
		}
	}
	TestOk(3, "Empty map should leave sets all zeros", pass);

	ResetMap(map);
	ResetSets(sets);
	GoldRushInitSets(sets, MAX_MAP_SIZE, MAX_MAP_SIZE, map, 2);
	ConnectAllCells(MAX_MAP_SIZE, MAX_MAP_SIZE, sets);
	pass = 1;
	for (int r = 0; r < MAX_MAP_SIZE; r++)
	{
		for (int c = 0; c < MAX_MAP_SIZE; c++)
		{
			pass &= 1
				&& PADGET(sets,r,c).parent == 0
				&& PADGET(sets,r,c).rank == 0
				&& PADGET(sets,r,c).goldCount == 0;
		}
	}
	TestOk(4, "Empty map should leave sets all zeros (LARGE input)", pass);

	ResetMap(map);
	FillMap(8, 8, map, GOLD);
	ResetSets(sets);
	GoldRushInitSets(sets, 8, 8, map, 1);
	ConnectAllCells(8, 8, sets);
	pass = 1;
	for (int r = 0; r < 8; r++)
	{
		for (int c = 0; c < 8; c++)
		{
			DisjointSet * resultA = SetFind(&PADGET(sets,r,c));
			DisjointSet * resultB = SetFind(&PADGET(sets,0,0));
			if (resultA != resultB)
			{
				pass = 0;
				printf("# Incorrect: (%d %d)[%ld] should be [%ld]\n", r, c, (long int)resultA, (long int)resultB);
			}
		}
	}
	TestOk(5, "Full map should join everything up - Bonus 1", pass);

	ResetSets(sets);
	GoldRushInitSets(sets, 8, 8, map, 2);
	ConnectAllCells(8, 8, sets);
	pass = 1;
	for (int r = 1; r < 8 - 1; r++)
	{
		for (int c = 1; c < 8 - 1; c++)
		{
			DisjointSet * resultA = SetFind(&PADGET(sets,r,c));
			DisjointSet * resultB = SetFind(&PADGET(sets,1,1));
			if (resultA != resultB)
			{
				pass = 0;
				printf("# Incorrect: (%d %d)[%ld] should be [%ld]\n", r, c, (long int)resultA, (long int)resultB);
			}
		}
	}
	TestOk(6, "Full map should join non-outer cells up - Bonus 2", pass);

	ResetMap(map);
	FillMap(MAX_MAP_SIZE, MAX_MAP_SIZE, map, GOLD);
	ResetSets(sets);
	GoldRushInitSets(sets, MAX_MAP_SIZE, MAX_MAP_SIZE, map, 1);
	ConnectAllCells(MAX_MAP_SIZE, MAX_MAP_SIZE, sets);
	pass = 1;
	for (int r = 0; r < MAX_MAP_SIZE; r++)
	{
		for (int c = 0; c < MAX_MAP_SIZE; c++)
		{
			DisjointSet * resultA = SetFind(&PADGET(sets,r,c));
			DisjointSet * resultB = SetFind(&PADGET(sets,0,0));
			if (resultA != resultB)
			{
				pass = 0;
				printf("# Incorrect: (%d %d)[%ld] should be [%ld]\n", r, c, (long int)resultA, (long int)resultB);
			}
		}
	}
	TestOk(7, "Full map should join everything up - Bonus 1 Large", pass);

	ResetSets(sets);
	GoldRushInitSets(sets, MAX_MAP_SIZE, MAX_MAP_SIZE, map, 2);
	ConnectAllCells(MAX_MAP_SIZE, MAX_MAP_SIZE, sets);
	pass = 1;
	for (int r = 1; r < MAX_MAP_SIZE - 1; r++)
	{
		for (int c = 1; c < MAX_MAP_SIZE - 1; c++)
		{
			DisjointSet * resultA = SetFind(&PADGET(sets,r,c));
			DisjointSet * resultB = SetFind(&PADGET(sets,1,1));
			if (resultA != resultB)
			{
				pass = 0;
				printf("# Incorrect: (%d %d)[%ld] should be [%ld]\n", r, c, (long int)resultA, (long int)resultB);
			}
		}
	}
	TestOk(8, "Full map should join non-outer cells up - Bonus 2 Large", pass);

	int mapSpecial[MAX_MAP_SIZE][MAX_MAP_SIZE] =
	{
		//   0     1     2     3     4     5     6     7
		{    0,    0, GOLD,    0,    0,    0,    0,    0 }, // 0
		{    0,    0, GOLD,    0,    0,    0, GOLD,    0 }, // 1
		{    0, GOLD,    0, GOLD,    0,    0, GOLD,    0 }, // 2
		{    0, GOLD,    0,    0, GOLD,    0,    0, GOLD }, // 3
		{ GOLD,    0,    0,    0, GOLD, GOLD, GOLD,    0 }, // 4
		{ GOLD,    0, GOLD,    0, GOLD,    0,    0,    0 }, // 5
		{ GOLD,    0,    0,    0, GOLD,    0,    0,    0 }, // 6
		{    0, GOLD, GOLD, GOLD,    0,    0,    0,    0 }  // 7
	};
	ResetSets(sets);
	GoldRushInitSets(sets, 8, 8, mapSpecial, 1);
	ConnectAllCells(8, 8, sets);
	int info3[][5] =
	{
		{ 0, 2, 1, 6, 1 },
		{ 0, 2, 5, 0, 1 },
		{ 0, 2, 7, 2, 1 },
		{ 0, 2, 5, 2, 0 },
		{ -1 }
	};
	TestOk(9, "Special 1 situation - bonus 1", TestSetConnections(info3, sets));

	ResetMap(map);
	// (3x3 block)---(3x3 block)  (3x3 block)
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			map[r][c] = map[r][c+4] = map[r][c+8] = GOLD;
		}
	}
	map[1][3] = GOLD;
	ResetSets(sets);
	GoldRushInitSets(sets, 3, 11, map, 1);
	ConnectAllCells(3, 11, sets);
	pass = 1;
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			pass &= SetFind(&PADGET(sets,r,c)) == SetFind(&PADGET(sets,r,c+4));
			pass &= SetFind(&PADGET(sets,r,c)) != SetFind(&PADGET(sets,r,c+8));
			pass &= PADGET(sets,r,c).isGold;
			pass &= PADGET(sets,r,c+4).isGold;
			pass &= PADGET(sets,r,c+8).isGold;
			pass &= PADGET(sets,r,c).goldCount;
			pass &= PADGET(sets,r,c+4).goldCount;
			pass &= PADGET(sets,r,c+8).goldCount;
		}
		pass &= SetFind(&PADGET(sets,r,0)) == SetFind(&PADGET(sets,0,0));
		pass &= SetFind(&PADGET(sets,r,8)) == SetFind(&PADGET(sets,0,8));
	}
	TestOk(10, "Gold region with separate pure gold - Bonus 1", pass);

	ResetSets(sets);
	GoldRushInitSets(sets, 3, 11, map, 2);
	pass = 1;
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			int pure = r == 1 && c == 1;
			pass &= pure == PADGET(sets,r,c).goldCount;
			pass &= pure == PADGET(sets,r,c+4).goldCount;
			pass &= pure == PADGET(sets,r,c+8).goldCount;
		}
	}
	ConnectAllCells(3, 11, sets);
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			pass &= SetFind(&PADGET(sets,r,c)) == SetFind(&PADGET(sets,r,c+4));
			pass &= SetFind(&PADGET(sets,r,c)) != SetFind(&PADGET(sets,r,c+8));
			pass &= PADGET(sets,r,c).isGold;
			pass &= PADGET(sets,r,c+4).isGold;
			pass &= PADGET(sets,r,c+8).isGold;
		}
		pass &= SetFind(&PADGET(sets,r,0)) == SetFind(&PADGET(sets,0,0));
		pass &= SetFind(&PADGET(sets,r,8)) == SetFind(&PADGET(sets,0,8));
	}
	TestOk(11, "Gold region with separate pure gold - Bonus 2", pass);

	TestEnd();
}

void TestQuickSort()
{
	printf("\n# QuickSort\n");
	TestPlan(4);

	int pass;

	int in4a[4] = { 1, 2, 3, 4 };
	QuickSort(in4a, 4);
	pass = 1
		&& in4a[0] == 1
		&& in4a[1] == 2
		&& in4a[2] == 3
		&& in4a[3] == 4;
	TestOk(1, "Sorted array should stay sorted", pass);

	int in6[6] = { 0 };
	int out6[6] = { 0 };
	pass = 1;
	for (int i = 0; i < 1000000; i++)
	{
		//printf("# %d\n", i);
		int x = i;
		out6[0] = in6[0] = x % 10; x /= 10;
		out6[1] = in6[1] = x % 10; x /= 10;
		out6[2] = in6[2] = x % 10; x /= 10;
		out6[3] = in6[3] = x % 10; x /= 10;
		out6[4] = in6[4] = x % 10; x /= 10;
		out6[5] = in6[5] = x % 10; x /= 10;
		QuickSort(out6, 6);
		for (int j = 0; j < 5; j++)
		{
			if (out6[j] > out6[j+1])
			{
				pass = 0;
				printf("# Incorrect - [%d,%d,%d,%d,%d,%d] sorted became [%d,%d,%d,%d,%d,%d]\n", in6[0], in6[1], in6[2], in6[3], in6[4], in6[5], out6[0], out6[1], out6[2], out6[3], out6[4], out6[5]);
				break;
			}
		}
	}
	TestOk(2, "Brute force array of 6 integers", pass);

	int in5[5] = { 0 };
	int out5[5] = { 0 };
	pass = 1;
	for (int i = 0; i < 100000; i++)
	{
		//printf("# %d\n", i);
		int x = i;
		out5[0] = in5[0] = x % 10; x /= 10;
		out5[1] = in5[1] = x % 10; x /= 10;
		out5[2] = in5[2] = x % 10; x /= 10;
		out5[3] = in5[3] = x % 10; x /= 10;
		out5[4] = in5[4] = x % 10; x /= 10;
		QuickSort(out5, 5);
		for (int j = 0; j < 4; j++)
		{
			if (out5[j] > out5[j+1])
			{
				pass = 0;
				printf("# Incorrect - [%d,%d,%d,%d,%d] sorted became [%d,%d,%d,%d,%d]\n", in5[0], in5[1], in5[2], in5[3], in5[4], out5[0], out5[1], out5[2], out5[3], out5[4]);
				break;
			}
		}
	}
	TestOk(3, "Brute force array of 5 integers", pass);

	int in10[10] = { 1, 9, 4, 5, 6, 3, 8, 2, 4, 9 };
	QuickSort(in10, 10);
	pass = 1
		&& in10[0] == 1
		&& in10[1] == 2
		&& in10[2] == 3
		&& in10[3] == 4
		&& in10[4] == 4
		&& in10[5] == 5
		&& in10[6] == 6
		&& in10[7] == 8
		&& in10[8] == 9
		&& in10[9] == 9;
	TestOk(4, "Hard coded array of 10 integers", pass);

	TestEnd();
}

int CompareGoldResults(int a[MAX_ARRAY_SIZE], int b[MAX_ARRAY_SIZE])
{
	for (int i = 0; b[i - 1]; i++)
	{
		if (a[i] != b[i]) return 0;
	}
	return 1;
}

void TestGoldRush12(void)
{
	printf("\n# BONUS TASK. GOLD RUSH\n");
	TestPlan(15);

	int results[MAX_ARRAY_SIZE];

	int map[MAX_MAP_SIZE][MAX_MAP_SIZE] =
	{
	//   0 1 2 3 4 5 6 7 8 9 1011121314
		{1,2,2,0,0,0,0,0,0,0,0,0,0,0,0}, //  0
		{0,4,3,0,0,0,0,9,9,8,0,0,0,0,0}, //  1
		{0,2,0,3,3,0,0,9,9,0,0,0,0,0,0}, //  2
		{0,0,0,0,0,4,6,9,9,6,0,0,0,0,0}, //  3
		{0,0,0,0,0,0,9,0,8,0,0,6,0,0,0}, //  4
		{0,0,9,9,9,9,0,0,0,0,7,7,8,8,0}, //  5
		{0,0,9,9,9,9,0,0,0,0,0,7,0,0,0}, //  6
		{0,0,9,9,9,9,0,1,1,1,2,2,2,2,2}, //  7
		{0,0,0,9,9,0,0,0,0,0,0,0,0,3,0}, //  8
		{0,0,0,4,4,0,0,0,0,0,0,0,5,6,0}, //  9
		{0,0,0,0,9,9,9,0,0,9,0,0,0,5,0}, // 10
		{0,0,1,2,9,9,9,0,0,0,9,0,0,4,2}, // 11
		{0,0,0,0,9,9,9,0,0,0,9,9,9,0,0}, // 12
		{9,9,0,0,0,0,1,0,0,0,0,9,0,0,0}, // 13
		{9,0,0,0,0,0,2,2,0,0,0,0,0,0,0}  // 14
	};
	int out1[MAX_ARRAY_SIZE] = { 21, 9, 6, 3, 0 };
	GoldRush(results, 15, 15, map, 1);
	TestOk(1, "Project Sheet Example - bonus 1", CompareGoldResults(results, out1));

	int out2[MAX_ARRAY_SIZE] = { 2, 1, 0 };
	GoldRush(results, 15, 15, map, 2);
	TestOk(2, "Project Sheet Example - bonus 2", CompareGoldResults(results, out2));

	ResetMap(map);
	GoldRush(results, 15, 15, map, 1);
	TestOk(3, "Empty map - bonus 1", results[0] == 0);

	ResetMap(map);
	GoldRush(results, 15, 15, map, 2);
	TestOk(4, "Empty map - bonus 2", results[0] == 0);

	ResetMap(map);
	FillMap(MAX_MAP_SIZE, MAX_MAP_SIZE, map, GOLD);
	GoldRush(results, MAX_MAP_SIZE, MAX_MAP_SIZE, map, 1);
	TestOk(5, "Full map - bonus 1", results[0] == MAX_MAP_SIZE * MAX_MAP_SIZE && results[1] == 0);

	ResetMap(map);
	FillMap(MAX_MAP_SIZE, MAX_MAP_SIZE, map, GOLD);
	GoldRush(results, MAX_MAP_SIZE, MAX_MAP_SIZE, map, 2);
	TestOk(6, "Full map - bonus 2", results[0] == (MAX_MAP_SIZE - 2) * (MAX_MAP_SIZE - 2) && results[1] == 0);

	int mapSpecial[MAX_MAP_SIZE][MAX_MAP_SIZE] =
	{
		//   0     1     2     3     4     5     6     7
		{    0,    0, GOLD,    0,    0,    0,    0,    0 }, // 0
		{    0,    0, GOLD,    0,    0,    0, GOLD,    0 }, // 1
		{    0, GOLD,    0, GOLD,    0,    0, GOLD,    0 }, // 2
		{    0, GOLD,    0,    0, GOLD,    0,    0, GOLD }, // 3
		{ GOLD,    0,    0,    0, GOLD, GOLD, GOLD,    0 }, // 4
		{ GOLD,    0, GOLD,    0, GOLD,    0,    0,    0 }, // 5
		{ GOLD,    0,    0,    0, GOLD,    0,    0,    0 }, // 6
		{    0, GOLD, GOLD, GOLD,    0,    0,    0,    0 }  // 7
	};
	int outSpecial[MAX_ARRAY_SIZE] = { 20, 1, 0 };
	GoldRush(results, 8, 8, mapSpecial, 1);
	TestOk(7, "Special 1 situation - bonus 1", CompareGoldResults(results, outSpecial));

	int mapSmall[MAX_MAP_SIZE][MAX_MAP_SIZE] = { 0 };
	int pass = 1;
	for (int i = 0; i < 16; i++)
	{
		mapSmall[0][0] = GOLD * !!(i & (1 << 0));
		mapSmall[0][1] = GOLD * !!(i & (1 << 1));
		mapSmall[1][0] = GOLD * !!(i & (1 << 2));
		mapSmall[1][1] = GOLD * !!(i & (1 << 3));

		int goldCount = 0
			+ mapSmall[0][0]
			+ mapSmall[0][1]
			+ mapSmall[1][0]
			+ mapSmall[1][1];
		goldCount /= GOLD;

		GoldRush(results, 2, 2, mapSmall, 1);
		if (results[0] != goldCount || (goldCount && results[1]))
		{
			printf("# Incorrect - %d results = [%d, %d]\n", i, results[0], results[1]);
			pass = 0;
		}
	}
	TestOk(8, "Brute force small - bonus 1", pass);

	int map2[MAX_MAP_SIZE][MAX_MAP_SIZE] =
	{
		{ 9, 9, 9 },
		{ 9, 9, 9 },
		{ 9, 9, 9 }
	};
	GoldRush(results, 3, 3, map2, 1);
	TestOk(9, "Example 2 - bonus 1", results[0] == 9 && results[1] == 0);

	GoldRush(results, 3, 3, map2, 2);
	TestOk(10, "Example 2 - bonus 2", results[0] == 1 && results[1] == 0);

	int map3[MAX_MAP_SIZE][MAX_MAP_SIZE] =
	{
		{9, 9, 9},
		{9, 9, 9},
		{9, 9, 8}
	};
	GoldRush(results, 3, 3, map3, 1);
	TestOk(11, "Example 3 - bonus 1", results[0] == 8 && results[1] == 0);

	GoldRush(results, 3, 3, map3, 2);
	TestOk(12, "Example 3 - bonus 2", results[0] == 0);

	int map4[MAX_MAP_SIZE][MAX_MAP_SIZE] =
	{
		{ 9, 0, 9, 9 },
		{ 0, 0, 0, 9 },
		{ 9, 9, 0, 0 }
	};
	int out4[MAX_ARRAY_SIZE] = { 3, 2, 1, 0 };
	GoldRush(results, 3, 4, map4, 1);
	TestOk(13, "Odd number of results - Bonus 1", CompareGoldResults(results, out4));

	ResetMap(map);
	// (3x3 block)---(3x3 block)  (3x3 block)
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			map[r][c] = map[r][c+4] = map[r][c+8] = GOLD;
		}
	}
	map[1][3] = GOLD;
	int out5[MAX_ARRAY_SIZE] = { 19, 9, 0 };
	GoldRush(results, 3, 11, map, 1);
	TestOk(14, "Gold regions with separate pure gold - Bonus 1", CompareGoldResults(results, out5));
	int out6[MAX_ARRAY_SIZE] = { 2, 1, 0 };
	GoldRush(results, 3, 11, map, 2);
	TestOk(15, "Gold regions with separate pure gold - Bonus 2", CompareGoldResults(results, out6));

	TestEnd();
}

void TestGoldRush0(void)
{
	printf("\n# TASK 10. GOLD RUSH\n");
	TestPlan(7);

	int results[MAX_ARRAY_SIZE];

	int map[MAX_MAP_SIZE][MAX_MAP_SIZE] =
	{
	//   0 1 2 3 4 5 6 7 8 9 1011121314
		{1,2,2,0,0,0,0,0,0,0,0,0,0,0,0}, //  0
		{0,4,3,0,0,0,0,9,9,8,0,0,0,0,0}, //  1
		{0,2,0,3,3,0,0,9,9,0,0,0,0,0,0}, //  2
		{0,0,0,0,0,4,6,9,9,6,0,0,0,0,0}, //  3
		{0,0,0,0,0,0,9,0,8,0,0,6,0,0,0}, //  4
		{0,0,9,9,9,9,0,0,0,0,7,7,8,8,0}, //  5
		{0,0,9,9,9,9,0,0,0,0,0,7,0,0,0}, //  6
		{0,0,9,9,9,9,0,1,1,1,2,2,2,2,2}, //  7
		{0,0,0,9,9,0,0,0,0,0,0,0,0,3,0}, //  8
		{0,0,0,4,4,0,0,0,0,0,0,0,5,6,0}, //  9
		{0,0,0,0,9,9,9,0,0,9,0,0,0,5,0}, // 10
		{0,0,1,2,9,9,9,0,0,0,9,0,0,4,2}, // 11
		{0,0,0,0,9,9,9,0,0,0,9,9,9,0,0}, // 12
		{9,9,0,0,0,0,1,0,0,0,0,9,0,0,0}, // 13
		{9,0,0,0,0,0,2,2,0,0,0,0,0,0,0}  // 14
	};
	GoldRush(results, 15, 15, map, 0);
	TestOk(1, "Project Sheet Example", results[0] == 39 && results[1] == 3);

	ResetMap(map);
	GoldRush(results, 15, 15, map, 0);
	TestOk(2, "Empty map", results[0] == 0 && results[1] == 0);

	ResetMap(map);
	FillMap(MAX_MAP_SIZE, MAX_MAP_SIZE, map, GOLD);
	GoldRush(results, MAX_MAP_SIZE, MAX_MAP_SIZE, map, 0);
	TestOk(3, "Full map", results[0] == MAX_MAP_SIZE * MAX_MAP_SIZE && results[1] == (MAX_MAP_SIZE - 2) * (MAX_MAP_SIZE - 2));

	int mapSpecial[MAX_MAP_SIZE][MAX_MAP_SIZE] =
	{
		//   0     1     2     3     4     5     6     7
		{    0,    0, GOLD,    0,    0,    0,    0,    0 }, // 0
		{    0,    0, GOLD,    0,    0,    0, GOLD,    0 }, // 1
		{    0, GOLD,    0, GOLD,    0,    0, GOLD,    0 }, // 2
		{    0, GOLD,    0,    0, GOLD,    0,    0, GOLD }, // 3
		{ GOLD,    0,    0,    0, GOLD, GOLD, GOLD,    0 }, // 4
		{ GOLD,    0, GOLD,    0, GOLD,    0,    0,    0 }, // 5
		{ GOLD,    0,    0,    0, GOLD,    0,    0,    0 }, // 6
		{    0, GOLD, GOLD, GOLD,    0,    0,    0,    0 }  // 7
	};
	GoldRush(results, 8, 8, mapSpecial, 0);
	TestOk(4, "Special 1 situation", results[0] == 21 && results[1] == 0);

	int mapSmall[MAX_MAP_SIZE][MAX_MAP_SIZE] = { 0 };
	int pass = 1;
	for (int i = 0; i < 16; i++)
	{
		mapSmall[0][0] = GOLD * !!(i & (1 << 0));
		mapSmall[0][1] = GOLD * !!(i & (1 << 1));
		mapSmall[1][0] = GOLD * !!(i & (1 << 2));
		mapSmall[1][1] = GOLD * !!(i & (1 << 3));

		int goldCount = 0
			+ mapSmall[0][0]
			+ mapSmall[0][1]
			+ mapSmall[1][0]
			+ mapSmall[1][1];
		goldCount /= GOLD;

		GoldRush(results, 2, 2, mapSmall, 0);
		if (results[0] != goldCount || results[1])
		{
			printf("# Incorrect - %d results = [%d, %d]\n", i, results[0], results[1]);
			pass = 0;
		}
	}
	TestOk(5, "Brute force small", pass);

	int map2[MAX_MAP_SIZE][MAX_MAP_SIZE] =
	{
		{ 9, 9, 9 },
		{ 9, 9, 9 },
		{ 9, 9, 9 }
	};
	GoldRush(results, 3, 3, map2, 0);
	TestOk(6, "Example 2", results[0] == 9 && results[1] == 1);

	int map3[MAX_MAP_SIZE][MAX_MAP_SIZE] =
	{
		{9, 9, 9},
		{9, 9, 9},
		{9, 9, 8}
	};
	GoldRush(results, 3, 3, map3, 0);
	TestOk(7, "Example 3", results[0] == 8 && results[1] == 0);

	TestEnd();
}

void TestDivisorOfThree(void)
{
	printf("\n# TASK 1. DIVISOR OF THREE\n");
	TestPlan(9);

	TestEqualsInt(1, "Example 1 -      1288,     759,     1173", DivisorOfThree(     1288,     759,     1173),      23);
	TestEqualsInt(2, "Example 2 -       760,    1960,     2720", DivisorOfThree(      760,    1960,     2720),      40);
	TestEqualsInt(3, "Example 3 -       100,       0,  1000000", DivisorOfThree(      100,       0,  1000000),      -1);
	TestEqualsInt(4, "Moderate  -     20000,   40000,    20000", DivisorOfThree(    20000,   40000,    20000),   20000);
	TestEqualsInt(5, "Large 1   - 234788987, 1238634,  9173827", DivisorOfThree(234788987, 1238634,  9173827),       1);
	TestEqualsInt(6, "Large 2   -    433408, 1234197, 19747152", DivisorOfThree(   433408, 1234197, 19747152),    1693);
	TestEqualsInt(7, "Smallest  -         1,       1,        1", DivisorOfThree(        1,        1,       1),       1);
	TestEqualsInt(8, "Range     -         1, INT_MAX,  1000000", DivisorOfThree(        1, INT_MAX,  1000000),       1);
	TestEqualsInt(9, "MAX       -   INT_MAX, INT_MAX,  INT_MAX", DivisorOfThree(  INT_MAX, INT_MAX,  INT_MAX), INT_MAX);

	TestEnd();
}

void TestAverageSheep(void)
{
	printf("\n# TASK 2. AVERAGE SHEEP\n");
	TestPlan(5);

	int sheep2[MAX_ARRAY_SIZE] = {-1, 25, 12, 18, -1, 9999};
	TestEqualsDouble(1, "Example 1", AverageSheep(sheep2), 18.333333);

	int sheep3[MAX_ARRAY_SIZE] = {-1, 22, 9999, -1, 25, 12};
	TestEqualsDouble(2, "Example 2", AverageSheep(sheep3), 22.0);

	int sheep4[MAX_ARRAY_SIZE] = {-1, -1, 9999, -1, 25, 12};
	TestEqualsDouble(3, "Example 3", AverageSheep(sheep4), 0.0);

	int sheep5[MAX_ARRAY_SIZE] = { 0 };
	sheep5[3] = 20;
	sheep5[5] = 500;
	sheep5[999] = 9999;
	TestEqualsDouble(4, "Large", AverageSheep(sheep5), 0.52052052052052052);

	int sheep6[MAX_ARRAY_SIZE] = { 9999 };
	TestEqualsDouble(5, "9999 at start", AverageSheep(sheep6), 0.0);

	TestEnd();
}

void TestEmphasise(void)
{
	printf("\n# TASK 3. EMPHASISE\n");
	TestPlan(4);

	char wordsA[MAX_ARRAY_SIZE] = "this is a _good_ question!";
	Emphasise(wordsA);
	TestEqualsString(1, "Example 1", wordsA, "this is a GOOD question!");

	char wordsB[MAX_ARRAY_SIZE] = "It is _over 9000_!";
	Emphasise(wordsB);
	TestEqualsString(2, "Example 2", wordsB, "It is OVER 9000!");

	char wordsC[MAX_ARRAY_SIZE] = "_Nothing to see here_";
	Emphasise(wordsC);
	TestEqualsString(3, "Example 3", wordsC, "NOTHING TO SEE HERE");

	char wordsD[MAX_ARRAY_SIZE] = "__";
	Emphasise(wordsD);
	TestEqualsString(4, "Smallest: \"__\"", wordsD, "");

	TestEnd();
}

void TestPrimeFactors(void)
{
	printf("\n# TASK 4. PRIME FACTORS\n");
	TestPlan(10);

	int factorCount = 0;
	int factors[MAX_ARRAY_SIZE];
	int pass;

	factorCount = PrimeFactors(567, factors);
	pass = factorCount == 5
		&& factors[0] == 3
		&& factors[1] == 3
		&& factors[2] == 3
		&& factors[3] == 3
		&& factors[4] == 7;
	TestOk(1, "Example 1", pass);

	factorCount = PrimeFactors(5678901, factors);
	pass = factorCount == 4
		&& factors[0] == 3
		&& factors[1] == 3
		&& factors[2] == 17
		&& factors[3] == 37117;
	TestOk(2, "Example 2", pass);

	factorCount = PrimeFactors(13, factors);
	pass = factorCount == 1
		&& factors[0] == 13;
	TestOk(3, "Example 3", pass);

	factorCount = PrimeFactors(1 << 30, factors);
	pass = factorCount == 30;
	for (int i = 0; i < 30; i++) pass &= factors[i] == 2;
	TestOk(4, "Highest power of 2", pass);

	factorCount = PrimeFactors(2, factors);
	pass = factorCount == 1
		&& factors[0] == 2;
	TestOk(5, "Smallest number", pass);

	factorCount = PrimeFactors(3, factors);
	pass = factorCount == 1
		&& factors[0] == 3;
	TestOk(6, "Small prime - 3", pass);

	factorCount = PrimeFactors(7, factors);
	pass = factorCount == 1
		&& factors[0] == 7;
	TestOk(7, "Small prime - 7", pass);

	factorCount = PrimeFactors(999983, factors);
	pass = factorCount == 1
		&& factors[0] == 999983;
	TestOk(8, "Large computable prime - largest below 10^6", pass);

	factorCount = PrimeFactors(99999989, factors);
	pass = factorCount == 1
		&& factors[0] == 99999989;
	TestOk(9, "Large computable prime - largest below 10^8", pass);

	factorCount = PrimeFactors(479001600, factors);
	pass = factorCount == 19
		&& factors[0] == 2
		&& factors[1] == 2
		&& factors[2] == 2
		&& factors[3] == 2
		&& factors[4] == 2
		&& factors[5] == 2
		&& factors[6] == 2
		&& factors[7] == 2
		&& factors[8] == 2
		&& factors[9] == 2
		&& factors[10] == 3
		&& factors[11] == 3
		&& factors[12] == 3
		&& factors[13] == 3
		&& factors[14] == 3
		&& factors[15] == 5
		&& factors[16] == 5
		&& factors[17] == 7
		&& factors[18] == 11;
	TestOk(10, "Largest factorial - 12!", pass);

	TestEnd();
}

int CompareMaze(int a[10][10], int b[10][10])
{
	for (int r = 0; r < 10; r++)
	{
		for (int c = 0; c < 10; c++)
		{
			if (a[r][c] != b[r][c]) return 0;
		}
	}
	return 1;
}

void TestConnectTwo(void)
{
	printf("\n# TASK 5. CONNECT TWO\n");
	TestPlan(9);

	int in1[10][10] =
	{
		{1, 0, 2, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};
	int out1[10][10] =
	{
		{1, 3, 2, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};
	ConnectTwo(in1);
	TestOk(1, "Example 1", CompareMaze(in1, out1));

	int in2[10][10] =
	{
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};
	int out2[10][10] =
	{
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{3, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{3, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{2, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};
	ConnectTwo(in2);
	TestOk(2, "Example 2", CompareMaze(in2, out2));

	int in3[10][10] =
	{
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 2, 0, 0}
	};
	int out3[10][10] =
	{
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 3, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 3, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 3, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 3, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 3, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 3, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 3, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 3, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 2, 0, 0}
	};
	ConnectTwo(in3);
	TestOk(3, "Example 3", CompareMaze(in3, out3));

	int in4[10][10] =
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 2, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};
	int out4[10][10] =
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 3, 0},
		{0, 0, 0, 0, 0, 0, 0, 3, 0, 0},
		{0, 0, 0, 0, 0, 0, 3, 0, 0, 0},
		{0, 0, 2, 3, 3, 3, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};
	ConnectTwo(in4);
	TestOk(4, "Start top right", CompareMaze(in4, out4));

	int in5[10][10] =
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 2, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};
	int out5[10][10] =
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 3, 2, 0, 0, 0, 0},
		{0, 0, 0, 3, 0, 0, 0, 0, 0, 0},
		{0, 0, 3, 0, 0, 0, 0, 0, 0, 0},
		{0, 3, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};
	ConnectTwo(in5);
	TestOk(5, "Start bottom left", CompareMaze(in5, out5));

	int in6[10][10] =
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 2, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
	};
	int out6[10][10] =
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 2, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 3, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 3, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 3, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 3, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 3, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 3, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
	};
	ConnectTwo(in6);
	TestOk(6, "Start bottom right", CompareMaze(in6, out6));

	int in7[10][10] =
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 2, 0}
	};
	int out7[10][10] =
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 3, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 3, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 3, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 3, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 3, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 2, 0}
	};
	ConnectTwo(in7);
	TestOk(7, "Diagonal end at bottom", CompareMaze(in7, out7));

	int in8[10][10] =
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};
	int out8[10][10] =
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
		{0, 0, 0, 0, 0, 0, 0, 0, 3, 0},
		{0, 0, 0, 0, 0, 0, 0, 3, 0, 0},
		{0, 0, 0, 0, 0, 0, 3, 0, 0, 0},
		{0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};
	ConnectTwo(in8);
	TestOk(8, "Diagonal end at top right", CompareMaze(in8, out8));

	int in9[10][10] =
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 2, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};
	int out9[10][10] =
	{
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 2, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};
	ConnectTwo(in9);
	TestOk(9, "Neighbouring left", CompareMaze(in9, out9));

	TestEnd();
}

void TestDayTrader()
{
	printf("\n# TASK 6. THE WOLF OF WALL STREET\n");
	TestPlan(9);

	int bestRun, bestRunIndex;

	int pricesA[15] = { 59, 60, 55, 23, 42, 44, 48, 50, 43, 45, 43, 44, 47, 51, 52 };
	DayTrader(pricesA, 15, &bestRun, &bestRunIndex);
	TestOk(1, "Example 1", bestRun == 4 && bestRunIndex == 3);

	int pricesB[10] = { 1, 2, 3, 3, 3, 4, 3, 4, 5, 6 };
	DayTrader(pricesB, 10, &bestRun, &bestRunIndex);
	TestOk(2, "Example 2", bestRun == 3 && bestRunIndex == 6);

	int pricesC[10] = { 123, 120, 118, 119, 121, 126, 127, 130, 129, 132 };
	DayTrader(pricesC, 10, &bestRun, &bestRunIndex);
	TestOk(3, "Example 3", bestRun == 5 && bestRunIndex == 2);

	int pricesD[1] = { 0 };
	DayTrader(pricesD, 1, &bestRun, &bestRunIndex);
	TestOk(4, "Smallest", bestRun == 0 && bestRunIndex == 0);

	int pricesE[5] = { 4, 4, 4, 4, 4 };
	DayTrader(pricesE, 5, &bestRun, &bestRunIndex);
	TestOk(5, "All equal", bestRun == 0 && bestRunIndex == 0);

	int pricesF[5] = { 5, 4, 3, 2, 1 };
	DayTrader(pricesF, 5, &bestRun, &bestRunIndex);
	TestOk(6, "Decreasing", bestRun == 0 && bestRunIndex == 0);

	int pricesG[8] = { 1, 2, 3, 2, 8, 6, 7, 8 };
	DayTrader(pricesG, 8, &bestRun, &bestRunIndex);
	TestOk(7, "Two equal sequences - should fetch first occurance", bestRun == 2 && bestRunIndex == 0);

	int pricesH[MAX_ARRAY_SIZE] = { 0 };
	DayTrader(pricesH, MAX_ARRAY_SIZE, &bestRun, &bestRunIndex);
	TestOk(8, "MAX_ARRAY_SIZE empty", bestRun == 0 && bestRunIndex == 0);
	for (int i = 0; i < MAX_ARRAY_SIZE; i++) pricesH[i] = i;
	DayTrader(pricesH, MAX_ARRAY_SIZE, &bestRun, &bestRunIndex);
	TestOk(9, "MAX_ARRAY_SIZE sequence", bestRun == MAX_ARRAY_SIZE - 1 && bestRunIndex == 0);

	TestEnd();
}

int CompareCompressed(int a[MAX_ARRAY_SIZE], int b[MAX_ARRAY_SIZE])
{
	for (int i = 0; b[i - 1] != -1; i++)
	{
		if (a[i] != b[i]) return 0;
	}
	return 1;
}

void TestCompress(void)
{
	printf("\n# TASK 7. COMPRESSION\n");
	TestPlan(6);

	int output[MAX_ARRAY_SIZE];

	int inputB[MAX_ARRAY_SIZE] =  { 1, 1, 2, 2, -1 };
	int outputB[MAX_ARRAY_SIZE] = { 2, 1, 2, 2, -1 };
	Compress(inputB, output);
	TestOk(1, "Example 1", CompareCompressed(output, outputB));

	int inputC[MAX_ARRAY_SIZE] =  { 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, -1};
	int outputC[MAX_ARRAY_SIZE] = { 10, 7, -1 };
	Compress(inputC, output);
	TestOk(2, "Example 2", CompareCompressed(output, outputC));

	int inputD[MAX_ARRAY_SIZE] =  { 4, 7, 7, 7, -1 };
	int outputD[MAX_ARRAY_SIZE] = { 1, 4, 3, 7, -1 };
	Compress(inputD, output);
	TestOk(3, "Example 3", CompareCompressed(output, outputD));

	int inputE[MAX_ARRAY_SIZE] = { 1, -1 };
	int outputE[MAX_ARRAY_SIZE] = { 1, 1, -1 };
	Compress(inputE, output);
	TestOk(4, "Smallest input", CompareCompressed(output, outputE));

	int inputF[MAX_ARRAY_SIZE] = { 1, 1, 1 };
	inputF[MAX_ARRAY_SIZE - 1] = -1;
	int outputF[MAX_ARRAY_SIZE] = { 3, 1, MAX_ARRAY_SIZE - 4, 0, -1 };
	Compress(inputF, output);
	TestOk(5, "Largest input", CompareCompressed(output, outputF));

	int inputG[MAX_ARRAY_SIZE] = { 7, 7, 7, 7, 7, 3, 4, 4, 4, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1 };
	int outputG[MAX_ARRAY_SIZE] = { 5, 7, 1, 3, 3, 4, 1, 7, 12, 0, -1 };
	Compress(inputG, output);
	TestOk(6, "Example from project sheet", CompareCompressed(output, outputG));

	TestEnd();
}

void TestAddOne(void)
{
	printf("\n# TASK 8. ARBITRARY INCREMENTING\n");
	TestPlan(3);

	char output[MAX_ARRAY_SIZE];

	char inA[MAX_ARRAY_SIZE] =   "99999";
	char outA[MAX_ARRAY_SIZE] = "100000";
	AddOne(inA, output);
	TestEqualsString(1, "Example 1", output, outA);

	char inB[MAX_ARRAY_SIZE] =  "12399999999";
	char outB[MAX_ARRAY_SIZE] = "12400000000";
	AddOne(inB, output);
	TestEqualsString(2, "Example 2", output, outB);

	char inC[MAX_ARRAY_SIZE] =   "9";
	char outC[MAX_ARRAY_SIZE] = "10";
	AddOne(inC, output);
	TestEqualsString(3, "Example 3", output, outC);

	TestEnd();
}

void TestHistogram(void)
{
	printf("\n# TASK 9. HISTOGRAM\n");
	TestPlan(4);

	char out[MAX_ARRAY_SIZE];

	int in1[10] = {1, 0, 3, 1, 2, 4, 5, 6, 2, 2};
	char out1[MAX_ARRAY_SIZE] =
		"************\n"
		"*       X  *\n"
		"*      XX  *\n"
		"*     XXX  *\n"
		"*  X  XXX  *\n"
		"*  X XXXXXX*\n"
		"*X XXXXXXXX*\n"
		"************";
	Histogram(out, in1, 10);
	TestEqualsString(1, "Example 1", out, out1);

	int in2[3] = {1, 0, 1};
	char out2[MAX_ARRAY_SIZE] =
		"*****\n"
		"*X X*\n"
		"*****";
	Histogram(out, in2, 3);
	TestEqualsString(2, "Example 2", out, out2);

	int in3[3] = {0, 1, 0};
	char out3[MAX_ARRAY_SIZE] =
		"*****\n"
		"* X *\n"
		"*****";
	Histogram(out, in3, 3);
	TestEqualsString(3, "Example 3", out, out3);

	int in4[1] = { 100 };
	char out4[MAX_ARRAY_SIZE] = { 0 };
	out4[0] = out4[1] = out4[2] = '*';
	out4[3] = '\n';
	int i;
	for (i = 1; i <= 100; i++)
	{
		out4[4*i+0] = '*';
		out4[4*i+1] = 'X';
		out4[4*i+2] = '*';
		out4[4*i+3] = '\n';
	}
	out4[4*i+0] = out4[4*i+1] = out4[4*i+2] = '*';
	out4[4*i+3] = '\0';
	Histogram(out, in4, 1);
	TestEqualsString(4, "Single large number", out, out4);

	TestEnd();
}

int main(void)
{
	TestGcd();
	TestIsLowerAlphabetic();
	TestToUpperCase();
	TestMazeInitLocations();
	TestSignum();
	TestIntMax();
	TestIsPure();
	TestDisjointSet();
	TestConnectCell();
	TestQuickSort();

	TestDivisorOfThree();
	TestAverageSheep();
	TestEmphasise();
	TestPrimeFactors();
	TestConnectTwo();
	TestDayTrader();
	TestCompress();
	TestAddOne();
	TestHistogram();

	TestGoldRush0();
	TestGoldRush12();

	printf("\n");
	printf("# Final Summary:\n");
	printf("# ===============\n");
	printf("# >  Planned: %d\n", testTotalPlanned);
	printf("# >   Passed: %d\n", testTotalSuccess);
	printf("# >   Failed: %d\n", testTotalFailure);
}
