#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#pragma warning(disable: 4996)

typedef struct NODE
{
    int key;
    struct NODE* next;
}NODE;

typedef struct part
{
    NODE* LT;
    NODE* GT;
    NODE* EQ;
}part;

NODE* getNODE(int i)
{
    NODE* brandNew = (NODE*)malloc(sizeof(NODE));
    brandNew->key = i;
    brandNew->next = NULL;
    return brandNew;
}

NODE* merge(NODE* LT, NODE* EQ, NODE* GT)
{
    NODE* dummy = getNODE(1);
    NODE* L = LT;
    NODE* E = EQ;
    NODE* G = GT;
    NODE* cur = dummy;
    while (L != NULL)
    {
        cur->next = L;
        cur = cur->next;
        L = L->next;
    }
    while (E != NULL)
    {
        cur->next = E;
        cur = cur->next;
        E = E->next;
    }
    while (G != NULL)
    {
        cur->next = G;
        cur = cur->next;
        G = G->next;
    }
    NODE* forReturn = dummy->next;
    free(dummy);
    return forReturn;
}

part parition(NODE* L, int pivot)
{
    NODE* LT = getNODE(1);
    NODE* EQ = getNODE(1);
    NODE* GT = getNODE(1);
    NODE* cur = L;
    NODE* L_temp = LT;
    NODE* E_temp = EQ;
    NODE* G_temp = GT;

    while (cur != NULL)//변수 주의!
    {
        if (cur->key > pivot)
        {
            G_temp->next = getNODE(cur->key);
            G_temp = G_temp->next;
        }
        else if(cur->key==pivot)
        {
            E_temp->next = getNODE(cur->key);
            E_temp = E_temp->next;
        }
        else
        {
            L_temp->next = getNODE(cur->key);
            L_temp = L_temp->next;
        }
        cur = cur->next;
    }
    part forReturn;
    forReturn.EQ = EQ->next;
    forReturn.GT = GT->next;
    forReturn.LT = LT->next;
    free(EQ);
    free(GT);
    free(LT);
    return forReturn;
}

NODE* quickSort(NODE* L)
{
    if (L == NULL || L->next == NULL)
    {
        return L;
    }
    int i = 0;
    NODE* cnt = L;
    while (cnt != NULL)
    {
        cnt = cnt->next;
        i++;
    }
    srand(time(NULL));
    int random = rand() % (i);
    int pivot = 0;
    cnt = L;
    for (int j = 0; j < random; j++)
    {
        cnt = cnt->next;
    }
    pivot = cnt->key;
    part division = parition(L, pivot);
    free(L);
    division.LT = quickSort(division.LT);
    division.GT = quickSort(division.GT);
    return merge(division.LT, division.EQ, division.GT);
}


int main()
{
    int n = 0;
    scanf("%d", &n);
    int input = 0;
    scanf("%d", &input);
    NODE* first = getNODE(input);
    NODE* temp = first;
    for (int i = 1; i < n; i++)
    {
        scanf("%d", &input);
        temp->next = getNODE(input);
        temp = temp->next;
    }
    first = quickSort(first);
    temp = NULL;
    while (first != NULL)
    {
        temp = first;
        printf(" %d", temp->key);
        first = first->next;
        free(temp);
    }
}
