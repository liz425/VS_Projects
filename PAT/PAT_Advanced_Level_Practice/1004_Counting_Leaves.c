#include<stdio.h>
#include<stdlib.h>

//1004 Counting Leaves
#define MaxSize 100
typedef struct node{
	int size;
	int *child;
}*Tnode;

typedef struct{
	int data[MaxSize];
	int rear;
	int front;
}Queue;

void AddQ(Queue *PtrQ, int item)
{
	if ((PtrQ->rear + 1) % MaxSize == PtrQ->front)
		return;
	PtrQ->rear = (PtrQ->rear + 1) % MaxSize;
	PtrQ->data[PtrQ->rear] = item;
}

int DeleteQ(Queue *PtrQ)
{
	if (PtrQ->rear == PtrQ->front)
		return -1;
	else
	{
		PtrQ->front = (PtrQ->front + 1) % MaxSize;
		return PtrQ->data[PtrQ->front];
	}
}

int IsEmpty(Queue *PtrQ)
{
	if (PtrQ->rear == PtrQ->front)
		return 1;
	else
		return 0;
}

int main(void)
{
	int N, M;
	scanf("%d%d", &N, &M);
	Tnode *tree = calloc(N + 1, sizeof(Tnode));  //总共N个结点，但是根节点编号为1，故开辟N + 1个结点空间
	int i, j;
	for (i = 1; i <= N; i++)
	{
		tree[i] = malloc(sizeof(struct node));
		tree[i]->size = 0;				//每个节点child数目初始化为0
	}
	for (i = 1; i <= M; i++)
	{
		int ID, K;
		scanf("%d%d", &ID, &K);
		tree[ID]->size = K;
		tree[ID]->child = calloc(K, sizeof(int));
		for (j = 0; j < K; j++)
		{
			scanf("%d", &tree[ID]->child[j]);
		}
	}
	//层序遍历
	int num_current = 1;		//当前层的结点数,初始化为根结点
	int num_next = 0;			//下一层的结点数
	int leaves_cnt = 0;
	Queue *PtrQ = malloc(sizeof(Queue));				//创建队列，根结点入列
	AddQ(PtrQ, 1);
	while (num_current != 0)
	{
		int i, j;
		for (i = 0; i < num_current; i++)	//遍历当前层的结点
		{
			int parent = DeleteQ(PtrQ);
			if (tree[parent]->size == 0)	//如果当前结点是叶子结点，leaves_cnt++
			{
				leaves_cnt++;
				continue;
			}
			for (j = 0; j < tree[parent]->size; j++)	//当前结点不是叶子结点，child入列
			{
				AddQ(PtrQ, tree[parent]->child[j]);
				num_next++;
			}
		}
		//当前层扫描完毕
		printf("%d", leaves_cnt);	//输出当前层叶子节点数,
		leaves_cnt = 0;				//当前层叶子节点数清零
		if (num_next != 0)			//还有下一层，输出空格
			printf(" ");
		num_current = num_next;		//跟新当前层为下一层
		num_next = 0;
	}

	//system("pause");
	return 0;
}