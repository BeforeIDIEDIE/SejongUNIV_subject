#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable:4996)

typedef struct NODE 
{
    struct NODE* lChild;
    struct NODE* rChild;
    struct NODE* parent;
    int key;
} NODE;

NODE* getNODE(int k) 
{
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    newNode->lChild = NULL;
    newNode->rChild = NULL;
    newNode->parent = NULL;
    newNode->key = k;
    return newNode;
}

int findElement(NODE* root, int k) 
{
    NODE* current = root;
    while (current != NULL) 
    {
        if (current->key > k)
        { 
            current = current->lChild;
        }
        else if (current->key < k)
        {
            current = current->rChild;
        }
        else
        {
            return current->key;
        }
    }
    return -999;
}

NODE* treeSearch(NODE* root, int k) 
{
    NODE* current = root;
    while (current != NULL) 
    {
        if (current->key > k)
        {
            current = current->lChild;
        }
        else if (current->key < k)
        {
            current = current->rChild;
        }
        else
        {
            return current;  // 키가 존재함
        }
    }
    return NULL; 
}
NODE* findParentForInsert(NODE* root, int k) 
{
    NODE* parent = NULL;
    NODE* current = root;
    while (current != NULL) 
    {
        parent = current;
        if (k < current->key)
        {
            current = current->lChild;
        }
        else
        {
            current = current->rChild;
        }
    }
    return parent;
}
void insertItem(NODE** root, int k) //더블포인터
{
    if (*root == NULL) 
    { 
        *root = getNODE(k);
        return;
    }

    NODE* parent = findParentForInsert(*root, k);
    if (parent->key == k)
    {
        return;
    }

    NODE* newNode = getNODE(k);
    newNode->parent = parent;
    if (k < parent->key)
    {
        parent->lChild = newNode;
    }
    else
    { 
        parent->rChild = newNode;
    }
}

int removeElement(NODE** root, int k) //더블포인터
{
    NODE* target = treeSearch(*root, k);
    if (target == NULL) 
    {
        return -999;
    }
    if (target->lChild == NULL && target->rChild == NULL) 
    {  
        if (target->parent == NULL)
        {
            *root = NULL;
        }
        else if (target == target->parent->lChild)
        {
            target->parent->lChild = NULL;
        }
        else
        {
            target->parent->rChild = NULL;
        }
        free(target);
    }
    else if (target->lChild == NULL || target->rChild == NULL) 
    { 
        NODE* child = (target->lChild != NULL) ? target->lChild : target->rChild;
        if (target->parent == NULL)
        {
            *root = child;
        }
        else if (target == target->parent->lChild)
        {
            target->parent->lChild = child;
        }
        else
        {
            target->parent->rChild = child;
        }
        child->parent = target->parent;
        free(target);
    }
    else 
    {
        NODE* successor = target->rChild;
        while (successor->lChild != NULL)
        {
            successor = successor->lChild;
        }
        target->key = successor->key;
        removeElement(&(target->rChild), successor->key);
    }
    return k;
}

void preOrderSucc(NODE* root) 
{
    if (root == NULL)
    {
        return;
    }
    printf("%d ", root->key);
    preOrderSucc(root->lChild);
    preOrderSucc(root->rChild);
}

int main() 
{
    NODE* root = NULL;  // 초기값은 NULL로 설정
    char cmd;
    while (1) {
        scanf(" %c", &cmd);
        int input = 0;
        switch (cmd) 
        {
        case 'i':
        {
            scanf("%d", &input);
            insertItem(&root, input);
            break;
        }
        case 'd':
        {
            scanf("%d", &input);
            int result = removeElement(&root, input);
            if (result == -999)
            {
                printf("X\n");
            }
            else
            {
                printf("%d\n", result);
            }
            break;
        }
        case 's':
            scanf("%d", &input);
            int found = findElement(root, input);
            if (found == -999)
            {
                printf("X\n");
            }
            else
            {
                printf("%d\n", found);
            }
            break;
        case 'p':
            preOrderSucc(root);
            printf("\n");
            break;
        case 'q':
            free(root);
            return 0;
        }
    }
}
