#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct HeapStruct *MinHeap;
#define MinData -1;

typedef struct TreeNode{
	int Weight;
	struct TreeNode *Left, *Right;
	int Length;         //current node path length
}*HuffmanTree;


struct HeapStruct{
	HuffmanTree *Elements;
	int Size;
	int Capacity;
};

MinHeap Create(int MaxSize)  //��������ΪMaxSize����С��
{				
	MinHeap H = (MinHeap)malloc(sizeof(struct HeapStruct));
	H->Elements = calloc((MaxSize + 1),sizeof(HuffmanTree));
	H->Size = 0;
	H->Capacity = MaxSize;
	H->Elements[0] = malloc(sizeof(struct TreeNode)); /*��ʼ���ڱ��½��*/
	H->Elements[0]->Weight = MinData;  //����Sentinel
	H->Elements[0]->Left = H->Elements[0]->Right = NULL;
	H->Elements[0]->Length = 0;
	return H;
}

MinHeap Insert(MinHeap H, HuffmanTree item)
{		/* ��Ԫ��item ������С��H������H->Elements[0]�Ѿ�����Ϊ�ڱ� */
	int i;
	if (H->Size >= H->Capacity) {
		printf("��С������");
		return H;
	}
	i = ++(H->Size); /* iָ��������е����һ��Ԫ�ص�λ�� */
	for (; H->Elements[i/2]->Weight > item->Weight; i /= 2)
		H->Elements[i] = H->Elements[i/2]; /* ���Ϲ��˽�� */
	H->Elements[i] = item; /* ��item ���� */
	return H;
}

HuffmanTree DeleteMin(MinHeap H)
{			/* ����С��H��ȡ����ֵΪ��С��Ԫ�أ���ɾ��һ����� */
	int Parent, Child;
	HuffmanTree MinItem, temp;
	if (H->Size <= 0) {
		printf("��С����Ϊ��");
		return NULL;
	}
	MinItem = H->Elements[1];	/* ȡ������㣬��Сֵ */
	/* ����С�������һ��Ԫ�شӸ���㿪ʼ���Ϲ����²��� */
	temp = H->Elements[H->Size--];
	for (Parent = 1; Parent * 2 <= H->Size; Parent = Child) {
		Child = Parent * 2;
		if ((Child != H->Size) &&
			(H->Elements[Child]->Weight > H->Elements[Child + 1]->Weight))
			Child++; /* Childָ�������ӽ��Ľ�С�� */
		if (temp->Weight <= H->Elements[Child]->Weight) break;
		else /* �ƶ�tempԪ�ص���һ�� */
			H->Elements[Parent] = H->Elements[Child];
	}
	H->Elements[Parent] = temp;
	return MinItem;
}

HuffmanTree LengthUpdate(HuffmanTree T, int RootLength)
{
	T->Length = RootLength;
	if (T->Left)
		LengthUpdate(T->Left, RootLength + 1);
	if (T->Right)
		LengthUpdate(T->Right, RootLength + 1);
	return T;
}


HuffmanTree Huffman(MinHeap H)
{ /* ����H->Size��Ȩֵ�Ѿ�����H->Elements[]->Weight�� */
	int i; 
	HuffmanTree T;
	int S = H->Size;
	for (i = 1; i < S; i++) { 		/*��S = H->Size-1�κϲ�,ע��H->Size ��ֵ����H�仯���ı䣬���ȴ��S��*/
		T = malloc(sizeof(struct TreeNode)); /*�����½��*/
		T->Left = DeleteMin(H);
		/*����С����ɾ��һ����㣬��Ϊ��T�����ӽ��*/
		T->Right = DeleteMin(H);
		/*����С����ɾ��һ����㣬��Ϊ��T�����ӽ��*/
		T->Weight = T->Left->Weight + T->Right->Weight;
		/*������Ȩֵ*/
		Insert(H, T); /*����T������С��*/
	}
	T = DeleteMin(H);    //HuffmanTree built incomplete, need to update length
	T = LengthUpdate(T, 0);     //'0' represent the length of root
	return T;
}

int WPL(HuffmanTree T)         //Calculate WPL
{
	if (!T)
		return 0;
	else if (!(T->Left) && !(T->Right))
		return T->Length * T->Weight;
	else
		return WPL(T->Left) + WPL(T->Right);
}

int LeavesNum(HuffmanTree T)  //Calculate number of leaves
{
	if (!T)
		return 0;
	else if (!(T->Left) && !(T->Right))
		return 1;
	else
		return LeavesNum(T->Left) + LeavesNum(T->Right);
}

int main(void)
{
	char *str = (char *)malloc(10);
	char c;
	int N,i,j,w;
	int set[128] = {0};
//	FILE *fp = NULL;
//	fp = fopen("04-3.txt", "r");
	scanf("%d", &N);

	MinHeap H = Create( N );  //��������ΪN����С��
	for (i = 0; i < N; i++)
	{
		scanf("%s", str);
		c = *str;
		scanf("%d", &w);
		set[c] = w;
		HuffmanTree tmp = malloc(sizeof(struct TreeNode)); /*�����½��, for node input*/
		tmp->Weight = w;
		tmp->Length = 0;
		tmp->Left = tmp->Right = NULL;
		Insert(H, tmp);
	} 

	HuffmanTree T = Huffman( H );			// ����Huffman��
	int wpl_true = WPL(T);					//������СWPLֵ
	int leavesnum_true = LeavesNum(T);		//����Ҷ�ӽ����
//	printf("True WPL = %d\n", wpl_true);
	int M;              //M students
	scanf("%d", &M);
	for (i = 0; i < M; i++)					//����M��ͬѧ��submission
	{
		HuffmanTree Root = malloc(sizeof(struct TreeNode));
		HuffmanTree Current = Root;
		Root->Length = 0;
		Root->Weight = 0;
		Root->Left = Root->Right = NULL;
		for (j = 0; j < N; j++)				//����submission��������Ӧ��������һ����Huffman��
		{
			char c, g;
			scanf("%s", str);
			c = *str;
			scanf("%s", str);
			int l = strlen(str);
			Current = Root;
			while (l--)
			{
				g = *(str++);
				if (g == '0')
				{
					if (!Current->Left)
					{
						HuffmanTree Temp = malloc(sizeof(struct TreeNode));
						Temp->Left = Temp->Right = NULL;
						Current->Left = Temp;
						Temp->Length = Current->Length + 1;
						Current = Temp;
					}
					else
						Current = Current->Left;
				}
				else if (g == '1')
				{
					if (!Current->Right)
					{
						HuffmanTree Temp = malloc(sizeof(struct TreeNode));
						Temp->Left = Temp->Right = NULL;
						Current->Right = Temp;
						Temp->Length = Current->Length + 1;
						Current = Temp;
					}
					else
						Current = Current->Right;
				}
				else
					printf("Read String Error");

				if (l == 0)
					Current->Weight = set[c];
				else
					Current->Weight = 0;
			}
		}
//		printf("%d -- ", LeavesNum(Root));
//		printf("%d\n", WPL(Root));
		if (LeavesNum(Root) != leavesnum_true)			//�����Huffman����Ҷ�ӽ����Ŀ��WPL������ȷ
			printf("No\n");
		else if (WPL(Root) != wpl_true)
			printf("No\n");
		else
			printf("Yes\n");
	}
//	fclose(fp);
	system("pause");
	return 0;
}

