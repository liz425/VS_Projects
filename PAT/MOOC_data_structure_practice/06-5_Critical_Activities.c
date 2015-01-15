#include<stdio.h>
#include<stdlib.h>

int N, M, TimeMax = 0;
int Indegree[100] = { 0 };
int Outdegree[100] = { 0 };
int Earliest[100] = { 0 };
int Latest[100] = { 0 };

typedef struct NodeQ{
	int Data;
	struct NodeQ *Next;
}QNode;       //QNode for LinkQueue;

typedef struct NodeG{
	int Data;
	int Weight;
	struct NodeG *Next;
}GNode;       //GNode for Graph;

GNode **PtrGP;		//Linked Graph, Positive
GNode **PtrGN;		//Linked Graph, Negative

void GraphInsert(int x, int y, int t)
{
	//update GraphPositive
	GNode *temp1 = malloc(sizeof(GNode));
	temp1->Data = y;
	temp1->Weight = t;
	temp1->Next = PtrGP[x]->Next;
	PtrGP[x]->Next = temp1;
	Outdegree[x]++;

	//update GraphNegative
	GNode *temp2 = malloc(sizeof(GNode));
	temp2->Data = x;
	temp2->Weight = t;
	temp2->Next = PtrGN[y]->Next;
	PtrGN[y]->Next = temp2;
	Indegree[y]++;
}

typedef struct{
	QNode *rear;
	QNode *front;
}LinkQueue;
LinkQueue *PtrQ;

void AddQ(LinkQueue *PtrQ, int item)
{
	QNode *tempQ = malloc(sizeof(QNode));
	tempQ->Data = item;
	tempQ->Next = NULL;
	if (PtrQ->front == NULL)   //Empty LinkQueue
		PtrQ->front = PtrQ->rear = tempQ;
	else
	{
		PtrQ->rear->Next = tempQ;
		PtrQ->rear = tempQ;
	}
}

int DeleteQ(LinkQueue *PtrQ)
{
	if (PtrQ->front == NULL)  //Empty LinkQueue
		return -1;
	else
	{
		QNode *tempQ = PtrQ->front;
		PtrQ->front = tempQ->Next;
		if (PtrQ->front == NULL)    //Delete the last element in LinkQueue
			PtrQ->rear = NULL;		//Set LinkQueue to Empty
		int item = tempQ->Data;
		free(tempQ);					//free memory of the deleted node
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


int TopSort(void)
{
	int v, i = 0;
	int cnt = 0;
	ClearQ(PtrQ);
	for (i = 0; i < N; i++){
		if (Indegree[i] == 0)
			AddQ(PtrQ,i);
	}
	GNode *tempG;
	while (!IsEmpty(PtrQ)){
		v = DeleteQ(PtrQ);
		cnt++;					//更新已完成结点
		if (Earliest[v] > TimeMax)		//更新工程当前进度的时间
			TimeMax = Earliest[v];
		tempG = PtrGP[v]->Next;
		while (tempG != NULL){
			i = tempG->Data;			//v的每个邻结点i
			if (Earliest[v] + tempG->Weight > Earliest[i])	//结点i的Earliest更新
				Earliest[i] = Earliest[v] + tempG->Weight;
			if (--Indegree[i] == 0) //邻结点入度减1；如果为0，入队列
				AddQ(PtrQ, i);
			tempG = tempG->Next;
		}
	}
	if (cnt != N)   //图中包含有向环
		return 0;
	else			//输出工程的最大时间
		return TimeMax;
}

void ReverseTopSort(void)
{
	int v, i = 0;
	int cnt = 0;
	ClearQ(PtrQ);
	for (i = 0; i < N; i++){
		if (Outdegree[i] == 0)
			AddQ(PtrQ, i);
	}
	GNode *tempG;
	while (!IsEmpty(PtrQ)){
		v = DeleteQ(PtrQ);
		cnt++;					//更新已完成结点
		tempG = PtrGN[v]->Next;
		while (tempG != NULL){
			i = tempG->Data;			//v的每个邻结点i
			if (Latest[v] - tempG->Weight < Latest[i])	//结点i的Latest更新
				Latest[i] = Latest[v] - tempG->Weight;
			if (--Outdegree[i] == 0) //邻结点出度减1；如果为0，入队列
				AddQ(PtrQ, i);
			tempG = tempG->Next;
		}
	}
}

int main(void)
{
	scanf("%d%d", &N, &M);
	int i,s,d,t;

	PtrGP = malloc(N*sizeof(GNode *));		//PtrGP is the Positive Adjacent List of Graph
	PtrGN = malloc(N*sizeof(GNode *));		//PtrGN is the Negative Adjacent List of Graph
	//initiate Nodes of Graph
	for (i = 0; i < N; i++)
	{
		//Initiate positive Adjacent List of Graph
		PtrGP[i] = malloc(sizeof(GNode));
		PtrGP[i]->Data = i;		//first node of PtrGP[i] is node 'i' itself
		PtrGP[i]->Weight = 0;
		PtrGP[i]->Next = NULL;	//NULL means no node is connected to node i;
		
		//Initiate negative Adjacent List of Graph
		PtrGN[i] = malloc(sizeof(GNode));
		PtrGN[i]->Data = i;		
		PtrGN[i]->Weight = 0;
		PtrGN[i]->Next = NULL;	
	}
	//scan in the Graph							
	for (i = 0; i < M; i++)
	{
		scanf("%d%d%d", &s, &d, &t);
		GraphInsert(s - 1, d - 1, t);
	}
	// initiate LinkQueue
	PtrQ = malloc(sizeof(LinkQueue));
	PtrQ->rear = NULL;
	PtrQ->front = NULL;
	//Calculate the Maxtime
	int ans = TopSort();
	printf("%d\n",ans);
	if (!ans)
		return 0;
	for (i = 0; i < N; i++){
		Latest[i] = TimeMax;
	}
	ReverseTopSort();
	//print critical path
	for (i = 0; i < N; i++){
		GNode *tempG = PtrGP[i]->Next;
		while (tempG != NULL){
			if (Earliest[i] + tempG->Weight == Latest[tempG->Data])
				printf("%d->%d\n", i + 1, tempG->Data + 1);
			tempG = tempG->Next;
		}
	}
	//system("pause");
	return 0;
}