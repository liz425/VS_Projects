#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int main(void)
{
	int i = 0;
	int n = 0;
	scanf("%d",&n);
	while (n > 1)
	{
		if (n % 2 == 0)
			n = n / 2;
		else
			n = (3 * n + 1) / 2;
		i++;
	}
	printf("%d",i);
	return 0;
}