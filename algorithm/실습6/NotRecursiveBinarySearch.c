#include<stdio.h>

#include<stdlib.h>

#pragma warning(disable:4996)

int BinarySearch(int* L, int l, int r, int value)
{
    int initial_r = r;
    while (l < r)
    {
        int half = (l + r) / 2;
        if (L[half] > value)
        {
            l = l;
            r = half - 1;
        }
        else if (L[half] < value)
        {
            r = r;
            l = half + 1;
        }
        else
        {
            return half;
        }
    }
    if (r < 0)
    {
        r = 0;
    }

    return r;
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
