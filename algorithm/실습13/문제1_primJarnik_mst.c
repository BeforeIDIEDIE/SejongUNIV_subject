/*
 [ 문제 1 ] (Prim-Jarnik 알고리즘) 입력으로 주어지는 그래프를 Prim-Jarnik 알고리즘을 이용하여
최소신장트리(Minimum Spanning Tree, MST)를 생성하는 프로그램을 작성하고,
최소신장트리의 생성 과정과 총무게를 결과로 출력하시오.
입력 그래프의 성질:
 ◦ n (1 ≤ n ≤ 100) 개의 정점과 m (1 ≤ m ≤ 1,000) 개의 간선으로 구성된다.
 ◦ 정점은 1 ~ n 사이의 정수로 번호가 매겨져 있고, 정점의 번호는 모두 다르다.
 ◦ 모든 간선은 무방향간선이고, 한 정점에서 임의의 다른 정점으로 가는 경로는 반드시존재한다.
 ◦ 간선의 무게는 중복이 없는양의 정수다.

 주의:
◦ 알고리즘 수행의 출발정점은 번호가 가장 빠른 정점인 1부터 시작한다.- Prim-Jarnik 알고리즘의 첫 출발정점은 그래프 내 아무 정점이라도 무방하지만, 이번
실습에서는 번호가 가장 빠른 정점인 1에서 출발해야 OJ 시스템의 정답과 일치시킬 수 있다.

입출력:
 ◦ 입력- 첫 줄에 정점의 개수 n, 간선의 개수 m이 주어진다.- 1
<알고리즘 실습> 최소신장트리- 이후 m개의 줄에 한 줄에 하나씩 간선의 정보(간선의 양끝 정점 번호와 무게)가 주어진다.
간선은 임의의 순서로 입력되고, 중복 입력되는 간선은 없다.
 (무방향간선이므로 간선 (u, v)와 (v, u)는 동일한 간선으로 취급)- 무게로는 양의 정수가 입력되고, 중복되는 무게는 없다.
 ◦ 출력- 모든 정점의 번호를 출력한 후, 마지막 줄에 MST 간선 무게의 합 즉, 총무게를 출력한다.
입력 예시
5 7
 1 2 1
 1 4 2
 1 5 4
 2 5 7
 4 5 3
 3 5 5
 2 3 6
출력 예시
□1 2 4 5 3
 11
*/

#include<stdio.h>

#include<stdlib.h>

#pragma warning(disable: 4996)

void primJarnik_mst(int** arr, int n)
{
    int* used = (int*)calloc((n), sizeof(int));
    int* dist = (int*)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++)
    {
        dist[i] = 100000;//-1이 아닌 이렇게!
    }

    int cur = 1;
    dist[cur - 1] = 0;

    for (int i = 0; i < n; i++)
    {
        printf(" %d", cur);
        used[cur - 1] = 1;
        for (int j = 0; j < n; j++)
        {
            if (used[j] == 0 && arr[cur - 1][j] != 0 && arr[cur - 1][j] < dist[j])//조건 수정
            {
                dist[j] = arr[cur - 1][j];
            }
        }
        int min = 10000;
        for (int j = 0; j < n; j++)
        {
            if (used[j] == 0 && dist[j] < min)//조건 수정
            {
                cur = j+1;
                min = dist[j];
            }
        }
    }
    int total = 0;
    for (int i = 0; i < n; i++)
    {
        total += dist[i];
    }
    printf("\n%d", total);
    free(used);
    free(dist);
}

int main()
{
    int n = 0, m = 0;
    scanf("%d %d", &n, &m);

    int** arr = (int**)calloc(n, sizeof(int*));
    for (int i = 0; i < n; i++)
    {
        arr[i] = (int*)calloc(n, sizeof(int));
    }
    for (int i = 0; i < m; i++)
    {
        int a = 0, b = 0, w = 0;
        scanf("%d %d %d", &a, &b, &w);
        arr[a - 1][b - 1] = w;
        arr[b - 1][a - 1] = w;
    }
    primJarnik_mst(arr, n);
    free(arr);
}
