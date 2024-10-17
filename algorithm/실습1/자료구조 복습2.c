#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable:4996)

typedef struct NODE
{
    int elem;
    struct NODE* left;
    struct NODE* right;
} NODE;

NODE* getNODE(int elem, int right, int left)
{
    NODE* brandNew = (NODE*)malloc(sizeof(NODE));
    brandNew->elem = elem;
    brandNew->left = (left == 0) ? NULL : getNODE(left, 0, 0);
    brandNew->right = (right == 0) ? NULL : getNODE(right, 0, 0);
    return brandNew; 
}

void linkNODE(NODE* root, int right, int left)
{
    root->left = (left == 0) ? NULL : getNODE(left, 0, 0);
    root->right = (right == 0) ? NULL : getNODE(right, 0, 0);
}

//이곳
NODE* findNODE(NODE* root, int value)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (root->elem == value)
    {
        return root;
    }

    NODE* leftResult = findNODE(root->left, value);
    if (leftResult != NULL)
    {
        return leftResult;
    }
    return findNODE(root->right, value);
}

void searchNODE(NODE* root, const char* path)
{
    NODE* current = root;
    printf("%d", current->elem); 
    while (*path)
    {
        if (*path == 'R')
        {
            current = current->right;
        }
        else if (*path == 'L')
        {
            current = current->left;
        }
        printf(" %d", current->elem);
        path++;
    }
    printf("\n");
}

int main()
{
    int n = 0;
    NODE* root = NULL;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int parents = 0, right = 0, left = 0;
        scanf(" %d %d %d", &parents, &left, &right);
        if (i == 0)
        {
            root = getNODE(parents, right, left);
        }
        else
        {
            NODE* curRoot = findNODE(root, parents);
            linkNODE(curRoot, right, left);
        }
    }

    int cmd = 0;
    scanf("%d", &cmd);
    getchar();
    for (int i = 0; i < cmd; i++)
    {
        char arr[101];
        scanf("%s", arr);
        searchNODE(root, arr);
    }

    return 0;
}
