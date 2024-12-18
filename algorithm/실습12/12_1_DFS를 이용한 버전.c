#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

typedef struct NODE
{
    char id;
    int in;
    struct EDGE* out;
}NODE;

typedef struct EDGE
{
    int to;
    struct EDGE* next;
}EDGE;
int findID(NODE* G, int n, char id)
{
    for (int i = 0; i < n; i++)
    {
        if (G[i].id == id)
        {
            return i;
        }
    }
}

void addEDGE(NODE* G, char from, char to, int n)
{
    int f = findID(G, n, from);
    int t = findID(G, n, to);
    EDGE** cur = &(G[f].out);
    EDGE* brandNew = (EDGE*)malloc(sizeof(EDGE));
    brandNew->next = NULL;
    brandNew->to = t;
    brandNew->next = (*cur);
    (*cur) = brandNew;
    G[t].in++;//해당 부분 누락되어 틀린적 OO
    return;

    //아래조건 필요 없다.
    //if ((*cur) == NULL || (*cur)->to > to)
    //{
    //    brandNew->next = (*cur);
    //    (*cur) = brandNew;
    //    G[t].in++;//해당 부분 누락되어 틀린적 OO
    //    return;
    //}
    //while ((*cur) != NULL)
    //{
    //    if ((*cur)->next == NULL || (*cur)->next->to > t)
    //    {
    //        break;
    //    }
    //    cur = &((*cur)->next);
    //}
    //brandNew->next = (*cur)->next;
    //(*cur)->next = brandNew;
    //G[t].in++;
}

void DFS(NODE* G, int s, int* used, int* order, int* flag,int*num,int n)
{
    if ((*flag) == 1)
    {
        return;
    }
    used[s] = 1;
    EDGE* cur = G[s].out;
    while (cur != NULL)
    {
        if (used[cur->to] == 0)
        {
            DFS(G, cur->to, used, order, flag, num,n);
        }
        else if(used[cur->to]==1)//이 부분
        {
            (*flag) = 1;
            return;
        }
        cur = cur->next;
    }
    used[s] = 2;//이 부분
    order[(*num)--] = s;
}

int main()
{
    int n = 0;
    scanf("%d", &n);
    NODE* G = (NODE*)malloc(sizeof(NODE) * n);
    for (int i = 0; i < n; i++)
    {
        scanf(" %c", &G[i].id);
        G[i].in = 0;
        G[i].out = NULL;
    }
    int m = 0;
    scanf("%d", &m);
    for (int i = 0; i < m; i++)
    {
        char a = 0, b = 0;
        scanf(" %c %c", &a, &b);
        addEDGE(G, a, b, n);
    }
    int front = 0, rear = 0;
    int* used = (int*)malloc(sizeof(int) * n);
    int* order = (int*)malloc(sizeof(int) * n);
    int idx = 0;
    for (int i = 0; i < n; i++)
    {
        used[i] = 0;//초기값 설정할 것
        order[i] = -1; // 초기값 설정
    }
    int flag = 0, num = n-1;
    for (int i = 0; i < n; i++)
    {
        if (flag == 1)
        {
            printf("0");
            return;
        }
        if (used[i] == 0)
        {
            DFS(G, i, used, order, &flag, &num, n);
        }
    }
    for (int i = 0; i < n; i++)
    {
        printf("%c ", G[order[i]].id);
    }
}
