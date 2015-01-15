#include <stdio.h>
#include <stdlib.h>



int main(void)
{
	int n;
	int i = 0;
	int j = 0;
	int k = 0;
	scanf("%d", &n);
	int a[10][2] = { 0 };
	int b[10] = { 0 };
	while (i < n)
	{	
		char *c=malloc(1);
		for (j = 0; j < 2; j++)
		{
			scanf("%s", c);
			if (*c == '-')
				a[i][j] = 99;
			else
			{
				k = *c - 48;
				b[k] = 1;
				a[i][j] = k;

			}
		}
		i++;
	}

	for (k = 0; k < n; k++)
	{
		if (b[k] == 0)
		{
			b[0] = k;
			break;
		}
	}

	k = 1;
	int flag = 0;
	for (i = 0; i < n; i++)
	{
		if ((a[b[i]][0] != 99))
			b[k++] = a[b[i]][0];
		if ((a[b[i]][1] != 99))
			b[k++] = a[b[i]][1];
		if ((a[b[i]][0] == 99) && (a[b[i]][1] == 99))
		{
			if (flag == 0)
			{
				printf("%d", b[i]);
				flag = 1;
			}
			else
				printf(" %d", b[i]);
		}
			
	}


	//system("pause");
	return 0;
}

