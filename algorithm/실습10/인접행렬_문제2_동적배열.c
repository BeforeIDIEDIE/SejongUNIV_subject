#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable:4996)

void modifyGraph(int** arr, int a, int b, int w) 
{
    arr[a - 1][b - 1] = w;
    arr[b - 1][a - 1] = w;
}

void printNODE(int** arr, int a) 
{
    for (int i = 0; i < 6; i++) 
    {
        if (arr[a - 1][i] == 0) 
        {
            continue;
        }
        printf(" %d %d", i + 1, arr[a - 1][i]);
    }
    printf("\n");
}

int main() 
{
    int** arr = (int**)calloc(6, sizeof(int*));
    for (int i = 0; i < 6; i++) 
    {
        arr[i] = (int*)calloc(6, sizeof(int));
    }


    int init[6][6] = 
    {
        {0, 1, 1, 1, 0, 2},
        {1, 0, 1, 0, 0, 0},
        {1, 1, 0, 0, 4, 0},
        {1, 0, 0, 0, 0, 0},
        {0, 0, 4, 0, 4, 3},
        {2, 0, 0, 0, 3, 0}
    };

    for (int i = 0; i < 6; i++) 
    {
        for (int j = 0; j < 6; j++) 
        {
            arr[i][j] = init[i][j];
        }
    }

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
            // 메모리 해제
            for (int i = 0; i < 6; i++) 
            {
                free(arr[i]);
            }
            free(arr);
            return 0;
        }
        }
    }
}
