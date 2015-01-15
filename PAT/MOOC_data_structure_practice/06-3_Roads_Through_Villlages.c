#include<stdio.h>
#include<stdlib.h>

int N, M;
int *S;

typedef struct HeapStruct *MinHeap;
#define MinData -1;

typedef struct GraphNode{
	int cost;
	int source;
	int dest;
}*GraphEdge;

struct HeapStruct{
	GraphEdge *Elements;
	int Size;
	int Capacity;
};

MinHeap Create(int MaxSize)  //创建容量为MaxSize的最小堆
{
	MinHeap H = (MinHeap)malloc(sizeof(struct HeapStruct));
	H->Elements = calloc((MaxSize + 1), sizeof(GraphEdge));
	H->Size = 0;
	H->Capacity = MaxSize;
	H->Elements[0] = malloc(sizeof(struct GraphNode)); /*初始化哨兵新结点*/
	H->Elements[0]->cost = MinData;  //定义Sentinel
	H->Elements[0]->source = H->Elements[0]->dest = -1;
	return H;
}

MinHeap Insert(MinHeap H, GraphEdge item)
{		/* 将元素item 插入最小堆H，其中H->Elements[0]已经定义为哨兵 */
	int i;
	if (H->Size >= H->Capacity) {
		//printf("最小堆已满");
		return H;
	}
	i = ++(H->Size); /* i指向插入后堆中的最后一个元素的位置 */
	for (; H->Elements[i / 2]->cost > item->cost; i /= 2)
		H->Elements[i] = H->Elements[i / 2]; /* 向上过滤结点 */
	H->Elements[i] = item; /* 将item 插入 */
	return H;
}

GraphEdge DeleteMin(MinHeap H)
{			/* 从最小堆H中取出键值为最小的元素，并删除一个结点 */
	int Parent, Child;
	GraphEdge MinItem, temp;
	if (H->Size <= 0) {
		//printf("最小堆已为空");
		return NULL;
	}
	MinItem = H->Elements[1];	/* 取出根结点，最小值 */
	/* 用最小堆中最后一个元素从根结点开始向上过滤下层结点 */
	temp = H->Elements[H->Size--];
	for (Parent = 1; Parent * 2 <= H->Size; Parent = Child) {
		Child = Parent * 2;
		if ((Child != H->Size) &&
			(H->Elements[Child]->cost > H->Elements[Child + 1]->cost))
			Child++; /* Child指向左右子结点的较小者 */
		if (temp->cost <= H->Elements[Child]->cost) break;
		else /* 移动temp元素到下一层 */
			H->Elements[Parent] = H->Elements[Child];
	}
	H->Elements[Parent] = temp;
	return MinItem;
}

int GetRoot(int node)
{
	if (S[node] < 0)
		return node;
	else
		return GetRoot(S[node]);
}

void MergeSet(int a, int b)
{
	int roota = GetRoot(a);
	int rootb = GetRoot(b); 
	if (-S[roota] > -S[rootb]){
		S[roota] = S[roota] + S[rootb];
		S[rootb] = roota;
	}
	else{
		S[rootb] = S[roota] + S[rootb];
		S[roota] = rootb;
	}
}

int Kruskal(MinHeap H)
{
	int EdgeNum = 0;
	int TotalCost = 0;
	GraphEdge temp;
	while (((temp = DeleteMin(H)) != NULL) && (EdgeNum < N - 1))
	{
		if (GetRoot(temp->source) != GetRoot(temp->dest)){
			MergeSet(temp->source, temp->dest);
			TotalCost = TotalCost + temp->cost;
			EdgeNum++;
		}
	}
	if (EdgeNum == N - 1)
		return TotalCost;
	else
		return -1;
}

int main(void)
{
	scanf("%d%d", &N, &M);
	int i;
	MinHeap H = Create(M);			//创建最小堆，存放所有“边”
	S = malloc((N + 1)*sizeof(int));//创建集合，利用并查集来构建最小生成树
	for (i = 1; i <= N; i++){		//初始化集合
		S[i] = -1;
	}
	for (i = 0; i < M; i++)
	{
		GraphEdge item = malloc(sizeof(struct GraphNode));
		scanf("%d%d%d", &item->source, &item->dest, &item->cost);
		Insert(H, item);
	}
	printf("%d", Kruskal(H));
	//system("pause");
	return 0;
}