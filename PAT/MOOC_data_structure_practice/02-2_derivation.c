#include<stdio.h>
#include<stdlib.h>


typedef struct Node{
	int coef;
	int expo;
	struct Node *next;
}PNode;

int main(void)
{
	int coef, expo= 1;
	PNode *head = (PNode *)malloc(sizeof(PNode));
	head->coef = 0;
	head->expo = 0;
	head->next = NULL;
	PNode *rear = head;
	//FILE *fp = NULL;
	//fp = fopen("2-2.txt", "r");
	while (1)
	{
		//if(fscanf(fp,"%d", &coef) == EOF)
		if(scanf("%d", &coef) == EOF)
			break;
		//fscanf(fp, "%d", &expo);
		scanf("%d", &expo);
		if (expo == 0)
			continue;
		PNode *tmp = (PNode *)malloc(sizeof(PNode));
		tmp->coef = coef * expo;
		tmp->expo = expo - 1;
		tmp->next = NULL;
		rear->next = tmp;
		rear = tmp;
	}

	PNode *current = head->next;
	if (current == NULL)
		printf("%d %d", 0,0);
	while (current)
	{	
		if (current->next)
			printf("%d %d ", current->coef,current->expo);
		else
			printf("%d %d", current->coef, current->expo);
		current = current->next;
	}
	//fclose(fp);
	//system("pause");
	return 0;
}