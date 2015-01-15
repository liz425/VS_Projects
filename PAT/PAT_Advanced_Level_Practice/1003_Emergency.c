#include<stdio.h>
#include<stdlib.h>

//PAT Adcanced Level 1003: Emergency

int g[500][500] = { 0 };	//�洢ͼ��Ϣ��ֵΪ�����·��Ȩ��
int person[500] = { 0 };	//ĳһ����rescue teams number 
int N, M, S, D;				//city����road������㣬�յ�
int path[500] = { 0 };		//ĳһ�㵽�������·���������������в�����̣�
int dist[500] = { 0 };		//ĳһ�㵽���ľ���
int collected[500] = { 0 };	//ĳһ���Ƿ񱻷��ʹ�
int p_coll[500] = { 0 };	//���õ�����·���������в��У������rescue teams number��

int MinDist(void)
{
	int i, k = -1, min = 0x7fffffff;
	for (i = 0; i < N; i++)
	{
		if (!collected[i] && (dist[i] < min))
		{
			min = dist[i];
			k = i;
		}
	}
	return k;
}

void Dijkstra(int s, int d)
{
	int i = 0;
	for (i = 0; i < N; i++)
	{
		dist[i] = 0x7fffffff;
	}
	dist[s] = 0;
	path[s] = 1;
	p_coll[s] = person[s];
	collected[s] = 0;
	while (1)
	{
		int v = MinDist();
		if (v == d)
			return;
		else if (v == -1)
			return;
		collected[v] = 1;
		for (i = 0; i < N; i++)
		{
			if (g[v][i] && !collected[i])
			{
				if (dist[v] + g[v][i] < dist[i])
				{
					dist[i] = dist[v] + g[v][i];
					p_coll[i] = p_coll[v] + person[i];
					path[i] = path[v];
				}
				else if (dist[v] + g[v][i] == dist[i])
				{
					path[i] = path[i] + path[v];
					if (p_coll[v] + person[i] > p_coll[i])
					{
						p_coll[i] = p_coll[v] + person[i];
					}
				}
			}
		}
	}
}

int main(void)
{
	scanf("%d%d%d%d", &N, &M, &S, &D);
	int i = 0;
	int p, q, dis;
	for (i = 0; i < N; i++)
	{
		scanf("%d", &person[i]);
	}
	for (i = 0; i < M; i++)
	{
		scanf("%d%d%d", &p, &q, &dis);
		g[p][q] = dis;
		g[q][p] = dis;
	}
	Dijkstra(S, D);
	printf("%d %d", path[D], p_coll[D]);
	//system("pause");
	return 0;
}