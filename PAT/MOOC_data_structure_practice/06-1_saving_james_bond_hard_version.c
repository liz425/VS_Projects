#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int *dist;
int *path;
int N, JumpL;

typedef struct node{
	int x;
	int y;
}cnode;
cnode *croc;

typedef struct Node{
	int Data;
	struct Node *Next;
}QNode;       //QNode for LinkQueue; GNode for Graph

typedef struct{
	QNode *rear;
	QNode *front;
}LinkQueue;
LinkQueue *PtrQ;

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

int BFS(void)
{
	while (!IsEmpty(PtrQ))
	{
		int item = DeleteQ(PtrQ);
		if ((abs(croc[item].x) >= 50 - JumpL) || (abs(croc[item].y) >= 50 - JumpL))
			return item;
		else
		{
			int i = 0;
			for (i = 0; i < N; i++)
				if ((i != item) && (dist[i] == -1) && (pow(croc[i].x - croc[item].x, 2) + pow(croc[i].y - croc[item].y, 2) <= pow(JumpL, 2)))
				{
					AddQ(PtrQ, i);
					dist[i] = dist[item] + 1;
					path[i] = item;
				}
		}
	}
	return -1;
}

void PrintPath(item)
{
	if (path[item] != -1)
		PrintPath(path[item]);
	printf("%d %d\n", croc[item].x, croc[item].y);
}

int main(void)
{
	scanf("%d%d", &N, &JumpL);
	croc = calloc(N, sizeof(cnode));
	dist = calloc(N, sizeof(int));
	path = calloc(N, sizeof(int));

	//James Bond could jump out of the lake directly from the island
	if (JumpL + 7.5 >= 50)
	{
		printf("%d", 1);
		return 0;
	}
	
	// initiate LinkQueue
	PtrQ = malloc(sizeof(LinkQueue));
	PtrQ->rear = NULL;
	PtrQ->front = NULL;

	//initiate position of crocodiles
	int i;
	int dis2[100];				//used dis2[100] to sort the first node, make sure of the minimum first jump
	for (i = 0; i < N; i++)
	{
		scanf("%d%d", &croc[i].x, &croc[i].y);
		path[i] = -1;
		int dis = pow(croc[i].x, 2) + pow(croc[i].y, 2);
		if (dis <= pow(JumpL + 7.5, 2))
		{
			dist[i] = 1;
			dis2[i] = dis;
		}
		else
		{
			dist[i] = -1;
			dis2[i] = 0x7fffffff;
		}
	}

	for (i = 0; i < N; i++)
	{
		int min = 0x7fffffff;
		int j = 0, k = 0;
		for (j = 0; j < N; j++)
		{
			if (dis2[j] < min)
			{
				min = dis2[j];
				k = j;
			}
		}
		if (min < 0x7fffffff)
		{
			AddQ(PtrQ, k);
			dis2[k] = 0x7fffffff;
		}
	}
		
	//BFS
	int ans = BFS();
	if (ans != -1)
	{
		printf("%d\n",dist[ans] + 1);
		PrintPath(ans);
	}
	else
		printf("0");
	//system("pause");
	return 0;
}