#include<stdio.h>
#include<stdlib.h>

//PAT Adcanced Level 1001: A + B Format
int main(void)
{
	int a, b;
	scanf("%d%d", &a, &b);
	int sum = a + b;
	if (sum == 0)		/*0直接输出0*/
	{
		printf("0");
	}
	else
	{
		if (sum < 0)	/*负数先输出负号*/
		{
			printf("-");
			sum = -sum;
		}
		int ans[10] = { 0 };
		int n = 0;
		while (sum > 0)
		{
			ans[n++] = sum % 10;
			sum = sum / 10;
		}
		while (--n >= 0)
		{
			printf("%d", ans[n]);
			if ((n % 3 == 0) && (n > 0))   /*每隔三位输出逗号*/
				printf(",");
		}
	}
	
	//system("pause");
	return 0;
}