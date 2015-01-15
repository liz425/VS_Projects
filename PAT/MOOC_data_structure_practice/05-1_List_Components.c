#include<stdio.h>
#include<stdlib.h>

int g[10][10] = { 0 };
int visited[10] = { 0 };
int N, E;


void DFS (v)
{
	int i = 0;
	visited[v] = 1;
	printf("%d ", v);
	for (i = 0; i < N; i++)
	{
		if (!visited[i] && g[v][i])
			DFS(i);
	}
}

typedef struct{
	int Data[10];
	int rear;
	int front;
}Queue;

Queue *Q;

void AddQ(Queue *PtrQ, int item)
{
	if ((PtrQ->rear + 1) % 10 == PtrQ->front)
		return;
	PtrQ->rear = (PtrQ->rear + 1) % 10;
	PtrQ->Data[PtrQ->rear] = item;
}

int DeleteQ(Queue *PtrQ)
{
	if (PtrQ->front == PtrQ->rear)
		return -1;
	else
	{
		PtrQ->front = (PtrQ->front + 1) % 10;
		return PtrQ->Data[PtrQ->front];
	}
}

int IsEmpty(Queue *PtrQ)
{
	if (PtrQ->rear == PtrQ->front)
		return 1;
	else
		return 0;
}

void BFS(int v)
{
	visited[v] = 1;
	printf("%d ", v);
	AddQ(Q, v);
	while (!IsEmpty(Q))
	{
		int v = DeleteQ(Q);
		int i = 0;
		for(i = 0; i < N; i++)
		if (!visited[i] && g[v][i])
		{
			visited[i] = 1;
			printf("%d ", i);
			AddQ(Q, i);
		}
	}
	return;
}

int main(void)
{
	int i = 0;
	scanf("%d%d", &N, &E);
	for (i = 0; i < E; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		g[a][b] = g[b][a] = 1;
	}

	//// DFS
	for (i = 0; i < N; i++)
	{
		if (!visited[i])
		{
			printf("{ ");
			DFS(i);
			printf("}\n");
		}
	}

	// Re-initiate
	Q = malloc(sizeof(Queue));
	Q->rear = 0;
	Q->front = 0;
	for (i = 0; i < N; i++)
		visited[i] = 0;

	//BFS
	for (i = 0; i < N; i++)
	{
		if (!visited[i])
		{
			printf("{ ");
			BFS(i);
			printf("}\n");
		}
	}

	//system("pause");
	return 0;
}

