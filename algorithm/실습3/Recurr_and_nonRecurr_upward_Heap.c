#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

int* H;
int n = 0;

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void downHeap(int i)
{
    int larger;
    if (i * 2 > n)
    {
        return;
    }
    if (i * 2 == n)
    {
        larger = i * 2;
    }
    else
    {
        larger = (H[i * 2] > H[i * 2 + 1]) ? i * 2 : i * 2 + 1;
    }
    if (H[i] < H[larger])
    {
        swap(&H[i], &H[larger]);
        downHeap(larger);
    }
}

void buildHeap()
{
    for (int i = n / 2; i >= 1; i--)
    {
        downHeap(i);
    }
}

void rBuildHeap(int i)
{
    if (i > n)
    {
        return;
    }
    rBuildHeap(2 * i);
    rBuildHeap(2 * i + 1);
    downHeap(i);
}

void printHeap()
{
    for (int i = 1; i <= n; i++)
    {
        printf(" %d", H[i]);
    }
    printf("\n");
}

int main()
{
    H = (int*)malloc(sizeof(int) * 101);

    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &H[i]);
    }

    rBuildHeap(1);

    printHeap();

    free(H);
    return 0;
}
