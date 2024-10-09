#include<stdio.h>

#include<stdlib.h>

#pragma warning(disable:4996)

int BinarySearch(int* L, int l, int r, int value)
{
    if (l > r)
    {
        return r;
    }

    int half = (l + r) / 2;
    if (L[half] > value)
    {
        return BinarySearch(L, l, half - 1, value);
    }
    else if (L[half] < value)
    {
        return BinarySearch(L, half + 1, r, value);
    }
    else
    {
        return half;
    }
}


int main()
{
    int n = 0, target = 0;
    scanf("%d %d", &n, &target);

    int* arr = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    printf(" %d", BinarySearch(arr, 0, n - 1, target));
}
