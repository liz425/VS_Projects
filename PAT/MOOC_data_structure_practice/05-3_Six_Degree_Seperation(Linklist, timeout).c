#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int N, E;


typedef struct Node{
	int Data;
	struct Node *Next;
}QNode,GNode;       //QNode for LinkQueue; GNode for Graph

typedef struct{
	QNode *rear;
	QNode *front;
}LinkQueue;
LinkQueue *PtrQ;

GNode **PtrG;       //Graph

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
	while (PtrQ->front != NULL)
		DeleteQ(PtrQ);			//use DeleteQ to free the memory, but slower
	//PtrQ->front = PtrQ->rear = NULL;  //directly set the pointer, faster but may lead to memory leakage
}

int IsEmpty(LinkQueue *PtrQ)
{
	if (PtrQ->front == NULL)
		return 1;
	else
		return 0;
}


void GraphInsert(int x, int y)
{
	GNode *temp = malloc(sizeof(GNode));
	temp->Data = y;
	temp->Next = PtrG[x]->Next;
	PtrG[x]->Next = temp;
}


int BFS(int v)
{
	int i=0;
	int *visited = malloc(N*sizeof(int));
	for (i = 0; i < N; i++)
		visited[i] = 0;
	//int visited[10000] = {0};
	visited[v] = 1;
	int count = 1;
	int level = 0;
	int last = v;
	int tail = v;
	ClearQ(PtrQ);				//clear LinkQueue
	AddQ(PtrQ, v);
	while (!IsEmpty(PtrQ))
	{
		int v = DeleteQ(PtrQ);
		GNode *temp = PtrG[v]->Next;
		while (temp!=NULL)
		{
			i = temp->Data;
			if (!visited[i])
			{
				visited[i] = 1;
				AddQ(PtrQ, i);
				count++;
				tail = i;
			}
			temp = temp->Next;
		}
		if (v == last)
		{
			level++;
			last = tail;
		}
		if (level == 6) break;
	}
	free(visited);
	return count;
}



int main(void)
{
	int i = 0;
	FILE *fp;
	fp = fopen("05-3.txt", "r");
	clock_t start, stop;
	fscanf(fp, "%d%d", &N, &E);
	printf("N = %d, E = %d\n", N, E);
	system("Pause");
	start = clock();
	PtrG = malloc(N*sizeof(GNode *));		//PtrG is the Adjacent List of Graph
	//initiate Nodes of Graph
	for (i = 0; i < N; i++)
	{
		PtrG[i] = malloc(sizeof(GNode));
		PtrG[i]->Data = i;		//first node of PtrG.[i] is node 'i' itself
		PtrG[i]->Next = NULL;	//NULL means no node is connected to node i;
	}

	//Generate Graph PtrG
	for (i = 0; i < E; i++)
	{
		int a, b;
		fscanf(fp, "%d%d", &a, &b);
		GraphInsert(a - 1, b - 1); 		//The index of node 'a' is 'a-1'
		GraphInsert(b - 1, a - 1);
	}


	// initiate LinkQueue
	PtrQ = malloc(sizeof(LinkQueue));
	PtrQ->rear = NULL;
	PtrQ->front = NULL;
	
	//BFS
	for (i = 0; i < N; i++)
	{
		int count =	BFS(i);
		printf("%d: %.2f%%\n", i + 1, count*100.0 / N);
	}
	stop = clock();
	fclose(fp);
	double duration = ((double)(stop - start)) / CLK_TCK;
	printf("N = %d\n", N);
	printf("Execution Duration = %f\n", duration);
	printf("CLK_TCK = %d\n", CLK_TCK);
	system("pause");
	return 0;
}

