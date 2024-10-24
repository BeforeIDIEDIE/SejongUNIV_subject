#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#pragma warning(disable: 4996)

void merge(int*A,int l1, int r1, int l2, int r2)
{
    int i1 = l1;
    int i2 = l2;
    int curi = 0;
    int* temp = (int*)malloc(sizeof(int) * (r1 - l1 + 1 + r2 - l2 + 1));
    while (i1 <= r1 && i2 <= r2)//조건 != 쓰지 않기
    {
        if (A[i1] > A[i2])
        {
            temp[curi++] = A[i2++];
        }
        else
        {
            temp[curi++] = A[i1++];
        }
    }
    while (i1 <= r1)//조건 수정 i1 != r1은 틀림
    {
        temp[curi++] = A[i1++];
    }
    while (i2 <= r2)//조건 수정 i2 != r2은 틀림
    {
        temp[curi++] = A[i2++];
    }
    for (int i = 0; i < curi; i++)
    {
        A[i + l1] = temp[i];
    }
    free(temp);//동적할당해제 중요!
}

int partition(int l, int r)
{
    return (l + r) / 2;
}

void mergeSort(int*A, int l, int r)
{
    if (r - l <= 0)
    {
        return;
    }
    int half_floor = partition(l, r);
    mergeSort(A, l, half_floor);
    mergeSort(A, half_floor + 1, r);
    merge(A, l, half_floor, half_floor + 1, r);
}

int main()
{
    int n = 0;
    scanf("%d", &n);
    int* A = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);//scanf에 &붙이는거 중요!
    }
    mergeSort(A, 0, n - 1);
    for (int i = 0; i < n; i++)
    {
        printf(" %d", A[i]);
    }
    free(A);
    return 0;
}
