/*
[ 문제 2 ] (인접행렬 구현) 그림 1의 무방향 가중그래프를 인접행렬로 표현하고, 명령어에 따라
그래프 정보를 인쇄하거나 그래프를 수정하는 프로그램을 작성하시오. 명령어 정의와
입출력 예시는 문제 1과 같다.
*/

#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable:4996)

void modifyGraph(int arr[6][6], int a,int b,int w)
{
    arr[a - 1][b - 1] = w;
    arr[b - 1][a - 1] = w;
}

void printNODE(int arr[6][6], int a)
{
    for (int i = 0; i < 6; i++)
    {
        if (arr[a - 1][i] == 0)
        {
            continue;
        }
        printf(" %d %d",i+1,arr[a-1][i]);
    }
    printf("\n");
}

int main()
{
    /*int** arr = (int**)calloc(6, sizeof(int*));
    for (int i = 0; i < 6; i++)
    {
        arr[i] = (int*)calloc(6, sizeof(int));
    }*/

    int arr[6][6] = { {0,1,1,1,0,2},{1,0,1,0,0,0},{1,1,0,0,4,0},{1,0,0,0,0,0},{0,0,4,0,4,3},{2,0,0,0,3,0} };
    while (1)
    {
        char cmd = 0;
        scanf(" %c", &cmd);
        switch (cmd)
        {
        case 'a':
        {
            int a = 0;
            scanf("%d", &a);
            if (a > 6 || a < 1)
            {
                printf("-1\n");
                continue;
            }
            printNODE(arr, a);
            break;
        }
        case 'm':
        {
            int a = 0, b = 0, w = 0;
            scanf("%d %d %d", &a, &b, &w);
            if (a > 6 || a < 1 || b > 6 || b < 1)
            {
                printf("-1\n");
                continue;
            }
            modifyGraph(arr, a, b, w);
            break;
        }
        case 'q':
        {
            return;
            break;
        }
        }
    }
}
