#include<stdio.h>
#include<stdlib.h>

int main(void)
{
	int n[100] = { 0 };
	char c;
	int sum = 0;
	int ls[10];
	int i = 0, k = 1;
	while (1)
	{
		c = getchar();
		if (c == ' ' || c == '\n')
			break;
		sum += ((int)c - 48);
	}
	while (sum > 0)
	{
		ls[k] = sum % 10;
		sum = sum / 10;
		k++;
	}
	for (i = k - 1; i > 0; i--)
	{
		switch (ls[i])
		{
		case 0:printf("ling"); break;
		case 1:printf("yi");   break;
		case 2:printf("er");   break;
		case 3:printf("san");  break;
		case 4:printf("si");   break;
		case 5:printf("wu");   break;
		case 6:printf("liu");  break;
		case 7:printf("qi");   break;
		case 8:printf("ba");   break;
		case 9:printf("jiu");  break;
		default:printf("ling");
			break;
		}
		if (i > 1)
			printf(" ");
	}
	system("pause");
	return 0;
}