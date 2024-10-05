#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable:4996)

typedef struct NODE
{
    char elem;
    struct NODE* prev;
    struct NODE* next;
} NODE;

int total_elem_cnt = 0;

NODE* getNODE(char e)
{
    NODE* newNODE = (NODE*)malloc(sizeof(NODE));
    newNODE->elem = e;
    newNODE->next = NULL;
    newNODE->prev = NULL;
    return newNODE;
}

void add(NODE* list, int r, char e)
{
    if (r < 1 || total_elem_cnt + 1 < r)
    {
        printf("invalid position\n");
    }
    else
    {
        NODE* cur = list;
        for (int i = 0; i < r; i++) 
        {
            cur = cur->next;
        }
        NODE* insert = getNODE(e);
        insert->prev = cur->prev;
        insert->next = cur;
        cur->prev->next = insert;
        cur->prev = insert;
        total_elem_cnt++;
    }
}

void delete(NODE* list, int r)
{
    if (r < 1 || total_elem_cnt < r)
    {
        printf("invalid position\n");
    }
    else
    {
        NODE* cur = list;
        for (int i = 0; i < r; i++) 
        {
            cur = cur->next;
        }
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
        free(cur);
        total_elem_cnt--;
    }
}

char get(NODE* list, int r)
{
    if (r < 1 || total_elem_cnt < r)
    {
        printf("invalid position\n");
        return '\0';
    }
    else
    {
        NODE* cur = list;
        for (int i = 0; i < r; i++)
        {
            cur = cur->next;
        }
        return cur->elem;
    }
}

void print(NODE* list)
{
    NODE* cur = list->next;
    while (cur->next != NULL)
    {
        printf("%c", cur->elem);
        cur = cur->next;
    }
    printf("\n");
}

void freeList(NODE* list) {
    NODE* cur = list;
    while (cur != NULL) {
        NODE* temp = cur;
        cur = cur->next;
        free(temp);
    }
}

int main()
{
    NODE* list = (NODE*)malloc(sizeof(NODE));
    NODE* tail = (NODE*)malloc(sizeof(NODE));

    list->next = tail;
    tail->prev = list;
    list->prev = NULL;
    tail->next = NULL;

    int cmd = 0;
    scanf("%d", &cmd);
    getchar(); 

    for (int i = 0; i < cmd; i++)
    {
        char input;
        scanf(" %c", &input);
        switch (input)
        {
        case 'A':
        {
            int rank;
            char elem;
            scanf("%d %c", &rank, &elem);
            add(list, rank, elem);
            break;
        }
        case 'D':
        {
            int rank;
            scanf("%d", &rank);
            delete(list, rank);
            break;
        }
        case 'G':
        {
            int rank;
            scanf("%d", &rank);
            char value = get(list, rank);
            if (value != '\0')
            {
                printf("%c\n", value);
            }
            break;
        }
        case 'P':
        {
            print(list);
            break;
        }
        }
    }

    freeList(list);

    return 0;
}
