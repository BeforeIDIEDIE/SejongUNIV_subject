#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable:4996)

typedef struct NODE
{
    int elem;
    struct NODE* next;
} NODE;

typedef struct pair
{
    NODE* L1;
    NODE* L2;
} pair;

NODE* getNODE(int elem)
{
    NODE* brandNew = (NODE*)malloc(sizeof(NODE));
    brandNew->elem = elem;
    brandNew->next = NULL;
    return brandNew;
}

NODE* merge(NODE* L1, NODE* L2)
{
    NODE dummy;
    NODE* tail = &dummy;
    dummy.next = NULL;

    while (L1 != NULL && L2 != NULL) 
    {
        if (L1->elem < L2->elem) 
        {
            tail->next = L1;
            L1 = L1->next;
        }
        else 
        {
            tail->next = L2;
            L2 = L2->next;
        }
        tail = tail->next;
    }
    tail->next = (L1 != NULL) ? L1 : L2;

    return dummy.next;
}

pair partition(NODE* L, int k) 
{
    NODE* L1 = L;
    NODE* L2 = L;
    NODE* p = L;

    for (int i = 0; i < k - 1 && p != NULL; i++) 
    {
        p = p->next;
    }

    if (p != NULL) {
        L2 = p->next;
        p->next = NULL;
    }

    pair brandNew;
    brandNew.L1 = L1;
    brandNew.L2 = L2;
    return brandNew;
}

NODE* mergeSort(NODE* L) 
{
    if (L == NULL || L->next == NULL) 
    {
        return L;
    }

    NODE* p = L;
    int length = 0;
    while (p != NULL)
    {
        length++;
        p = p->next;
    }

    int mid = length / 2;
    pair split = partition(L, mid);
    NODE* L1 = mergeSort(split.L1);
    NODE* L2 = mergeSort(split.L2);

    return merge(L1, L2);
}

int main()
{
    int n = 0;
    scanf("%d", &n);

    int input = 0;
    scanf("%d", &input);
    NODE* arr = getNODE(input);

    NODE* p = arr;
    for (int i = 1; i < n; i++)
    {
        scanf("%d", &input);
        p->next = getNODE(input);
        p = p->next;
    }

    NODE* sortedList = mergeSort(arr);

    NODE* current = sortedList;
    while (current != NULL)
    {
        printf("%d", current->elem);
        current = current->next;
        if (current != NULL)
        {
            printf(" ");
        }
    }

    return 0;
}
