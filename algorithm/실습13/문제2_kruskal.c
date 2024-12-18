/*
[ 문제 2 ] (Kruskal 알고리즘) 입력으로 주어지는 그래프를 Kruskal 알고리즘을 이용하여
최소신장트리(Minimum Spanning Tree, MST)를 생성하는 프로그램을 작성하고, 최소신장트리의 생성 과정과 총무게를 결과로 출력하시오. 입력 그래프의 성질:
◦ 문제 1의 입력 그래프의 성질과 동일하다. 구현 조건:
◦ Kruskal 알고리즘 구현 시, 우선순위 큐와 분리집합의 구현이 필요할 수 있다. 분리집합은
교재 4.6절에 간략히 설명되어 있으며 상세한 내용은 데이터구조 교재를 참고하라. 입출력:
◦ 입력
입력 예시 출력 예시
5 7
1 2 1
1 4 2
1 5 4
2 5 7
4 5 3
3 5 5
2 3 6
↦ n = 5, m = 7
↦ 정점, 정점, 무게
□1 2 4 5 3
11
↦ MST 생성시 추가되는 정점
↦ MST 총무게
<알고리즘 실습> 최소신장트리- 3 -
- 문제 1의 입력과 동일하다. ◦ 출력
 - 최소신장트리(MST) 생성 과정에서 추가되는 간선의 무게를 순서대로 출력한다. - 모든 간선의 무게를 출력한 후, 마지막 줄에 MST 간선 비용의 합 즉, 총무게를 출력한다.
입력 예시2 출력 예시2
5 7
1 2 75
1 4 95
1 3 51
2 4 9
4 3 19
4 5 42
3 5 31
↦ n = 5, m = 7
↦ 정점, 정점, 무게
□9 19 31 51
110
↦ MST 간선 무게
↦ MST 총무게
입력 예시1 출력 예시1
6 9
1 2 3
1 3 20
2 4 25
2 5 17
3 4 34
3 5 1
3 6 12
4 5 5
5 6 37
↦ n = 6, m = 9
↦ 정점, 정점, 무게
□1 3 5 12 17
38
↦ MST 간선 무게
↦ MST 총무게
*/

#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)

#define min(a, b) (a>b?b:a)
#define max(a,b) (a>b?a:b)


typedef struct EDGE
{
    int a, b, w;
    struct EDGE* next;
}EDGE;

void sort_edge(EDGE* l, int m)
{
    for (int i = 1; i < m; i++)
    {
        EDGE save = l[i];
        int idx = i-1;
        while (idx >= 0 && save.w < l[idx].w)//조건!
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
        p[idx] = findP(p,p[idx]);
    }
    return p[idx];
}


int main()
{
    int n = 0, m = 0;
    scanf("%d %d", &n, &m);
    EDGE* edgeL = (EDGE*)malloc(sizeof(EDGE) * m);
    for (int i = 0; i < m; i++)
    {
        int a = 0, b = 0,w = 0;
        scanf("%d %d %d", &a, &b,&w);
        edgeL[i].a = min(a, b) -1;//0베이스
        edgeL[i].b = max(a, b) -1;//0베이스!
        edgeL[i].w = w;
    }
    sort_edge(edgeL, m);
    int total = 0;
    //kruskal
    int* parent = (int*)malloc(sizeof(int)*n);
    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
    }
    for (int i = 0; i < m; i++)
    {
        int pa = findP(parent, edgeL[i].a);
        int pb = findP(parent, edgeL[i].b);
        if (pa !=pb)
        {
            int minP = min(pa, pb);
            parent[max(pa, pb)] = minP;
            printf(" %d", edgeL[i].w);
            total += edgeL[i].w;
        }
    }
    printf("\n%d", total);
}
