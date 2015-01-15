#include<stdio.h>
#include<stdlib.h>

int main(void)
{
	char ch;
	do{
		int n, m;
		scanf("%d%d", &n, &m);
		scanf("%c", &ch);
		int* matrix[50][50];
		int i, j;
		int cnt = 1;
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < m; j++)
			{
				scanf("%c", &ch);
				matrix[i][j] = malloc(4);
				//initial, scanning in 
				if (ch == '1')
				{
					*matrix[i][j] = -1;
				}
				else if (ch == '0')
				{
					*matrix[i][j] = 0;
				}
				else
					printf("Error_0");
				//¹¹Ôì
				if (*matrix[i][j] != 0)
				{
					if (j == 0)
					{
						*matrix[i][j] = cnt++;
						if ((i != 0) && (*matrix[i - 1][j] != 0))
							matrix[i][j] = matrix[i - 1][j];
					}
					else if(*matrix[i][j - 1] != 0)
					{
						matrix[i][j] = matrix[i][j - 1];
						if ((i != 0) && (*matrix[i - 1][j] != 0))
							*matrix[i - 1][j] = *matrix[i][j];
					}
					else
					{
						if ((i != 0) && (*matrix[i - 1][j] != 0))
							matrix[i][j] = matrix[i - 1][j];
						else
							*matrix[i][j] = cnt++;
					}
				}

			}
			scanf("%c", &ch);
		}

		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				if (*matrix[i][j] >= 0)
					printf("%d  ", *matrix[i][j]);
				else
					printf("%d ", *matrix[i][j]);
			}
			printf("\n");
		}
	} while (ch != '$');

	

 	system("pause");
	return 0;
}