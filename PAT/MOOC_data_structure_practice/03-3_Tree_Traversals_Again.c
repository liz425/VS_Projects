#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int push(int a);
int pop(void);
int prtPostTree(int point);

int stk[30] = { 0 };
int stk_p = -1;
int tree[30][2] = { 0 };
int root = 0;

int main(void)
{
	int n, i;
	int flag = 0;
	char c[5];
	scanf("%d", &n);
	int father = 0;
	for (i = 1; i <= 2*n; i++)
	{
		int child;
		scanf("%s", c);
		if (strcmp(c, "Push") == 0)     //"Push" operation
		{
			scanf("%d", &child);
			push(child);
			if (flag == 0)
				tree[father][0] = child;
			else
				tree[father][1] = child;
			father = child;
			flag = 0;
			if (i == 1)
				root = child;
		}
		else                          //"Pop" operation
		{
			father = pop();
			flag = 1;
		}
	}

	prtPostTree(root);                //Postorder traversal

	//system("pause");
	return 0;
}

int push(int a)
{
	stk_p++;
	stk[stk_p] = a;
	return 0;
}

int pop(void)
{
	if (stk_p < 0)
		return -1;
	else
		return stk[stk_p--];
}

int prtPostTree(int point)
{
	if (tree[point][0])
		prtPostTree(tree[point][0]);
	if (tree[point][1])
		prtPostTree(tree[point][1]);
	if (point != root)
		printf("%d ", point);
	else
		printf("%d", point);
}

