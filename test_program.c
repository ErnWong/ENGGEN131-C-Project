#include "project.h"
#include "helpers.h"

int main()
{
}

int TestOk(int testNumber, char * message, int condition)
{
	if (condition) printf("ok %d", testNumber);
	else printf("not ok %d", testNumber);
	printf(" - %s\n", message);
	return condition;
}

int TestEqualsInt(int testNumber, char * message, int actual, int desired)
{
	int condition = actual == desired;
	if (condition) printf("ok %d - %s\n", testNumber, message);
	else 
	{
		printf("not ok %d - %s\n", testNumber, message);
		printf("# expcted %d, but got %d\n", desired, actual);
	}
	return condition;
}

void TestGcd()
{
	TestEqualsInt(1, "Gcd(1, 1) - Edge Case", Gcd(1, 1), 1);
	TestEqualsInt(2, "Gcd(1, 2)", Gcd(1, 1), 1);
}
