#include<stdio.h>

#include<stdlib.h>

#pragma warning(disable:4996)

typedef struct NODE
{
	int num;
	struct EDGE* adja;
}NODE;

typedef struct EDGE
{
	int to;
	struct EDGE* next;
}EDGE;

void addEDGE_SORT(NODE* G, int from, int to)
{
	EDGE* brandNew = (EDGE*)malloc(sizeof(EDGE));
	brandNew->next = NULL;
	brandNew->to = to;
	EDGE** cur = &(G[from - 1].adja);
	if ((*cur) == NULL || (*cur)->to > to)
	{
		brandNew->next = (*cur);
		(*cur) = brandNew;
		return;
	}
	while ((*cur) != NULL)
	{
		if ((*cur)->next == NULL || (*cur)->next->to > to)
		{
			break;
		}
		cur = &((*cur)->next);
	}
	brandNew->next = (*cur)->next;
	(*cur)->next = brandNew;
}

void addEDGE(NODE* G, int a, int b)
{
	addEDGE_SORT(G, a, b);
	addEDGE_SORT(G, b, a);
}

void BFS(NODE* G, int n, int s)
{
	int* Q = (int*)calloc(n, sizeof(int));
	int* used = (int*)calloc(n, sizeof(int));
	int front = 0, end = 0;

	Q[end++] = s;
	used[s - 1] = 1;

	printf("%d\n", s);

	while (front < end)
	{
		int cur = Q[front++];
		EDGE* searching = G[cur - 1].adja;
		while (searching != NULL)
		{
			if (used[searching->to - 1] == 0)
			{
				Q[end++] = searching->to;
				used[searching->to - 1] = 1;
				printf("%d\n", searching->to);
			}
			searching = searching->next;
		}
	}
}

int main()
{
	int n = 0, m = 0, s = 0;
	scanf("%d %d %d", &n, &m, &s);
	NODE* G = (NODE*)malloc(sizeof(NODE) * n);
	for (int i = 0; i < n; i++)
	{
		G[i].adja = NULL;
	}
	for (int i = 0; i < m; i++)
	{
		int a = 0, b = 0;
		scanf("%d %d", &a, &b);
		addEDGE(G, a, b);
	}
	BFS(G, n, s);
}
