#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
	int Address;
	int Data;
	int next;
	struct Node *PPrior;
	struct Node *PNext;
}PNode;


int main(void)
{
	int N, K;
	PNode *PtrL = (PNode *)malloc(sizeof(PNode));  //create a linked list

	scanf("%d", &(PtrL->next));  //linked list info
	scanf("%d", &N);
	scanf("%d", &K);
	int c = N;
	int ary[100000][2];

	while (c--)		//input scanning, store node into a array
	{
		int i, j, k;
		scanf("%d", &i);
		scanf("%d", &j);
		scanf("%d", &k);
		ary[i][0] = j;
		ary[i][1] = k;
	}

/////////////////////////////////////////////////////////////
//---------------create list--------------------------------
/////////////////////////////////////////////////////////////
	PNode *rear = PtrL;
	int trueN = 0;			// length of linked list, removed unuseful nodes
	while (rear->next != -1)   //assemble the linked list
	{
		PNode *tmp = (PNode *)malloc(sizeof(PNode));
		rear->PNext = tmp;
		tmp->Address = rear->next;
		tmp->Data = ary[tmp->Address][0];
		tmp->next = ary[tmp->Address][1];
		tmp->PPrior = rear;
		tmp->PNext = NULL;
		rear->PNext = tmp;
		rear = tmp;
		trueN++;
	}

/////////////////////////////////////////////////////////////
//------------reverse the list------------------------------
/////////////////////////////////////////////////////////////
	int loopn = trueN / K;     // time of reverse operation
	int loopi = 0;
	PNode *current = PtrL->PNext;
	while(loopn--)         // reverse loopn times
	{
		PNode *priorsec, *nextsec, *first;
		for (loopi = 0; loopi < K; loopi++)
		{
			PNode *exg;
			if (loopi == 0)
			{
				first = current;
				priorsec = current->PPrior;
				current->PPrior = current->PNext;
				current = current->PPrior;   //point to "next" element
			}
			else if (loopi == K - 1)
			{
				nextsec = current->PNext;
				current->PNext = current->PPrior;
				current->next = current->PNext->Address;
				current->PPrior = priorsec;
				priorsec->PNext = current;
				priorsec->next = current->Address;
				if (nextsec != NULL)
				{
					nextsec->PPrior = first;
					first->next = nextsec->Address;
				}
				else
					first->next = -1;
				first->PNext = nextsec;
				current = nextsec;
			}
			else
			{
				exg = current->PNext;
				current->PNext = current->PPrior;
				current->PPrior = exg;
				current->next = current->PNext->Address;
				current = current->PPrior;
			}
		}

	}

/////////////////////////////////////////////////////////////
//--------------print the list-------------------------------
/////////////////////////////////////////////////////////////
	current = PtrL->PNext;   //back to head of the linked list
	while (current)
	{
		if (current->next == -1)
		{
			printf("%05d %d %d\n", current->Address, current->Data, current->next);
			break;
		}
		else
			printf("%05d %d %05d\n", current->Address, current->Data, current->next);
		current = current->PNext;
	}
	//system("pause");
	return 0;
}


