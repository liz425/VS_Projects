#include<stdio.h>
#include<stdlib.h>

int *unsorted;
int *halfsorted;

void Insertion_Sort(int A[], int N)		
{
	int P, Tmp, i;
	for (P = 1; P<N; P++) {
		Tmp = A[P]; /* 摸下一张牌*/
		for (i = P; i>0 && A[i - 1]>Tmp; i--)
			A[i] = A[i - 1]; /* 移出空位*/
		A[i] = Tmp; /* 新牌落位*/
	}
}

/* L = 左边起始位置, R = 右边起始位置, RightEnd = 右边终点位置*/
void Merge(int A[], int TmpA[], int L, int R, int RightEnd)
{
	int LeftEnd = R - 1; /* 左边终点位置。假设左右两列挨着*/
	int Tmp = L; /* 存放结果的数组的初始位置*/
	int NumElements = RightEnd - L + 1;
	while (L <= LeftEnd && R <= RightEnd) {
		if (A[L] <= A[R]) TmpA[Tmp++] = A[L++];
		else TmpA[Tmp++] = A[R++];
	}
	while (L <= LeftEnd) /* 直接复制左边剩下的*/
		TmpA[Tmp++] = A[L++];
	while (R <= RightEnd) /*直接复制右边剩下的*/
		TmpA[Tmp++] = A[R++];
	int i = 0;
	for (i = 0; i < NumElements; i++, RightEnd--)
		A[RightEnd] = TmpA[RightEnd];
}


void Merge_pass(int A[], int TmpA[], int N, int length) /* length = 当前有序子列的长度*/
{
	int i, j;
	for (i = 0; i <= N - 2*length; i += 2 * length)
		Merge(A, TmpA, i, i + length, i + 2 * length - 1);
	if (i + length < N) /* 归并最后2个子列*/
		Merge(A, TmpA, i, i + length, N - 1);
	else /* 最后只剩1个子列*/
	for (j = i; j < N; j++) TmpA[j] = A[j];
}

void Merge_Sort(int A[], int N)
{
	int length = 1; /* 初始化子序列长度*/
	int *TmpA;
	int i;
	int flag = 0;
	TmpA = malloc(N * sizeof(int));
	if (TmpA != NULL) {
		while ((length < N)&&(flag <= 1)) {
			Merge_pass(A, TmpA, N, length);
			length *= 2;
			flag = flag * 2;
			for (i = 0; i < N; i++){
				if (A[i] != halfsorted[i])
					break;
			}
			if (i == N)
			{
				flag++;
			}
		}
		free(TmpA);
	}
}

int main(void)
{
	int N, i;
	scanf("%d", &N);
	unsorted = calloc(N, sizeof(int));
	halfsorted = calloc(N, sizeof(int));
	for (i = 0; i < N; i++)		/*Read in unsorted*/
	{
		scanf("%d", &unsorted[i]);
	}
	for (i = 0; i < N; i++)		/*Read in halfsorted*/
	{
		scanf("%d", &halfsorted[i]);
	}
	
	int k = 0;								/*use k to indicated sorted subarray*/
	while (halfsorted[k] <= halfsorted[k + 1])	/*Check if using insertion_sort*/
	{
		k++;									/*When quit, (i+1) is the length of first sorted subarray*/
		if (k == N - 1)
			break;
	}
	int flag = 0;					/*flag = 0 means using Insertion_sort*/
	for (i = k + 1; i < N; i++)
	{
		if (halfsorted[i] != unsorted[i])
		{
			flag = 1;
			break;
		}
	}

	if (flag)		/*using merge_sort*/
	{
		printf("Merge Sort\n");
		Merge_Sort(unsorted, N);
	}
	else			/*using insertion_sort*/
	{
		printf("Insertion Sort\n");
		Insertion_Sort(unsorted, k + 2);	/*only insertion (k+2) elements*/
	}

	for (i = 0; i < N - 1; i++)
	{
		printf("%d ", unsorted[i]);
	}
	printf("%d", unsorted[i]);
	//system("pause");
	return 0;
}