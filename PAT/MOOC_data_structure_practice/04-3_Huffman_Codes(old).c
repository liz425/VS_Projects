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

MinHeap Create(int MaxSize)  //创建容量为MaxSize的最小堆
{				
	MinHeap H = (MinHeap)malloc(sizeof(struct HeapStruct));
	H->Elements = calloc((MaxSize + 1),sizeof(HuffmanTree));
	int i = 0;
	for (i = 0; i <= MaxSize; i++)
	{
		*(H->Elements + i) = calloc(1, sizeof(struct TreeNode));
	}
	H->Size = 0;
	H->Capacity = MaxSize;
	(*(H->Elements)) = malloc(sizeof(struct TreeNode)); /*初始化哨兵新结点*/
	(*(H->Elements))->Weight = MinData;  //定义Sentinel
	(*(H->Elements))->Left = (*(H->Elements))->Right = NULL;
	(*(H->Elements))->Length = 0;
	return H;
}

MinHeap Insert(MinHeap H, HuffmanTree item)
{		/* 将元素item 插入最小堆H，其中H->Elements[0]已经定义为哨兵 */
	int i;
	if (H->Size >= H->Capacity) {
		printf("最小堆已满");
		return H;
	}
	i = ++(H->Size); /* i指向插入后堆中的最后一个元素的位置 */
	for (; (*(H->Elements + i/2))->Weight > item->Weight; i /= 2)
		*(H->Elements + i) = *(H->Elements + i/2); /* 向上过滤结点 */
	*(H->Elements + i) = item; /* 将item 插入 */
	return H;
}

HuffmanTree DeleteMin(MinHeap H)
{			/* 从最小堆H中取出键值为最小的元素，并删除一个结点 */
	int Parent, Child;
	HuffmanTree MinItem, temp;
	if (H->Size <= 0) {
		printf("最小堆已为空");
		return NULL;
	}
	MinItem = *(H->Elements + 1);	/* 取出根结点，最小值 */
	/* 用最小堆中最后一个元素从根结点开始向上过滤下层结点 */
	temp = *(H->Elements + H->Size--);
	for (Parent = 1; Parent * 2 <= H->Size; Parent = Child) {
		Child = Parent * 2;
		if ((Child != H->Size) &&
			((*(H->Elements + Child))->Weight > (*(H->Elements + Child + 1))->Weight))
			Child++; /* Child指向左右子结点的较小者 */
		if (temp->Weight <= (*(H->Elements + Child))->Weight) break;
		else /* 移动temp元素到下一层 */
			*(H->Elements + Parent) = *(H->Elements + Child);
	}
	*(H->Elements + Parent) = temp;
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
{ /* 假设H->Size个权值已经存在H->Elements[]->Weight里 */
	int i; 
	HuffmanTree T;
	int S = H->Size;
	for (i = 1; i < S; i++) {		/*做H->Size-1次合并,注意不能直接用H->Size,应该随着H变化，Size也会变化*/
		T = malloc(sizeof(struct TreeNode)); /*建立新结点*/
		T->Left = DeleteMin(H);
		/*从最小堆中删除一个结点，作为新T的左子结点*/
		T->Right = DeleteMin(H);
		/*从最小堆中删除一个结点，作为新T的右子结点*/
		T->Weight = T->Left->Weight + T->Right->Weight;
		/*计算新权值*/
		Insert(H, T); /*将新T插入最小堆*/
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
	MinHeap H = Create( N );  //创建容量为N的最小堆
	for (i = 0; i < N; i++)
	{
		scanf("%s", str);
		c = *str;
		scanf("%d", &w);
		set[c] = w;
		HuffmanTree tmp = malloc(sizeof(struct TreeNode)); /*建立新结点, for node input*/
		tmp->Weight = w;
		tmp->Length = 0;
		tmp->Left = tmp->Right = NULL;
		Insert(H, tmp);
	} 

	HuffmanTree T = Huffman( H );
	int wpl_true = WPL(T);
	int leavesnum_true = LeavesNum(T);
//	printf("True WPL = %d\n", wpl_true);
	int M;              //M students
	scanf("%d", &M);
	for (i = 0; i < M; i++)
	{
		HuffmanTree Root = malloc(sizeof(struct TreeNode));
		HuffmanTree Current = Root;
		Root->Length = 0;
		Root->Weight = 0;
		Root->Left = Root->Right = NULL;
		for (j = 0; j < N; j++)
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
		if (LeavesNum(Root) != leavesnum_true)
			printf("No\n");
		else if (WPL(Root) != wpl_true)
			printf("No\n");
		else
			printf("Yes\n");
	}

	//system("pause");
	return 0;
}