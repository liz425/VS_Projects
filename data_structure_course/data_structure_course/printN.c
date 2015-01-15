#include<stdio.h>

void printN(int N)
{
	if (N)
	{
		printN(N - 1);
		printf("%d\n", N);
	}
	return;
}
int main(void)
{
	printN(1000);
	return 0;
}