#include<stdio.h>
#include <stdlib.h>

int MaxSubseqSum(int A[], int N);

int main(void)
{
	int K, i;
	int A[100000] = {0};
	scanf("%d", &K);
	for (i = 1; i <= K; i++)
	{
		scanf("%d", &A[i]);
	}
	MaxSubseqSum(A, K);
	return 0;
}

int MaxSubseqSum(int A[], int N)
{
	long MaxSum = 0;
	long ThisSum = 0;
	int i;
	int first_index = 1;
	int current_first = 1;
	int last_index = N;
	for (i = 1; i <= N; i++)
	{
		ThisSum += A[i];
		if (ThisSum > MaxSum)
		{
			MaxSum = ThisSum;
			last_index = i;
			first_index = current_first;
		}
		else if (ThisSum < 0)
		{
			ThisSum = 0;
			current_first = i%N + 1;
		}
		else if (ThisSum == 0 && MaxSum == 0)
		{
			last_index = i;
			first_index = i;
			current_first = i;
		}
	}
	printf("%d %d %d",MaxSum,A[first_index],A[last_index]);
	system("pause");
	return 0;
}