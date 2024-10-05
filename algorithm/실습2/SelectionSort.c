#include<stdio.h>

#include<stdlib.h>

#pragma warning(disable:4996)

void Swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    
    //해당 방법과 같이 비트를 교환하는 방법도 가능하다.
    /*
    if(a!=b)
    {
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
    }
    */
}

void printDynamicArray(int* L, int n)//재사용
{
    for (int i = 0; i < n; i++)
    {
        printf(" %d", L[i]);
    }
    printf("\n");
}

void InsertSort(int* L, int n)//제자리 정렬
{
    for (int i = n-1; i > 0; i--)
    {
        int cur_Max = L[i], cur_Max_idx = i;
        for (int j = 0; j <i; j++)
        {
            if (cur_Max < L[j])
            {
                cur_Max = L[j];
                cur_Max_idx = j;
            }
        }
        Swap(&L[i], &L[cur_Max_idx]);
        //printDynamicArray(L, n);//디버깅 용
    }
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
    InsertSort(arr, n);
    printDynamicArray(arr, n);
}
