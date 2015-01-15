#include<stdio.h>
#include<stdlib.h>
#include<string.h>


char S[100001];
int P, Q, N;
int loopend[100000] = { 0 };
int ans[100000] = { 0 };
int out_loop = 0;
int up_bdy = 0;
int bottom_bdy;

void f_initial(int bottom, int up)
{
	int i, j;
	for (i = bottom; i <= up; i++)
	{
		long f = 0;
		int break_flag = 0;
		for (j = i; j < N; j++)
		{
			f = (f * 10 + (int)S[j] - 48) % P;
			if (f == 0)
			{
				loopend[i] = j;
				break_flag = 1;
				break;
			}
		}
		if (!break_flag)
			loopend[i] = -(up);
	}
}

void inquire(void *pArg)
{
	int b = *((int *)pArg);
	int e = *((int *)pArg + 1);
	int ans_index = *((int *)pArg + 2);
	int i, j;
	int cnt_final = 0;
	int loopfinal[100000] = { 0 };
	for (i = e - 1; i >= b - 1; i--)
	{
		long f = 0;
		if ((loopend[i] > 0) && (loopend[i] <= e - 1))
		{
			loopfinal[i] = loopfinal[loopend[i] + 1] + 1;
			cnt_final = loopfinal[i] + cnt_final;
			continue;
		}
		else if (loopend[i] <= -(e - 1))
		{
			continue;
		}
		else
		{
			long f = 0;
			for (j = i; j <= e - 1; j++)
			{
				f = (f * 10 + (int)S[j] - 48) % P;
				if (f == 0)
				{
					loopend[i] = j;
					loopfinal[i] = loopfinal[j + 1] + 1;
					break;
				}
			}
			if (f != 0)
				loopend[i] = -(e - 1);
			cnt_final = loopfinal[i] + cnt_final;
		}
	}
	printf("%d\n",cnt_final);
	free(pArg);
}



int main(void)
{
	
	scanf("%d%d", &P, &Q);
	scanf("%s", S);
	N = strlen(S);
	bottom_bdy = N;
	int i;
	
	for (i = 0; i < Q; i++)
	{
		int *args = malloc(4 * sizeof(int));
		scanf("%d%d", args, args + 1);
		args[2] = i;
		inquire(args);
	}
	
	//system("pause");
	return 0;
}