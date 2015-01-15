#include<stdio.h>
#include<stdlib.h>

int g[500][500][2] = {0};
int N, M, S, D;
int dist[500][3];
int path[500];

int MinDist(void)
{
	int i, k=-1, min = 0x7fffffff;
	for (i = 0; i < N; i++)
		if (!dist[i][1] && dist[i][0] < min)
		{
			min = dist[i][0];
			k = i;
		}
	return k;
}

void Dijkstra(int s, int d)
{
	int i = 0;
	for (i = 0; i < N; i++)
	{
		dist[i][0] = 0x7fffffff;    //dist[][0] for distance
		dist[i][1] = 0;				//dist[][1]==1 means collected
		dist[i][2] = 0x7fffffff;	//dist[][1] for price
		if (i == s)
		{
			dist[i][0] = 0;  
			dist[i][2] = 0;
		}
	}
	while (1)
	{
		int v = MinDist();
		if (v == d)
			return;
		else if (v == -1)
			return;
		dist[v][1] = 1;
		for (i = 0; i < N; i++)
		{
			if (g[v][i][0] && !dist[i][1])
			{
				if (dist[v][0] + g[v][i][0] < dist[i][0])
				{
					dist[i][0] = dist[v][0] + g[v][i][0];
					dist[i][2] = dist[v][2] + g[v][i][1];
					path[i] = v;
				}
				else if (dist[v][0] + g[v][i][0] == dist[i][0])
				{
					if (dist[v][2] + g[v][i][1] < dist[i][2])
					{
						dist[i][2] = dist[v][2] + g[v][i][1];
						path[i] = v;
					}
				}
			}
		}
	}
}

int main(void)
{
	scanf("%d%d%d%d", &N, &M, &S, &D);
	int i, p, q, Dis, Price;
	for (i = 0; i < M; i++)
	{
		scanf("%d%d%d%d", &p, &q, &Dis, &Price);
		g[p][q][0] = Dis;
		g[p][q][1] = Price;
		g[q][p][0] = Dis;
		g[q][p][1] = Price;
	}

	Dijkstra(S, D);
	printf("%d %d", dist[D][0], dist[D][2]);
	//system("pause");
	return 0;
}