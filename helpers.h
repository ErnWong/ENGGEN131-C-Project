#define SHEEP_TERMINATOR 9999
#define SHEEP_IGNORE -1
#define MAZE_SIZE 10
#define COMPRESSION_TERMINATOR -1
#define GOLD 9

#define PADDED_SIZE (MAX_MAP_SIZE + 2)
#define PADGET(sets, r, c) ((sets)[(r)+1][(c)+1])

int Gcd(int x, int y);
int IsLowerAlphabetic(char c);
char ToUpperCase(char c);
void MazeInitLocations(int maze[MAZE_SIZE][MAZE_SIZE], int * r1, int * c1,
		int * r2, int * c2);
int Signum(int x);
int IntMax(int * values, int size);
char * CharRepeat(char * string, char c, int count);
int IsGold(int r, int c, int map[MAX_MAP_SIZE][MAX_MAP_SIZE]);
int IsPure(int r, int c, int rows, int cols, int map[MAX_MAP_SIZE][MAX_MAP_SIZE]);
void GoldRush0(int * results, int rows, int cols,
		int map[MAX_MAP_SIZE][MAX_MAP_SIZE]);

typedef struct DisjointSet DisjointSet;

struct DisjointSet
{
	DisjointSet * parent;
	int rank;
	int goldCount;
	int isGold;
	//int seen;
};

void SetInit(DisjointSet * set);
void SetSwap(DisjointSet ** setA, DisjointSet ** setB);
DisjointSet * SetFind(DisjointSet * set);
void SetMerge(DisjointSet * setA, DisjointSet * setB);

void ConnectCell(int r, int c, DisjointSet sets[PADDED_SIZE][PADDED_SIZE]);
void ConnectAllCells(int rows, int cols,
		DisjointSet sets[PADDED_SIZE][PADDED_SIZE]);
void IntSwap(int * a, int * b);
void QuickSort(int * array, int size);
void GoldRushInitSets(DisjointSet sets[PADDED_SIZE][PADDED_SIZE],
		int rows, int cols, int map[MAX_MAP_SIZE][MAX_MAP_SIZE], int bonus);
int ExtractRegions(int * results, DisjointSet sets[PADDED_SIZE][PADDED_SIZE],
		int rows, int cols);
void GoldRush12(int * results, int rows, int cols,
		int map[MAX_MAP_SIZE][MAX_MAP_SIZE], int bonus);
