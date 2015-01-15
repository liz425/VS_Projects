#include<stdio.h>
#include<stdlib.h>

void Bubble_Sort(int A[], int N)
{
	int flag, temp;
	int P, i;
	for (P = N - 1; P >= 0; P--){
		flag = 0;
		for (i = 0; i<P; i++) { /*һ��ð��*/
			if (A[i] > A[i + 1]) {
				temp = A[i];
				A[i] = A[i + 1];
				A[i + 1] = temp;
				flag = 1; /*��ʶ�����˽���*/
			}
		}
		if (flag == 0) break; /*ȫ���޽���*/
	}
}

/* L = �����ʼλ��, R = �ұ���ʼλ��, RightEnd = �ұ��յ�λ�� */
void Merge(int A[], int TmpA[], int L, int R, int RightEnd)
{
	int LeftEnd = R - 1;		/* ����յ�λ�á������������а��� */
	int Tmp = L;				/* ��Ž��������ĳ�ʼλ�� */
	int NumElements = RightEnd - L + 1;
	int i;
	while (L <= LeftEnd && R <= RightEnd) {  /*���������ж���Ϊ��*/
		if (A[L] <= A[R]) 
			TmpA[Tmp++] = A[L++];
		else 
			TmpA[Tmp++] = A[R++];
	}
	while (L <= LeftEnd)		 /* ֱ�Ӹ������ʣ�µ� */
		TmpA[Tmp++] = A[L++];
	while (R <= RightEnd)		/*ֱ�Ӹ����ұ�ʣ�µ� */
		TmpA[Tmp++] = A[R++];
	for (i = 0; i < NumElements; i++, RightEnd--)  /*�������ݣ�ע��L�Ѿ����޸ģ�����ʹ��*/
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