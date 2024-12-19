
//메모리 누수는 고려 안함


//인접리스트 구현

#include<stdio.h>
#include<stdlib.h>

#pragma warning(disable:4996)

typedef struct NODE
{
    struct EDGE* adja;
}NODE;

typedef struct EDGE
{
    int to;
    int w;
    struct EDGE* next;
}EDGE;


void addEDGE_sorted(NODE* G, int from, int to, int w)
{
    EDGE** cur = &(G[from - 1].adja);
    EDGE* brandNew = (EDGE*)malloc(sizeof(EDGE));
    brandNew->next = NULL;
    brandNew->to = to;
    brandNew->w = w;
    if ((*cur) == NULL || (*cur)->to > to)
    {
        brandNew->next = (*cur);
        (*cur) = brandNew;
        return;
    }
    while ((*cur) != NULL)
    {
        if ((*cur)->to == to)
        {
            (*cur)->w = w;
            free(brandNew);
            return;
        }
        if ((*cur)->next == NULL || (*cur)->next->to > to)
        {
            break;
        }
        cur = &(*cur)->next;
    }
    brandNew->next = (*cur)->next;
    (*cur)->next = brandNew;
}

void removeEDGE(NODE* G, int from, int to)
{
    EDGE** cur = &(G[from - 1].adja);
    if ((*cur) != NULL && (*cur)->to == to)
    {
        EDGE* temp = (*cur);
        (*cur) = (*cur)->next;
        free(temp);
        return;
    }
    while ((*cur) != NULL)
    {
        if ((*cur)->next != NULL && (*cur)->next->to == to)
        {
            EDGE* temp = (*cur)->next;
            (*cur)->next = (*cur)->next->next;
            free(temp);
            return;
        }
        cur = &((*cur)->next);
    }
}

void addEDGE(NODE* G, int a, int b, int w)
{
    if (w == 0)
    {
        removeEDGE(G, a, b);
        removeEDGE(G, b, a);
        return;
    }
    addEDGE_sorted(G, a, b, w);
    addEDGE_sorted(G, b, a, w);
}
void print_node(NODE* G, int idx)
{
    EDGE* cur = G[idx - 1].adja;
    while (cur != NULL)
    {
        printf(" %d %d", cur->to, cur->w);
        cur = cur->next;
    }
    printf("\n");
}

void free_all(NODE* G, int n)
{
    for (int i = 0; i < n; i++)
    {
        EDGE* cur = G[i].adja;
        while (cur != NULL)
        {
            EDGE* temp = cur->next;
            free(cur);
            cur = temp;
        }
    }
    free(G);
}

int main()
{
    int n = 6;
    NODE* G = (NODE*)malloc(sizeof(NODE) * n);
    for (int i = 0; i < n; i++)
    {
        G[i].adja = NULL;
    }
    char cmd = 0;
    addEDGE(G, 1, 2, 1);
    addEDGE(G, 1, 3, 1);
    addEDGE(G, 1, 4, 1);
    addEDGE(G, 1, 6, 2);
    addEDGE(G, 2, 3, 1);
    addEDGE(G, 5, 5, 4);
    addEDGE(G, 6, 5, 3);
    addEDGE(G, 3, 5, 4);
    while (1)
    {
        scanf(" %c", &cmd);
        switch (cmd)
        {
        case 'a':
        {
            int input = 0;
            scanf("%d", &input);
            if (input >= 1 && input <= 6)
            {
                print_node(G, input);
            }
            else
            {
                printf("-1\n");
            }
            break;
        }
        case 'm':
        {
            int input1 = 0, input2 = 0, w = 0;
            scanf("%d %d %d", &input1, &input2, &w);
            if ((input1 >= 1 && input1 <= 6) && (input2 >= 1 && input2 <= 6))
            {
                addEDGE(G, input1, input2, w);
            }
            else
            {
                printf("-1\n");
            }
            break;
        }
        case 'q':
        {
            free_all(G, n);
            return;
            break;
        }
        }
    }
}


//방향그래프_진입차수ver
#include<stdio.h>
#include<stdlib.h>

#pragma warning(disable:4996)


typedef struct NODE
{
    char c;
    struct EDGE* adja;
    int in;
}NODE;

typedef struct EDGE
{
    int to;
    struct EDGE* next;
}EDGE;

int findC(NODE* G, char c, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (c == G[i].c)
        {
            return i;
        }
    }
}

void addEDGE(NODE* G, char from, char to, int n)
{
    int f = findC(G, from, n);
    int t = findC(G, to, n);
    EDGE** cur = &(G[f].adja);
    EDGE* brandNew = (EDGE*)malloc(sizeof(EDGE));
    brandNew->next = (*cur);
    brandNew->to = t + 1;
    (*cur) = brandNew;
    G[t].in++;//to가 아님!
}

int main()
{
    int n = 0;
    scanf("%d", &n);
    NODE* G = (NODE*)malloc(sizeof(NODE) * n);
    for (int i = 0; i < n; i++)
    {
        scanf(" %c", &G[i].c);
        G[i].adja = NULL;
        G[i].in = 0;
    }
    int m = 0;
    scanf("%d", &m);
    for (int i = 0; i < m; i++)
    {
        char a = 0, b = 0;
        scanf(" %c %c", &a, &b);
        addEDGE(G, a, b, n);
    }
    //여기부터 topological order
    int* order = (int*)malloc(sizeof(int) * n);
    int* Q = (int*)malloc(sizeof(int) * n);
    int front = 0, rear = 0, idx = 0;
    for (int i = 0; i < n; i++)
    {
        if (G[i].in == 0)
        {
            Q[rear++] = i;
        }
    }
    while (rear > front)
    {
        int cur = Q[front++];
        order[idx++] = cur;
        EDGE* cur_n = G[cur].adja;
        while (cur_n != NULL)
        {
            G[cur_n->to - 1].in--;
            if (G[cur_n->to - 1].in == 0)
            {
                Q[rear++] = cur_n->to - 1;
            }
            cur_n = cur_n->next;
        }
    }
    if (idx < n)
    {
        printf("0");
        return;
    }
    for (int i = 0; i < n; i++)
    {
        printf("%c ", G[order[i]].c);
    }
}
/*
3
A B C
3
A B
C A
C B
*/

//방향그래프_DFS응용
#include<stdio.h>
#include<stdlib.h>

#pragma warning(disable:4996)


typedef struct NODE
{
    char c;
    struct EDGE* adja;
}NODE;

typedef struct EDGE
{
    int to;
    struct EDGE* next;
}EDGE;

int findC(NODE* G, char c, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (c == G[i].c)
        {
            return i;
        }
    }
}

void addEDGE(NODE* G, char from, char to, int n)
{
    int f = findC(G, from, n);
    int t = findC(G, to, n);
    EDGE** cur = &(G[f].adja);
    EDGE* brandNew = (EDGE*)malloc(sizeof(EDGE));
    brandNew->next = (*cur);
    brandNew->to = t + 1;
    (*cur) = brandNew;
}

void DFS(NODE* G, int c, int* flag, int* order, int* used, int* ordering)
{
    if ((*flag) == 1)
    {
        return;
    }
    used[c - 1] = 1;
    EDGE* cur = G[c - 1].adja;
    while (cur != NULL)
    {
        if (used[cur->to - 1] == 0)
        {
            DFS(G, cur->to, flag, order, used, ordering);
        }
        else if (used[cur->to - 1] == 1)
        {
            (*flag) = 1;
            return;
        }
        cur = cur->next;
    }
    order[--(*ordering)] = c - 1;
    used[c - 1] = 2;
}

int main()
{
    int n = 0;
    scanf("%d", &n);
    NODE* G = (NODE*)malloc(sizeof(NODE) * n);
    for (int i = 0; i < n; i++)
    {
        scanf(" %c", &G[i].c);
        G[i].adja = NULL;
    }
    int m = 0;
    scanf("%d", &m);
    for (int i = 0; i < m; i++)
    {
        char a = 0, b = 0;
        scanf(" %c %c", &a, &b);
        addEDGE(G, a, b, n);
    }
    //여기부터 topological order
    int ordering = n, flag = 0;
    int* used = (int*)malloc(sizeof(int) * n);
    int* order = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        used[i] = 0;
        order[i] = -1;
    }
    for (int i = 0; i < n; i++)
    {
        if (used[i] == 0)
        {
            DFS(G, i + 1, &flag, order, used, &ordering);
        }
        if (flag == 1)
        {
            printf("0");
            return;
        }
    }
    for (int i = 0; i < n; i++)
    {
        printf("%c ", G[order[i]].c);
    }
}
/*
3
A B C
3
A B
C A
C B
*/
//prim_jarnik
#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)
#define max(a,b) (a>b?a:b)
#define min(a,b) (a>b?b:a)


typedef struct NODE
{
    struct EDGE* adja;
}NODE;

typedef struct EDGE
{
    int to;
    int w;
    struct EDGE* next;
}EDGE;

void addEDGE(NODE* G, int from, int to, int w)
{
    EDGE** cur = &(G[from - 1].adja);
    EDGE* brandNew = (EDGE*)malloc(sizeof(EDGE));
    brandNew->next = (*cur);
    brandNew->to = to;
    brandNew->w = w;
    (*cur) = brandNew;
}

int main()
{
    int n = 0, m = 0;
    scanf("%d %d", &n, &m);
    NODE* G = (NODE*)malloc(sizeof(NODE) * n);
    int* dist = (int*)malloc(sizeof(int) * n);
    int* used = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        G[i].adja = NULL;
        dist[i] = 100000;
        used[i] = 0;
    }
    for (int i = 0; i < m; i++)
    {
        int a = 0, b = 0, w = 0;
        scanf("%d %d %d", &a, &b, &w);
        addEDGE(G, a, b, w);
        addEDGE(G, b, a, w);
    }

    int cn = 1;
    dist[cn - 1] = 0;
    for (int i = 0; i < n; i++)
    {
        printf(" %d", cn);
        EDGE* cur = G[cn - 1].adja;
        used[cn - 1] = 1;
        while (cur != NULL)
        {
            if (used[cur->to - 1] == 0 && dist[cur->to - 1] > cur->w)
            {
                dist[cur->to - 1] = cur->w;
            }
            cur = cur->next;
        }
        int minC = 100000;
        for (int i = 0; i < n; i++)
        {
            if (used[i] == 0 && minC > dist[i])
            {
                cn = i + 1;
                minC = dist[i];
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
//kruskal
#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)
#define max(a,b) (a>b?a:b)
#define min(a,b) (a>b?b:a)

typedef struct EDGE
{
    int a, b, w;
}EDGE;

void sort(EDGE* l, int m)
{
    for (int i = 1; i < m; i++)
    {
        EDGE save = l[i];
        int idx = i - 1;
        while (idx >= 0 && l[idx].w > save.w)
        {
            l[idx + 1] = l[idx];
            idx--;
        }
        l[idx + 1] = save;
    }
}
int findP(int* p, int idx)
{
    if (p[idx] != idx)
    {
        p[idx] = findP(p, p[idx]);
    }
    return p[idx];
}

int main()
{
    int n = 0, m = 0, s = 0;
    scanf("%d %d", &n, &m);
    EDGE* l = (EDGE*)malloc(sizeof(EDGE) * m);
    for (int i = 0; i < m; i++)
    {
        int a = 0, b = 0, w = 0;
        scanf("%d %d %d", &a, &b, &w);
        l[i].a = min(a, b);
        l[i].b = max(a, b);
        l[i].w = w;
    }
    sort(l, m);
    int* parent = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
    }
    int total = 0;
    for (int i = 0; i < m; i++)
    {
        int pa = findP(parent, l[i].a - 1);
        int pb = findP(parent, l[i].b - 1);
        if (pa != pb)
        {
            printf(" %d", l[i].w);
            total += l[i].w;
            parent[pa] = pb;
        }
    }
    printf("\n%d", total);
}
//다익스트라
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

void downHeap(pair* h, int idx, int last)
{
    if (last < idx * 2 + 1)
    {
        int bigger = idx * 2;
        if (last < idx * 2)
        {
            return;
        }
        if (h[idx].dist > h[idx * 2].dist)
        {
            swap(&h[idx * 2], &h[idx]);
        }
        return;
    }
    int bigger = idx * 2;
    if (h[bigger].dist < h[bigger + 1].dist)
    {
        bigger += 1;
    }
    if (h[bigger].dist < h[idx].dist)
    {
        swap(&h[idx], &h[bigger]);
        downHeap(h, bigger, last);
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
        int a = 0, b = 0, w = 0;
        scanf("%d %d %d", &a, &b, &w);
        addEDGE(G, a, b, w);
        addEDGE(G, b, a, w);
    }
    pair* h = (pair*)malloc(sizeof(pair) * m);
    int* dist = (int*)malloc(sizeof(int) * n);
    int last = 0;
    for (int i = 0; i < n; i++)
    {
        dist[i] = 100000;
    }
    pair first;
    dist[s - 1] = 0;
    first.dist = 0;
    first.node = s;
    h[++last] = first;
    while (last > 0)
    {
        pair cur = h[1];
        swap(&h[1], &h[last]);
        downHeap(h, 1, --last);
        EDGE* cur_e = G[cur.node - 1].adja;
        while (cur_e != NULL)
        {
            if (dist[cur_e->to - 1] == 100000)
            {
                dist[cur_e->to - 1] = cur_e->w + dist[cur.node - 1];
                pair temp;
                temp.dist = cur_e->w + dist[cur.node - 1];
                temp.node = cur_e->to;//1베이스
                h[++last] = temp;
                upheap(h, last);
            }
            else if (dist[cur_e->to - 1] > dist[cur.node - 1] + cur_e->w)
            {
                dist[cur_e->to - 1] = dist[cur.node - 1] + cur_e->w;
                pair temp;
                temp.dist = dist[cur_e->to - 1];
                temp.node = cur_e->to;//1베이스
                h[++last] = temp;
                upheap(h, last);
            }
            cur_e = cur_e->next;
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (i == s - 1 || dist[i] == 100000)
        {
            continue;
        }
        printf("%d %d\n", i + 1, dist[i]);
    }
}
//벨만포드
#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)
#define min(a,b) (a>b?b:a)
typedef struct EDGE
{
    int from;
    int to;
    int w;
}EDGE;
int main()
{
    int n = 0, m = 0, s = 0;
    scanf("%d %d %d", &n, &m, &s);
    int* dist = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        dist[i] = 100000;
    }
    EDGE* list = (EDGE*)malloc(sizeof(EDGE) * m);
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &list[i].from, &list[i].to, &list[i].w);
    }
    dist[s - 1] = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (dist[list[j].from - 1] == 100000) continue;//해당 조건 필요!
            dist[list[j].to - 1] = min(dist[list[j].to - 1], dist[list[j].from - 1] + list[j].w);
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (i == s - 1 || dist[i] == 100000)
        {
            continue;
        }
        printf("%d %d\n", i + 1, dist[i]);
    }
}
