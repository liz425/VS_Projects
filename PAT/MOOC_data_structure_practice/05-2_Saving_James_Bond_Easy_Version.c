#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct node{
	int x;
	int y;
}cnode;

cnode *croc;
int *visited;
int N, JumpL;


int DFS(item)
{
	if ((abs(croc[item].x) >= 50 - JumpL) || (abs(croc[item].y) >= 50 - JumpL))
		return 1;
	else
	{
		int i = 0;
		for (i = 0; i < N; i++)
		{
			if ((i != item) && !visited[i] && (pow(croc[i].x - croc[item].x, 2) + pow(croc[i].y - croc[item].y, 2) <= pow(JumpL, 2)))
			{
				visited[i] = 1;
				int ans = DFS(i);
				if (ans)
					return 1;
			}
		}
		return 0;
	}
}

int main(void)
{
	scanf("%d%d", &N, &JumpL);
	croc = calloc(N, sizeof(cnode));
	int i;
	visited = calloc(N, sizeof(int));

	//initiate position of crocodiles
	for (i = 0; i < N; i++)
	{
		scanf("%d%d", &croc[i].x, &croc[i].y);
		visited[i] = 0;
	}
	int ans = 0;

	//James Bond could jump out of the lake directly from the island
	if (JumpL + 7.5 >= 50)
	{
		printf("Yes");
		return 0;
	}

	//DFS
	for (i = 0; i < N; i++)
	{
		if ((pow(croc[i].x, 2) + pow(croc[i].y, 2) <= pow(JumpL + 7.5,2)) && !visited[i])
		{
			visited[i] = 1;
			ans = DFS(i);
			if (ans)
			{
				printf("Yes");
				//system("pause");
				return 0;
			}
		}
	}
	printf("No");
	//system("pause");
	return 0;
}