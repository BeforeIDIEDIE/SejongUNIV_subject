#include<stdio.h>

#include<stdlib.h>

#pragma warning(disable:4996)

void Swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void InsertSort_fromUPToDown(int* L, int n)
{
    for (int i = n - 1; i >= 0; i--)
    {
        int cur_key = L[i];
        int cur_index = i;
        while (i < n - 1 && L[i]>L[i + 1])
        {
            Swap(&L[i], &L[i + 1]);
            i++;
        }
    }
}

void InsertSort_fromDownToUP(int* L, int n)
{
    for (int i = 0; i <= n-1; i++)
    {
        int cur_key = L[i];
        int cur_index = i;
        while (i > 0 && L[i] < L[i - 1])
        {
            Swap(&L[i], &L[i - 1]);
            i--;
        }
    }
}

void printDynamicArray(int* L, int n)//재사용
{
    for (int i = 0; i < n; i++)
    {
        printf(" %d", L[i]);
    }
    printf("\n");
}
int main()
{
    int n = 0;
    scanf("%d", &n);
    int* arr = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    //InsertSort_fromUPToDown(arr, n);
    InsertSort_fromDownToUP(arr, n);
    printDynamicArray(arr, n);
}
