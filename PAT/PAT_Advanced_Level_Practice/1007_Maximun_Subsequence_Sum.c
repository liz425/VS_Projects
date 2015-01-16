#include <stdio.h>
#include <stdlib.h>

int MaxSubseqSum(int A[], int N)
{
	//MaxSum初始化为-1；如果所有元素都为负数，MaxSum 不更新，输出头尾
	long MaxSum = -1;		
	long ThisSum = 0;
	int i;
	int first_index = 0;
	int current_first = 0;
	int last_index = N - 1;
	for (i = 0; i < N; i++)
	{
		ThisSum += A[i];
		if (ThisSum > MaxSum)	//子列和更新
		{
			MaxSum = ThisSum;
			last_index = i;
			first_index = current_first;
		}
		else if (ThisSum < 0)
		{
			ThisSum = 0;
			current_first = i + 1;
		}
	}
	if(MaxSum == -1)
	{
		MaxSum = 0;
		first_index = 0;
		last_index = N - 1;
	}
	printf("%d %d %d",MaxSum,A[first_index],A[last_index]);
	return 0;
}

int main(void)
{
	int K, i;
	scanf("%d", &K);
	int *A = calloc(K, sizeof(int));
	for (i = 0; i < K; i++)
	{
		scanf("%d", &A[i]);
	}
	MaxSubseqSum(A, K);
	//system("pause");
	return 0;
}

