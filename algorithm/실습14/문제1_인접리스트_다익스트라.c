/*
* [ 문제 1 ] (무방향 양의 가중그래프에서 최단거리 찾기) 무방향 양의 가중그래프(undirected 
weighted graph) G와 출발정점이 주어지면, 출발정점에서 다른 모든 정점으로 
가는 최단거리를 구하는 프로그램을 작성하라.
입력 그래프의 성질:
 ◦ n(1 ≤ n ≤ 100)개의 정점과 m(1 ≤ m ≤ 1,000)개의 간선으로 구성.
 ◦ 정점은 1 ~ n 사이의 정수로 번호가 매겨져 있고, 정점의 번호는 모두 다름.
 ◦ 모든 간선은 무방향간선
이다.
입출력:
 ◦ 입력- 첫 줄에 정점의 개수 n, 간선의 개수 m, 출발정점 번호 s가 주어진다.- 이후 m개의 줄에 한 줄에 하나씩 간선의 정보(간선의 양 끝 정점 번호, 무게)가 
주어진다. 최대로 가능한 가중치는 
20
을 넘지 않는다
고 가정한다. 
간선은 임의의 순서로 입력되고, 중복 입력되는 간선은 없다
(무방향간선이므로 간선 
(u, v)와 (v, u)는 동일한 간선으로 취급).
 ◦ 출력- 출발정점 s에서 다른 모든 정점으로의 최단거리를 출력한다. 한 줄에 한 정점과 그 
정점까지의 거리를 출력하되, 출력하는 순서는 정점의 번호의 오름차순으로 출력한다. 
도달할 수 없는 정점은 출력하지 않는다


input
 5 7 1 ↦ n=5, m=7, s=1
 1 2 1
 1 4 5
 5 1 10
 3 5 3
 4 3 1
 3 1 2
 2 3 2

 output
 2 1
 3 2
 4 3
 5 5


 input

  8 12 7 ↦ n=8, m=12, s=7
 1 2 1
 2 4 2
4 7 7
 3 6 1
 6 1 4
 7 6 9
 7 8 1
 1 3 2
 2 7 5
 1 4 1
 2 5 2
 7 5 2

 output
  1 5
 2 4
 3 7
 4 6
 5 2
 6 8
 8 1
*/


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

typedef struct pair
{
    int node;
    int dist;
}pair;

void addEDGE(NODE* G, int from, int to, int w)
{
    EDGE** cur = &(G[from - 1].adja);
    EDGE* brandNew = (EDGE*)malloc(sizeof(EDGE));
    brandNew->next = NULL;
    brandNew->to = to;
    brandNew->w = w;
    brandNew->next = (*cur);
    (*cur) = brandNew;
}

void swap(pair* a, pair* b)
{
    pair temp = *a;
    *a = *b;
    *b = temp;
}

void upheap(pair* h, int idx)
{
    if (idx == 1)
    {
        return;
    }
    if (h[idx].dist < h[idx / 2].dist)
    {
        swap(&h[idx], &h[idx / 2]);
        upheap(h, idx / 2);
    }
}
void downheap(pair* h, int idx, int last)//암기
{
    if (last < idx * 2)
    {
        return;
    }
    if(last< idx*2+1)
    {
        if (h[idx * 2].dist < h[idx].dist)
        {
            swap(&h[idx * 2], &h[idx]);
            return;
        }
    }
    int bigger = idx * 2;
    if (h[bigger].dist < h[bigger + 1].dist)
    {
        bigger += 1;
    }
    if (h[idx].dist > h[bigger].dist)
    {
        swap(&h[idx], &h[bigger]);
        downheap(h, bigger, last);
    }
}

int main()
{
    int n = 0, m = 0, s = 0;
    scanf("%d %d %d", &n, &m, &s);
    NODE* G = (NODE*)malloc(sizeof(NODE)*n);
    for (int i = 0; i < n; i++)
    {
        G[i].adja = NULL;
    }
    for (int i = 0; i < m; i++)
    {
        int a = 0, b = 0, w = 0;
        scanf("%d %d %d", &a, &b, &w);
        addEDGE(G, a, b, w);
        addEDGE(G, b, a, w);
    }
    int* dist = (int*)malloc(sizeof(int)*n);
    for (int i = 0; i < n; i++)
    {
        dist[i] = 100000;
    }
    dist[s - 1] = 0;
    pair* h = (pair*)malloc(sizeof(pair) * m);
    int last = 0;
    pair first;
    first.dist = dist[s - 1];
    first.node = s;
    h[++last] = first;
    while (last > 0)
    {
        pair cur_p = h[1];
        swap(&h[1], &h[last]);
        downheap(h, 1, --last);
        int cur = cur_p.node;
        EDGE* cur_e = G[cur - 1].adja;
        while (cur_e != NULL)
        {
            if (dist[cur_e->to - 1] == 100000)
            {
                pair temp;
                temp.dist = dist[cur - 1] + cur_e->w;
                dist[cur_e->to - 1] = temp.dist;
                temp.node = cur_e->to;
                h[++last] = temp;
                upheap(h, last);
            }
            else if (dist[cur_e->to - 1] > dist[cur - 1] + cur_e->w)
            {
                dist[cur_e->to - 1] = dist[cur - 1] + cur_e->w;
                pair temp;
                temp.dist = dist[cur_e->to - 1];
                temp.node = cur_e->to;
                h[++last] = temp;
                upheap(h, last);
            }
            cur_e = cur_e->next;
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (i == s - 1||dist[i]==100000)//조건 수정
        {
            continue;
        }
        printf("%d %d\n", i + 1, dist[i]);
    }
    free(h);
    free(dist);
}

