#include<stdio.h>
#include<stdlib.h>

//PAT Adcanced Level 1005: Spell It Right
int main(void)
{
	char S[102];
	scanf("%s", S);		//字符串形式存储 N
	int i = 0;
	int sum = 0;
	while (S[i] != '\0')
	{
		sum += (int)S[i] - 48;
		i++;
	}
	if (sum == 0)
	{
		printf("zero");
		return 0;
	}
	int k = 0;
	int digits[3];		//99*9 < 999, sum 最大为三位数
	while (sum != 0)	
	{
		digits[k++] = sum % 10;
		sum /= 10;
	}
	
	for (i = k - 1; i >= 0; i--)
	{
		switch (digits[i])
		{
		case 0:
			printf("zero");
			break;
		case 1:
			printf("one");
			break;
		case 2:
			printf("two");
			break;
		case 3:
			printf("three");
			break;
		case 4:
			printf("four");
			break;
		case 5:
			printf("five");
			break;
		case 6:
			printf("six");
			break;
		case 7:
			printf("seven");
			break;
		case 8:
			printf("eight");
			break;
		case 9:
			printf("nine");
			break;
		default:
			break;
		}
		if (i != 0)
			printf(" ");
	}
	
	
	//system("pause");
	return 0;
}