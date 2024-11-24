/*
[ 문제 1 ] (인접리스트 구현) 그림 1의 무방향 가중그래프를 인접리스트로 표현하고, 다음
명령어에 따라 그래프 정보를 출력하거나 그래프를 수정하는 프로그램을 작성하시오. 대화식 프로그램에 주어지는 명령어는 a, m, q 세 가지며 각 명령에 대해 다음과 같이
수행해야 한다. a <node number> : <node number>를 가지는 node와 인접한 node와 그
노드까지의 간선 가중치를 모두 인쇄. 단, node number의
오름차순으로 인쇄하되, space 외의 구분자 없이 노드번호
가중치 노드번호 가중치 ... 형식으로 인쇄한다. 그래프에 정점
a가 존재하지 않으면 아무 것도 하지 않고 –1을 출력한다.
그림 1 무방향 가중그래프
<알고리즘 실습> 그래프 표현- 2 -
m a b w : 간선 (a, b)의 가중치를 w로 변경한다. 그러한 간선이 존재하지 않을 때는
가중치 w인 새로운 간선 (a, b)를 생성한다. w = 0이면 간선 (a, b)를
삭제한다. 그래프에 정점 a 혹은 b가 존재하지 않으면 아무 것도 하지
않고 –1을 출력한다. q : 프로그램 종료
  */

#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable:4996)

typedef struct NODE 
{
    int n;
    struct EDGE* adja;
} NODE;

typedef struct EDGE 
{
    int n;
    int w;
    struct EDGE* next;
} EDGE;

NODE* createGraph(int cnt) 
{
    NODE* G = (NODE*)malloc(sizeof(NODE) * cnt);
    for (int i = 0; i < cnt; i++) 
    {
        G[i].n = i + 1;
        G[i].adja = NULL; // 초기화 필수!
    }
    return G;
}

void remove_EDGE(NODE* G, int from, int to) 
{
    EDGE** cur = &G[from - 1].adja;
    while (*cur != NULL) 
    {
        if ((*cur)->n == to) 
        {
            EDGE* temp = *cur;
            *cur = (*cur)->next;
            free(temp);
            return;
        }
        cur = &(*cur)->next;
    }
}

void modify_G_sorted(NODE* G, int from, int to, int w) 
{
    EDGE** cur = &(G[from - 1].adja);
    EDGE* brandNew = (EDGE*)malloc(sizeof(EDGE));
    brandNew->n = to;
    brandNew->w = w;
    brandNew->next = NULL;

    if ((*cur) == NULL || (*cur)->n > to) 
    { 
        brandNew->next = (*cur);
        *cur = brandNew;
        return;
    }

    while ((*cur) != NULL) 
    {
        if ((*cur)->n == to) 
        {
            (*cur)->w = w;
            free(brandNew);
            return;
        }
        if ((*cur)->next == NULL || (*cur)->next->n > to) 
        {
            break;
        }
        cur = &((*cur)->next);
    }
    brandNew->next = (*cur)->next;
    (*cur)->next = brandNew;
}

void modify_G(NODE* G, int from, int to, int w) 
{
    if (w == 0) 
    {
        remove_EDGE(G, from, to);
        remove_EDGE(G, to, from);
    }
    else {
        modify_G_sorted(G, from, to, w);
        modify_G_sorted(G, to, from, w);
    }
}

void print_adja(NODE* G, int from)
{
    EDGE* temp = G[from - 1].adja;
    while (temp != NULL) 
    {
        printf(" %d %d", temp->n, temp->w);
        temp = temp->next;
    }
    printf("\n");
}

void free_Graph(NODE* G, int cnt) 
{
    for (int i = 0; i < cnt; i++) 
    {
        EDGE* temp = G[i].adja;
        while (temp != NULL) 
        {
            EDGE* next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(G);
}

int main() 
{
    int n = 6;
    NODE* G = createGraph(n);

    modify_G(G, 1, 2, 1);
    modify_G(G, 1, 3, 1);
    modify_G(G, 1, 6, 2);
    modify_G(G, 1, 4, 1);
    modify_G(G, 2, 3, 1);
    modify_G(G, 3, 5, 4);
    modify_G(G, 5, 5, 4);
    modify_G(G, 5, 6, 3); 

    char cmd;
    while (1) 
    {
        scanf(" %c", &cmd);
        switch (cmd) 
        {
        case 'a': 
        {
            int from;
            scanf("%d", &from);
            if (from < 1 || from>6)
            {
                printf("-1\n");
                continue;
            }
            print_adja(G, from);
            break;
        }
        case 'm': 
        {
            int from, to, w;
            scanf("%d %d %d", &from, &to, &w);
            if ((from < 1 || from>6) || (to < 1 || to>6))
            {
                printf("-1\n");
                continue;
            }
            modify_G(G, from, to, w);
            break;
        }
        case 'q': 
        {
            free_Graph(G, n);
            return 0;
        }
        }
    }
}
