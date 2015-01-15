#include<stdio.h>
#include<stdlib.h>

int N, M, TimeMax = 0;
int cnt = 0;
int g[100][100] = { 0 };
int Indegree[100] = { 0 };
int Earliest[100] = { 0 };

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


void TopSort(void)
{
	int v, i = 0;
	for (i = 0; i < N; i++){
		if (Indegree[i] == 0)
			AddQ(PtrQ,i);
	}
	while (!IsEmpty(PtrQ)){
		v = DeleteQ(PtrQ);
		cnt++;					//��������ɽ��
		if (Earliest[v] > TimeMax)		//���¹��̵�ǰ���ȵ�ʱ��
			TimeMax = Earliest[v];
		for (i = 0; i < N; i++){
			if (g[v][i] != -1){			//v��ÿ���ڽ��i
				if (Earliest[v] + g[v][i] > Earliest[i])	//���i��Earliest����
					Earliest[i] = Earliest[v] + g[v][i];
				if (--Indegree[i] == 0) //�ڽ����ȼ�1�����Ϊ0�������
					AddQ(PtrQ, i);
			}
		}
	}
	if (cnt != N)   //ͼ�а�������
		printf("Impossible");
	else			//������̵����ʱ��
		printf("%d", TimeMax);
}

int main(void)
{
	scanf("%d%d", &N, &M);
	int i,j,s,d,t;
	//Initiate the Graph
	for (i = 0; i < N;i++)		//'-1' stands for no connection
		for (j = 0; j < N; j++)	//because the weight of an edge can be '0' 
			g[i][j] = -1;		
	//scan in the Graph							
	for (i = 0; i < M; i++)
	{
		scanf("%d%d%d", &s, &d, &t);
		g[s][d] = t;
		Indegree[d]++;
	}
	// initiate LinkQueue
	PtrQ = malloc(sizeof(LinkQueue));
	PtrQ->rear = NULL;
	PtrQ->front = NULL;
	//Calculate the Maxtime
	TopSort();
	//system("pause");
	return 0;
}