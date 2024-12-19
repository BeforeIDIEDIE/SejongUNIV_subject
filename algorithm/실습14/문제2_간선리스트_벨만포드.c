//[문제 2](방향 가중그래프에서 최단거리 찾기) 방향 가중그래프(directed weighted graph)
//G와 출발정점이 주어지면, 출발정점에서 다른 모든 정점으로 가는 최단거리를
//구하는 프로그램을 작성하라.
//입력 그래프의 성질 :
//◦ n(1 ≤ n ≤ 100)개의 정점과 m(1 ≤ m ≤ 1, 000)개의 간선으로 구성.
//◦ 정점은 1 ~n 사이의 정수로 번호가 매겨져 있고, 정점의 번호는 모두 다름.
//◦ 모든 간선은 방향간선이고, 무게를 가진다(음의 가중치도 허용).
//◦ 음의 사이클을 가지는 그래프는 입력되지 않는다고 가정.
//입출력 :
//    ◦ 입력 - 첫 줄에 정점의 개수 n, 간선의 개수 m, 출발정점 번호 s가 주어진다. - 이후 m개의 줄에 한 줄에 하나씩 간선의 정보(간선의 양끝 정점 번호, 무게)가
//    주어진다.가중치의 양의 최대값은 20을 넘지 않는다고 가정한다.
//    <알고리즘 실습> 최단경로 - 간선은 임의의 순서로 입력되고, 중복 입력되는 간선은 없다
//    (방향간선이므로 간선(u,
//        v)와(v, u)는 다른 간선으로
//        ◦ 출력
//        취급) - 출발정점 s에서 다른 모든 정점으로의 최단거리를 출력한다.한 줄에 한 정점과 그
//    정점까지의 거리를 출력하되, 출력하는 순서는 정점의 번호의 오름차순으로 출력한다.
//    도달할 수 없는 정점은 출력하지 않는다


/*
* 
input1
5 7 1
 1 2 1
 1 4 5
 5 1 -2
 3 5 3
 3 4 1
 1 3 2
 3 2 -3

 output1
  2 –1
 3 2
 4 3
 5 5

 input2
 4 5 1
 1 2 1
 2 3 -2
 3 1 2
 3 4 1
 1 4 5
 output2
 2 1
 3 –1
 4 0
*/




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
