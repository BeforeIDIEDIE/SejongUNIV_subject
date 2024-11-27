//[문제 1](DFS) 입력으로 주어지는 그래프의 DFS 순회 결과를 출력하는 프로그램을 작성하시오.
//입력 그래프의 성질 :
//◦ n(1 ≤ n ≤ 100) 개의 정점과 m(1 ≤ m ≤ 1, 000) 개의 간선으로 구성
//◦ 정점은 1 ~n 사이의 정수로 번호가 매겨져 있고, 정점의 번호는 모두 다름
//◦ 모든 간선은 무방향 간선
//이고, 한 정점에서 임의의 다른 정점으로 가는 경로는 반드시 존재
//구현 조건 :
//◦ 그래프는 인접리스트 구조
//를 사용하여 표현해야 한다.
//◦ 인접 정점의 조사 순서 - 정점 u의 인접 정점(or 부착 간선)들을 번호가 작은 정점부터 조사
//한다.
//(즉, 아래 DFS 의사 코드의 for 문(☚)에서 인접 정점들을 번호가 작은 정점부터 큰
//    순서대로 조사하라.조사 순서에 따라 방문 결과가 달라질 수 있음에 유의할 것)
//    DFS(u)
//{
//    u 방문;
//    for u의 인접 정점들 w에 대해서
//        ☚
//        if (w를 아직 방문하지 않았으면)
//            DFS(w);
//}
//입출력:
//◦ 입력 - 첫 줄에 정점의 개수 n, 간선의 개수 m, 순회 시작 정점 번호 s가 주어진다. - 이후 m개의 줄에 한 줄에 하나씩 간선의 정보(간선의 양 끝 정점 번호)가 주어진다.
//간선은 임의의 순서로 입력되고, 중복 입력되는 간선은 없다.
//(무방향 간선이므로 간선(u, v)와(v, u)는 동일한 간선으로 취급)
//◦ 출력 - 출발정점 s에서 출발하는 DFS의 방문 순서대로 정점 번호를 출력한다. - 1
//< 알고리즘 실습 > 그래프 순회
//입력 예시 1
//5 7 1 ↦ n = 5, m = 7, s = 1
//1 2
//1 4
//5 1
//3 5
//4 3
//3 1
//2 3
//출력 예시 1
//1
//2
//3
//4
//5
//입력 예시 2
//8 12 7 ↦ n = 8, m = 12, s = 7
//1 2
//2 4
//4 7
//3 6
//6 1
//7 6
//7 8
//1 3
//2 7
//1 4
//2 5
//7 5
//출력 예시 2
//7
//2
//1
//3
//6
//4
//5
//8


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


NODE* createEdge(int n)
{
    NODE* G = (NODE*)malloc(sizeof(NODE) * (n+1));
    for (int i = 1; i <= n; i++)
    {
        G[i].adja = NULL;
        G[i].num = i;
    }
    return G;
}

void addEDGE_sort(NODE*G,int from, int to)
{
    EDGE** cur = &(G[from].adja);
    EDGE* brandNew = (NODE*)malloc(sizeof(NODE));
    brandNew->next = NULL;
    brandNew->to = to;
    if ((*cur) == NULL || (*cur)->to > to)
    {
        brandNew->next = (*cur);
        (*cur) = brandNew;
        return;
    }
    while ((*cur)->next != NULL && (*cur)->next->to < to)//부등식 기억!!!
    {
        cur = &((*cur)->next);
    }
    brandNew->next = (*cur)->next;
    (*cur)->next = brandNew;
}

//간선 관계를 파악하는 함수- testing~
void print_rel(NODE* G, int n)
{
    for (int i = 1; i <= n; i++)
    {
        printf("%d : ", i);
        EDGE* temp = G[i].adja;
        while (temp != NULL)
        {
            printf(" %d", temp->to);
            temp = temp->next;
        }
        printf("\n");
    }
}

void DFS(NODE* G, int used_cnt, int* arr, int n, int s)
{
    if (used_cnt == n)
    {
        return;
    }
    EDGE* cur = G[s].adja;  
    while (cur != NULL)
    {
        int cur_searching = cur->to;
        if (arr[cur_searching - 1] == 0)
        {
            printf("%d\n", cur_searching);
            arr[cur_searching - 1] = 1;
            DFS(G, used_cnt + 1, arr, n, cur_searching);
        }
        cur = cur->next;
    }
    
}

int main()
{
    int n = 0, m = 0, s = 0;
    scanf("%d %d %d", &n, &m, &s);
    NODE* G = createEdge(n);
    for (int i = 0; i < m; i++)
    {
        int a = 0, b = 0;
        scanf("%d %d", &a, &b);
        addEDGE_sort(G, a, b);
        addEDGE_sort(G, b, a);
    }
    //print_rel(G, n);

    int* DFS_used = (int*)calloc(n, sizeof(int));
    DFS_used[s - 1] = 1;
    int used_cnt = 1;
    printf("%d\n", s);
    DFS(G, used_cnt, DFS_used, n, s);
}
