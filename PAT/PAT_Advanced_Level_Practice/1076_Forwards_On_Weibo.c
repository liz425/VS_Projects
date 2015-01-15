#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int g[10000][10000] = { 0 };
int *visited;
int N, E, L;


typedef struct Node{
	int Data;
	struct Node *Next;
}QNode, GNode;       //QNode for LinkQueue; GNode for Graph

typedef struct{
	QNode *rear;
	QNode *front;
}LinkQueue;
LinkQueue *PtrQ;

GNode **PtrG;       //Graph
GNode **RearG;		//rear point of list PtrG[i], used for graph generate acceleration

void AddQ(LinkQueue *PtrQ, int item)
{
	QNode *temp = malloc(sizeof(QNode));
	temp->Data = item;
	temp->Next = NULL;
	if (PtrQ->front == NULL)   //Empty LinkQueue
		PtrQ->front = PtrQ->rear = temp;
	else
	{
		PtrQ->rear->Next = temp;
		PtrQ->rear = temp;
	}
}

int DeleteQ(LinkQueue *PtrQ)
{
	if (PtrQ->front == NULL)  //Empty LinkQueue
		return -1;
	else
	{
		QNode *temp = PtrQ->front;
		PtrQ->front = temp->Next;
		if (PtrQ->front == NULL)    //Delete the last element in LinkQueue
			PtrQ->rear = NULL;		//Set LinkQueue to Empty
		int item = temp->Data;
		free(temp);					//free memory of the deleted node
		return item;
	}
}

void ClearQ(LinkQueue *PtrQ)
{
	//	while (PtrQ->front != NULL)
	//		DeleteQ(PtrQ);
	PtrQ->front = PtrQ->rear = NULL;
}

int IsEmpty(LinkQueue *PtrQ)
{
	if (PtrQ->front == NULL)
		return 1;
	else
		return 0;
}

//void GraphInsert(int x, int y)
//{
//	GNode *temp = PtrG[x];
//	while (temp->Next != NULL)
//		temp = temp->Next;
//	temp->Next = malloc(sizeof(GNode));
//	temp->Next->Data = y;
//	temp->Next->Next = NULL;
//}

void GraphInsert(int x, int y)
{
	GNode *temp = malloc(sizeof(GNode));
	temp->Data = y;
	temp->Next = NULL;
	RearG[x]->Next = temp;
	RearG[x] = temp;
}

int IsAdjacent(int x, int y)
{
	GNode *temp = PtrG[x];
	while (temp->Next != NULL)
	{
		temp = temp->Next;
		if (temp->Data == y)
			return 1;
	}
	return 0;
}

int BFS(int v)
{
	int i = 0;
	for (i = 0; i < N; i++)     //clear visited
		visited[i] = 0;
	//int visited[10000] = { 0 };
	visited[v] = 1;
	int count = 0;
	int level = 0;
	int last = v;
	int tail = v;
	ClearQ(PtrQ);				//clear LinkQueue
	AddQ(PtrQ, v);
	while (!IsEmpty(PtrQ))
	{
		int v = DeleteQ(PtrQ);
		for (i = 0; i < N; i++)
		{
			//if (!visited[i] && IsAdjacent(v, i))
			if (!visited[i] && g[v][i])
			{
				visited[i] = 1;
				AddQ(PtrQ, i);
				count++;
				//				if (count == N) break;
				tail = i;
			}
		}
		if (v == last)
		{
			level++;
			last = tail;
		}
		if (level == L) break;
	}
	return count;
}



int main(void)
{
	int i = 0;
	//FILE *fp;
	//fp = fopen("05-3.txt", "r");
	//clock_t start, stop;
	//start = clock();
	scanf("%d%d", &N, &L);
	PtrG = malloc(N*sizeof(GNode *));		//PtrG is the Adjacent List of Graph
	RearG = malloc(N*sizeof(GNode *));		//RearG is just for GraphInsert convenience
	visited = malloc(N*sizeof(int));
	//initiate Nodes of Graph
	for (i = 0; i < N; i++)
	{
		PtrG[i] = malloc(sizeof(GNode));
		PtrG[i]->Data = i;		//first node of PtrG.[i] is node 'i' itself
		PtrG[i]->Next = NULL;	//NULL means no node is connected to node i;
		RearG[i] = PtrG[i];
	}

	//Generate Graph PtrG
	for (i = 0; i < N; i++)
	{
		int j, K, m;
		scanf("%d", &K);
		for (j = 0; j < K; j++)
		{
			scanf("%d", &m);
			//GraphInsert(m-1, i); 		//The index of node 'a' is 'a-1'
			g[m-1][i] = 1;
		}
	}


	// initiate LinkQueue
	PtrQ = malloc(sizeof(LinkQueue));
	PtrQ->rear = NULL;
	PtrQ->front = NULL;

	//BFS
	int K;
	scanf("%d", &K);
	for (i = 0; i < K; i++)
	{
		int p;
		scanf("%d", &p);
		int count = BFS(p-1);
		printf("%d\n",count);
	}
	//stop = clock();
	//fclose(fp);
	//double duration = ((double)(stop - start)) / CLK_TCK;
	//printf("N = %d\n", N);
	//printf("Execution Duration = %f\n", duration);
	//printf("CLK_TCK = %d\n", CLK_TCK);
	//system("pause");
	return 0;
}

