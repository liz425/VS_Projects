#include<stdio.h>
#include<stdlib.h>

void Bubble_Sort(int A[], int N)
{
	int flag, temp;
	int P, i;
	for (P = N - 1; P >= 0; P--){
		flag = 0;
		for (i = 0; i<P; i++) { /*一趟冒泡*/
			if (A[i] > A[i + 1]) {
				temp = A[i];
				A[i] = A[i + 1];
				A[i + 1] = temp;
				flag = 1; /*标识发生了交换*/
			}
		}
		if (flag == 0) break; /*全程无交换*/
	}
}

/* L = 左边起始位置, R = 右边起始位置, RightEnd = 右边终点位置 */
void Merge(int A[], int TmpA[], int L, int R, int RightEnd)
{
	int LeftEnd = R - 1;		/* 左边终点位置。假设左右两列挨着 */
	int Tmp = L;				/* 存放结果的数组的初始位置 */
	int NumElements = RightEnd - L + 1;
	int i;
	while (L <= LeftEnd && R <= RightEnd) {  /*左右子序列都不为空*/
		if (A[L] <= A[R]) 
			TmpA[Tmp++] = A[L++];
		else 
			TmpA[Tmp++] = A[R++];
	}
	while (L <= LeftEnd)		 /* 直接复制左边剩下的 */
		TmpA[Tmp++] = A[L++];
	while (R <= RightEnd)		/*直接复制右边剩下的 */
		TmpA[Tmp++] = A[R++];
	for (i = 0; i < NumElements; i++, RightEnd--)  /*导回数据，注意L已经被修改，不能使用*/
		A[RightEnd] = TmpA[RightEnd];
}

void MSort(int A[], int TmpA[],
	int L, int RightEnd)
{
	int Center;
	if (L < RightEnd) {
		Center = (L + RightEnd) / 2;
		MSort(A, TmpA, L, Center);
		MSort(A, TmpA, Center + 1, RightEnd);
		Merge(A, TmpA, L, Center + 1, RightEnd);
	}
}

void Merge_Sort(int A[], int N)
{
	int *TmpA;
	TmpA = malloc(N * sizeof(int));
	if (TmpA != NULL) {
		MSort(A, TmpA, 0, N - 1);
		free(TmpA);
	}
}

int main(void)
{
	int N, i;
	scanf("%d", &N);
	int *A = calloc(N, sizeof(int));
	for (i = 0; i < N; i++)
	{
		scanf("%d", &A[i]);
	}
	Merge_Sort(A, N);
	for (i = 0; i < N - 1; i++)
	{
		printf("%d ", A[i]);
	}
	printf("%d", A[i]);
	//system("pause");
	return 0;
}