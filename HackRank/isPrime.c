#include<stdio.h>
#include<stdlib.h>

#define PL 100000

int main(void)
{
	int loop = 50000;
	int a = -1;
	while (loop-- > 0)
	{
		int isPrime[PL] = { 0 };
		int i, k;
		for (i = 2; i < PL; i++)
		{
			if (!isPrime[i])
			{
				for (k = 2; i*k < PL; k++)
				{
					isPrime[i*k] = 1;
				}
			}
		}
		for (i = 2; i < PL; i++)
		{
			if (!isPrime[i])
			{
				//printf("%d\n", i);
				a = -a;
			}
		}
	}
	printf("Done\n");
	system("pause");
	return 0;
}