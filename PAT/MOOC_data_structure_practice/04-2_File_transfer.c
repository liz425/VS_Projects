#include<stdio.h>
#include<stdlib.h>

typedef struct{
	int Data;
	int Parent;	
}SetType;

int GetRoot(SetType *s, int node)
{
	if (s[node - 1].Parent < 0)
		return node;
	else
		return GetRoot(s, s[node - 1].Parent + 1);
}

int main(void)
{
	int N;
	scanf("%d", &N);
	SetType *s = calloc(N,sizeof(SetType));
	int i = N;
	while (i--)
	{
		s[i].Data = i + 1;
		s[i].Parent = -1;
	}
	char str[2];
	char c;
	scanf("%s", str);
	c = *str;
	int sum = 0;
	while (c != 'S')
	{
		int c1, c2;
		scanf("%d%d", &c1, &c2);
		if (c == 'C')
		{
			if (GetRoot(s, c1) == GetRoot(s, c2))
				printf("yes\n");
			else
				printf("no\n");
		}
		else if (c == 'I')
		{	
			int root1 = GetRoot(s, c1);
			int root2 = GetRoot(s, c2);
			if (root1 != root2)
			{	
				sum++;
				if (-s[root1-1].Parent < -s[root2-1].Parent)
				{
					s[root2 - 1].Parent = s[root1 - 1].Parent + s[root2 - 1].Parent;
					s[root1 - 1].Parent = root2 - 1;
				}
				else
				{
					s[root1 - 1].Parent = s[root1 - 1].Parent + s[root2 - 1].Parent;
					s[root2 - 1].Parent = root1 - 1;
				}
			}
		}
		else
			printf("Error\n");
		scanf("%s", str);
		c = *str;
	}
	
	
	if (sum < N-1)
		printf("There are %d components.", N - sum);
	else if (sum == N-1)
		printf("The network is connected.");
	else
		printf("Error");
	//system("pause");
	return 0;
}