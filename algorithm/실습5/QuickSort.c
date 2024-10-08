//주석은 실수한 부분!

#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable:4996)

int findPivot(int first, int end)
{
    srand(time(NULL));

    return rand() % (end - first + 1) + first;//first와 end 순서 좀 생각!
}

void Swap(int* a, int* b)
{
    int* temp = *a;
    *a = *b;
    *b = temp;
}

int inPlacePartition(int* L, int l, int r, int k)
{
    int pivot = L[k];
    Swap(&L[k], &L[r]);
    int i = l, j = r-1;
    while (1)
    {
        while (j >= l&& L[j] > pivot)
        {
            j--;
        }
        while (i <= r - 1 && L[i] < pivot)
        {
            i++;
        }
        if (i >= j)//해당 if문은 여기에 위치해야함->안그러면 바꾸고 난 이후에 반복문이 종료된다.
        {
            break;
        }
        Swap(&L[i],&L[j]);
    }
    Swap(&L[i], &L[r]);//i가 올바른 위치

    return i;//i를 반환!!하도록!
}

void inPlaceQuickSort(int* L, int l, int r)
{
    if (l >= r)
    {
        return;
    }
    int k = findPivot(l, r);
    int pivot = inPlacePartition(L, l, r, k);
    inPlaceQuickSort(L, l, pivot - 1);
    inPlaceQuickSort(L, pivot + 1, r);
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
    inPlaceQuickSort(arr, 0, n - 1);
    printDynamicArray(arr, n);
}
