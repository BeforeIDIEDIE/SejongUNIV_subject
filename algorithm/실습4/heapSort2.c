#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#pragma warning(disable:4996)

int* L;//부모가 자식보다 큼
int n;

int lchild(int i)
{
    return i * 2;
}
int rchild(int i)
{
    return i * 2 + 1;
}
int parents(int i)
{
    return i / 2;
}
bool isValid(int i)
{
    return i >= 1 && i <= n;
}
void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void downHeap(int i)
{
    int smaller = i;
    if (isValid(lchild(i)) && L[lchild(i)] < L[smaller])
    {
        smaller = lchild(i);
    }
    if (isValid(rchild(i)) && L[rchild(i)] < L[smaller])
    {
        smaller = rchild(i);
    }
    if (i != smaller)
    {
        swap(&L[i], &L[smaller]);
        downHeap(smaller);
    }
}
void upHeap(int i)
{
    if (isValid(parents(i)) && L[i] < L[parents(i)])
    {
        swap(&L[i], &L[parents(i)]);
        upHeap(parents(i));
    }
}
void insertItrem(int k)
{
    L[++n] = k;
    upHeap(n);
}

int removeMin()
{
    int e = L[1];
    L[1] = L[n--];
    downHeap(1);
    return e;
}

void printHeap()
{
    int* copyL = (int*)malloc(sizeof(int) * 101);
    int idx = 0;
    while (n != 0)
    {
        copyL[idx++] = removeMin();
    }
    for (int i = 0; i < idx; i++)
    {
        printf(" %d", copyL[i]);
    }
    free(copyL);
}
void rBuildHeap(int i)//이거 암기
{
    if (i > n)
    {
        return;
    }
    rBuildHeap(2 * i);
    rBuildHeap(2 * i + 1);
    downHeap(i);
}
void buildHeap()//이거 암기
{
    for (int i = n / 2; i >= 1; i--)
    {
        downHeap(i);
    }
    return;
}

int main()
{
    scanf("%d", &n);
    L = (int*)malloc(sizeof(int) * 101);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &L[i]);
    }
    //rBuildHeap(1);
    buildHeap();
    printHeap();
}
