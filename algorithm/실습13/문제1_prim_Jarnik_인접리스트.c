#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef struct NODE
{
    struct EDGE* adja;
}NODE;

typedef struct EDGE
{
    struct EDGE* next;
    int to;
    int w;
}EDGE;


void addEDGE_sorted(NODE* G, int from, int to, int w)
{
    EDGE** cur = &(G[from - 1].adja);
    EDGE* brandNew = (EDGE*)malloc(sizeof(EDGE));
    brandNew->next = NULL;
    brandNew->to = to;
    brandNew->w = w;
    brandNew->next = (*cur);
    (*cur) = brandNew;
}

void prim_Jarnik(NODE* G, int n)
{
    int* dist = (int*)malloc(sizeof(int) * n);
    int* used = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        dist[i] = 1000000;
        used[i] = 0;
    }
    int cur= 0;
    dist[cur] = 0;
    for (int i = 0; i < n; i++)
    {
        used[cur] = 1;
        printf(" %d", cur + 1);
        EDGE* cur_n = G[cur].adja;
        while (cur_n != NULL)
        {
            if (used[cur_n->to - 1] == 0 && dist[cur_n->to - 1] > cur_n->w)
            {
                dist[cur_n->to - 1] = cur_n->w;
            }
            cur_n = cur_n->next;
        }
        int min_cost = 10000000;
        for (int i = 0; i < n; i++)
        {
            if (used[i] == 0 && min_cost > dist[i])
            {
                min_cost = dist[i];
                cur = i;
            }
        }
    }
    int total = 0;
    for (int i = 0; i < n; i++)
    {
        total += dist[i];
    }
    printf("\n%d", total);
}

int main()
{
    int n = 0, m = 0;
    scanf("%d %d", &n, &m);
    NODE* G = (NODE*)malloc(sizeof(NODE) * n);
    for (int i = 0; i < n; i++)
    {
        G[i].adja = NULL;
    }
    for (int i = 0; i < m; i++)
    {
        int a = 0, b = 0, w = 0;
        scanf("%d %d %d", &a, &b, &w);
        addEDGE_sorted(G, a, b, w);
        addEDGE_sorted(G, b, a, w);
    }
    prim_Jarnik(G, n);
}
