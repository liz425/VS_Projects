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
	Tnode *tree = calloc(N + 1, sizeof(Tnode));  //�ܹ�N����㣬���Ǹ��ڵ���Ϊ1���ʿ���N + 1�����ռ�
	int i, j;
	for (i = 1; i <= N; i++)
	{
		tree[i] = malloc(sizeof(struct node));
		tree[i]->size = 0;				//ÿ���ڵ�child��Ŀ��ʼ��Ϊ0
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
	//�������
	int num_current = 1;		//��ǰ��Ľ����,��ʼ��Ϊ�����
	int num_next = 0;			//��һ��Ľ����
	int leaves_cnt = 0;
	Queue *PtrQ = malloc(sizeof(Queue));				//�������У����������
	AddQ(PtrQ, 1);
	while (num_current != 0)
	{
		int i, j;
		for (i = 0; i < num_current; i++)	//������ǰ��Ľ��
		{
			int parent = DeleteQ(PtrQ);
			if (tree[parent]->size == 0)	//�����ǰ�����Ҷ�ӽ�㣬leaves_cnt++
			{
				leaves_cnt++;
				continue;
			}
			for (j = 0; j < tree[parent]->size; j++)	//��ǰ��㲻��Ҷ�ӽ�㣬child����
			{
				AddQ(PtrQ, tree[parent]->child[j]);
				num_next++;
			}
		}
		//��ǰ��ɨ�����
		printf("%d", leaves_cnt);	//�����ǰ��Ҷ�ӽڵ���,
		leaves_cnt = 0;				//��ǰ��Ҷ�ӽڵ�������
		if (num_next != 0)			//������һ�㣬����ո�
			printf(" ");
		num_current = num_next;		//���µ�ǰ��Ϊ��һ��
		num_next = 0;
	}

	//system("pause");
	return 0;
}