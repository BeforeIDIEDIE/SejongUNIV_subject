#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#pragma warning(disable:4996)

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int random(int l, int r)
{
    srand(time(NULL));
    return rand() % (r - l + 1) + l;
}

int partition(int* A, int l, int r, int k)
{
    int pivot = A[k];
    int i = l;
    int j = r - 1;
    swap(&A[r], &A[k]);
    while (i <= j)
    {
        while (i <= j && A[i] <= pivot)
        {
            i++;
        }
        while (i <= j && A[j] >= pivot)
        {
            j--;
        }
        if (i <= j)
        {
            swap(&A[i], &A[j]);
        }
    }
    swap(&A[i], &A[r]);
    return i;
}

void quickSort(int* A, int l, int r)
{
    if (l >= r)
    {
        return;
    }
    int i = partition(A, l, r, random(l,r));
    quickSort(A, l, i - 1);
    quickSort(A, i + 1, r);
}

int main()
{
    int n = 0;
    scanf("%d", &n);
    int* A = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        scanf(" %d", &A[i]);
    }
    quickSort(A, 0, n - 1);
    for (int i = 0; i < n; i++)
    {
        printf(" %d", A[i]);
    }
}
