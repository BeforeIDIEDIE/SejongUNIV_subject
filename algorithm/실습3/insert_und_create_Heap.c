#include<stdio.h>

#include<stdlib.h>

#pragma warning(disable: 4996)

int* H;
int n = 0;

int sibiling(int i)
{
    return i % 2 == 0 ? i + 1 : i - 1;
}

int parents(int i)
{
    return i / 2;
}

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void upHeap(int i)
{
    if (i == 1)
    {
        return;
    }
    if (H[i] > H[parents(i)])
    {
        swap(&H[i], &H[parents(i)]);
        upHeap(parents(i));
    }
}

void downHeap(int i)//디버깅함
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

void insertItem(int k)
{
    n++;
    H[n] = k;
    upHeap(n);
}

int removeMax()//디버깅함
{
    if (n == 0)
    {
        return -1;
    }
    int max = H[1];
    H[1] = H[n];
    n--;
    downHeap(1);
    return max;
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
    while (1)
    {
        char cmd = 0;
        scanf(" %c", &cmd);
        switch (cmd)
        {
        case 'i':
        {
            int input = 0;
            scanf("%d", &input);
            insertItem(input);
            printf("0\n");
            break;
        }
        case 'd':
        {
            int e = removeMax();
            printf("%d\n", e);
            break;
        }
        case 'p':
        {
            printHeap();
            break;
        }
        case 'q':
        {
            free(H);
            return;
            break;
        }
        }
    }
}
