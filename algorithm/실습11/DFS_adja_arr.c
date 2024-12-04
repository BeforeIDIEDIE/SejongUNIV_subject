#include<stdio.h>

#include<stdlib.h>

#pragma warning(disable:4996)


void DFS(int** adja, int* used, int n, int cur)
{
    for (int i = 0; i < n; i++)
    {
        if (adja[cur - 1][i] != 0&&used[i]!=1)
        {
            used[i] = 1;
            printf("%d\n", i + 1);
            DFS(adja, used, n, i+1);
        }
    }
}

int main()
{
    int n = 0, m = 0, s = 0;
    scanf("%d %d %d", &n, &m, &s);
    int** adja = (int**)calloc(n, sizeof(int*));
    for (int i = 0; i < n; i++)
    {
        adja[i] = (int*)calloc(n, sizeof(int));
    }
    for (int i = 0; i < m; i++)
    {
        int a = 0, b = 0;
        scanf("%d %d", &a, &b);
        adja[a - 1][b - 1] = 1;
        adja[b - 1][a - 1] = 1;
    }
    int* used = (int*)calloc(n, sizeof(int));
    printf("%d\n", s);
    used[s - 1] = 1;
    DFS(adja, used, n, s);
    for (int i = 0; i < n; i++)
    {
        free(adja[i]);
    }
    free(adja);
}
