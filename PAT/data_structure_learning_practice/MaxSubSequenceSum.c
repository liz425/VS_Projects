#include<stdio.h>

int MaxSubseqSum(int A[], int N);

int main(void)
{
	int K,i;
	int MaxSum;
	int A[100000];
	scanf("%d", &K);
	for (i = 1; i <= K; i++)
	{
		scanf("%d", &A[i]);
	}
	MaxSum = MaxSubseqSum(A, K);
	printf("%d", MaxSum);
}

int MaxSubseqSum(int A[], int N)
{
	int MaxSum = 0;
	int ThisSum = 0;
	int i;
	for (i = 1; i <= N; i++)
	{
		ThisSum += A[i];
		if (ThisSum > MaxSum)
			MaxSum = ThisSum;
		else if (ThisSum < 0)
			ThisSum = 0;
	}
	return MaxSum;
}