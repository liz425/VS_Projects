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

MinHeap Create(int MaxSize)  //��������ΪMaxSize����С��
{
	MinHeap H = (MinHeap)malloc(sizeof(struct HeapStruct));
	H->Elements = calloc((MaxSize + 1), sizeof(GraphEdge));
	H->Size = 0;
	H->Capacity = MaxSize;
	H->Elements[0] = malloc(sizeof(struct GraphNode)); /*��ʼ���ڱ��½��*/
	H->Elements[0]->cost = MinData;  //����Sentinel
	H->Elements[0]->source = H->Elements[0]->dest = -1;
	return H;
}

MinHeap Insert(MinHeap H, GraphEdge item)
{		/* ��Ԫ��item ������С��H������H->Elements[0]�Ѿ�����Ϊ�ڱ� */
	int i;
	if (H->Size >= H->Capacity) {
		//printf("��С������");
		return H;
	}
	i = ++(H->Size); /* iָ��������е����һ��Ԫ�ص�λ�� */
	for (; H->Elements[i / 2]->cost > item->cost; i /= 2)
		H->Elements[i] = H->Elements[i / 2]; /* ���Ϲ��˽�� */
	H->Elements[i] = item; /* ��item ���� */
	return H;
}

GraphEdge DeleteMin(MinHeap H)
{			/* ����С��H��ȡ����ֵΪ��С��Ԫ�أ���ɾ��һ����� */
	int Parent, Child;
	GraphEdge MinItem, temp;
	if (H->Size <= 0) {
		//printf("��С����Ϊ��");
		return NULL;
	}
	MinItem = H->Elements[1];	/* ȡ������㣬��Сֵ */
	/* ����С�������һ��Ԫ�شӸ���㿪ʼ���Ϲ����²��� */
	temp = H->Elements[H->Size--];
	for (Parent = 1; Parent * 2 <= H->Size; Parent = Child) {
		Child = Parent * 2;
		if ((Child != H->Size) &&
			(H->Elements[Child]->cost > H->Elements[Child + 1]->cost))
			Child++; /* Childָ�������ӽ��Ľ�С�� */
		if (temp->cost <= H->Elements[Child]->cost) break;
		else /* �ƶ�tempԪ�ص���һ�� */
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
	MinHeap H = Create(M);			//������С�ѣ�������С��ߡ�
	S = malloc((N + 1)*sizeof(int));//�������ϣ����ò��鼯��������С������
	for (i = 1; i <= N; i++){		//��ʼ������
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