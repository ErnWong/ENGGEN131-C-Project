int Gcd(int x, int y);
int IsLowerAlphabetic(char c);
char ToUpperCase(char c);
int IsPrimeNaive(int p);
int IsPrimeSeive(int p, int * isComposite);
int IsPrime(int p, int * isComposite);
int Signum(int x);
int IsGold(int r, int c, int map[MAX_MAP_SIZE][MAX_MAP_SIZE]);
int IsPure(int r, int c, int map[MAX_MAP_SIZE][MAX_MAP_SIZE]);
void GoldRush0(int * results, int rows, int cols,
    int map[MAX_MAP_SIZE][MAX_MAP_SIZE]);

typedef struct DisjointSet DisjointSet;

void SetInit(DisjointSet * set);
void SetSwap(DisjointSet ** setA, DisjointSet ** setB);
DisjointSet * SetFind(DisjointSet * set);
void SetMerge(DisjointSet * setA, DisjointSet * setB);

void ConnectCell(int r, int c, DisjointSet sets[MAX_MAP_SIZE][MAX_MAP_SIZE]);
void IntSwap(int * a, int * b);
void QuickSort(int * array, int size);
void GoldRush12(int * results, int rows, int cols,
    int map[MAX_MAP_SIZE][MAX_MAP_SIZE], int bonus);
