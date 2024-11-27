//[문제 2](BFS) 입력으로 주어지는 그래프의 BFS 순회 결과를 출력하는 프로그램을 작성하시오.
//입력 그래프의 성질 :
//◦ 문제 1과 동일
//구현 조건 :
//◦ 그래프는 인접행렬 구조
//를 사용하여 표현해야 한다.
//◦ 인접 정점의 조사 순서 - 문제 1과 동일하게 정점의 인접 정점(or 부착 간선)들을 번호가 작은 정점부터 조사
//한다.
//입출력 :
//    ◦ 입력 : 문제 1과 동일
//    ◦ 출력 : 출발정점 s에서 출발하는 BFS의 방문 순서대로 정점 번호를 출력한다. - 2
//    < 알고리즘 실습 > 그래프 순회
//    입력 예시 1
//    6 9 1 ↦ n = 6, m = 9, s = 1
//    3 5
//    1 3
//    4 1
//    2 3
//    3 4
//    6 4
//    3 6
//    1 2
//    2 5
//    출력 예시 1
//    1
//    2
//    3
//    4
//    5
//    6
//    입력 예시 2
//    8 12 4 ↦ n = 8, m = 12, s = 4
//    1 2
//    2 4
//    4 7
//    3 6
//    6 1
//    7 6
//    7 8
//    1 3
//    2 7
//    1 4
//    2 5
//    7 5
//    출력 예시 2
//    4
//    1
//    2
//    7
//    3
//    6
//    5
//    8

#include<stdio.h>

#include<stdlib.h>

#pragma warning(disable:4996)

int main()
{
    int n = 0, m = 0, s = 0;
    scanf("%d %d %d", &n, &m, &s);
    
    int** adja_arr = (int**)calloc(n, sizeof(int*));

    for (int i = 0; i < n; i++)
    {
        adja_arr[i] = (int*)calloc(n, sizeof(int));
    }

    for (int i = 0; i < m; i++)
    {
        int a = 0, b = 0;
        scanf("%d %d", &a, &b);
        adja_arr[a - 1][b - 1] = 1;
        adja_arr[b - 1][a - 1] = 1;
    }

    int* used = (int*)calloc(n, sizeof(int));
    int* Q = (int*)calloc(n+1, sizeof(int));
    int front = 0, rear = 0;
    Q[rear++] = s;
    used[s - 1] = 1;

    while (rear > front)
    {
        int cur = Q[front++];
        printf("%d\n", cur);
        //used[cur - 1] = 1;//여기 아님
        for (int i = 0; i < n; i++)
        {
            if (adja_arr[cur - 1][i] == 1 && used[i] == 0)
            {
                Q[rear++] = i+1;
                used[i] = 1;
            }
        }
    }
}
