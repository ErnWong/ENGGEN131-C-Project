#include "project.h"
#include "helpers.h"
// #include "project.c"

#include <limits.h>

int testPlan = 0;
int testSuccess = 0;
int testTotalPlanned = 0;
int testTotalSuccess = 0;

void TestPlan(int count)
{
	testPlan = count;
	testSuccess = 0;
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
}

int TestOk(int testNumber, char * message, int condition)
{
	if (condition) printf("ok %d", testNumber);
	else printf("not ok %d", testNumber);
	printf(" - %s\n", message);
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
	TestPlan(4);

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

		int result = IsPure(2, 2, map);
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

		int result = IsPure(2, 2, map);
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
	TestEqualsInt(3, "The only truthy input", IsPure(2, 2, pureMap), 1);

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

		int result = IsPure(2, 2, map);
		if (result)
		{
			printf("# Incorrect - Subtest mask: %d\n", i);
			pass = 0;
		}
	}
	TestOk(4, "Should not return true for non-gold neighbours", pass);

	TestEnd();
}

void TestGoldRush0(void)
{
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
	TestPlan(5);

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
	printf("\n# Before Init: sets @ %ld\n\n", (long int)sets);
	VisualiseSets(16,16,sets);
	GoldRushInitSets(sets, 15, 15, map, 1);
	printf("\n# After Init:\n\n");
	VisualiseSets(16,16,sets);
	ConnectAllCells(15, 15, sets);
	printf("\n# After ConnectAllCells:\n\n");
	VisualiseSets(16,16,sets);

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
				//&& PADGET(sets,r,c).seen == 0;
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
				//&& PADGET(sets,r,c).seen == 0;
		}
	}
	TestOk(3, "Empty map should leave sets all zeros\n", pass);

	int mapFull[MAX_MAP_SIZE][MAX_MAP_SIZE] =
	{
		{ GOLD, GOLD, GOLD, GOLD, GOLD, GOLD, GOLD, GOLD },
		{ GOLD, GOLD, GOLD, GOLD, GOLD, GOLD, GOLD, GOLD },
		{ GOLD, GOLD, GOLD, GOLD, GOLD, GOLD, GOLD, GOLD },
		{ GOLD, GOLD, GOLD, GOLD, GOLD, GOLD, GOLD, GOLD },
		{ GOLD, GOLD, GOLD, GOLD, GOLD, GOLD, GOLD, GOLD },
		{ GOLD, GOLD, GOLD, GOLD, GOLD, GOLD, GOLD, GOLD },
		{ GOLD, GOLD, GOLD, GOLD, GOLD, GOLD, GOLD, GOLD },
		{ GOLD, GOLD, GOLD, GOLD, GOLD, GOLD, GOLD, GOLD }
	};
	ResetSets(sets);
	GoldRushInitSets(sets, 8, 8, mapFull, 1);
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
	TestOk(4, "Full map should join everything up - Bonus 1\n", pass);
	ResetSets(sets);
	GoldRushInitSets(sets, 8, 8, mapFull, 2);
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
	TestOk(5, "Full map should join non-outer cells up - Bonus 2\n", pass);

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
	TestGoldRush0();
	TestDisjointSet();
	TestConnectCell();

	printf("\n# Final Summary: %d of %d tests passed\n", testTotalSuccess, testTotalPlanned);
}
