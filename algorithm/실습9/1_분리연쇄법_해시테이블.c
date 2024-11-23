//
//◦ 구현 조건
//- 해시테이블은 크기가 M인 배열로 동적 할당한다. - 입력 키는 중복이 없는 자연수다. - 키 x에 대한 해시함수 h(x) = x % M 을 사용한다. - 삽입 시 충돌이 발생하는 경우, 해당 버켓 리스트의 맨 앞에 삽입한다.◦ 입력
//- 해시테이블의 크기 M을 입력받는다. - 삽입(i), 탐색(s), 삭제(d), 인쇄(p) 명령어를 순서에 상관없이 반복하여 입력받는다.
//i <x> : 키 x를 해시테이블에 삽입
//s <x> : 키 x가 해시테이블에 존재하는지 탐색
//d <x> : 키 x가 해시테이블에 존재하면 삭제
//p : 해시테이블에 저장된 키들을 순서대로 인쇄(입출력 예시 참조) e : 프로그램 종료
//◦ 출력
//- 키를 삽입하였을 때 아무 출력을 하지 않는다. - 탐색 또는 삭제할 때, 키가 존재하면 리스트에서 해당 키가 저장된 순위(1부터 시작)를
//인쇄하고 없다면 0을 인쇄한다(해시테이블의 주소가 아닌 리스트에서의 순위를 인쇄함에
//    유의). - 해시테이블을 인쇄할 때, 0번 주소부터 마지막 주소까지 순회하면서 저장된 키들을
//    방문하는 순으로 인쇄한다.


#include<stdio.h>

#include<stdlib.h>

#pragma warning(disable:4996)

typedef struct NODE
{
    int num;
    struct NODE* next;
}NODE;



void insertNODE(NODE**arr, int i, int n)
{
    int idx = i % n;
    NODE* cur = (NODE*)malloc(sizeof(NODE));
    cur->num = i;
    cur->next = arr[idx];
    arr[idx] = cur;
}

int searchNODE(NODE** arr, int i, int n)
{
    int idx = i % n;
    if (arr[idx] == NULL)
    {
        return 0;
    }
    NODE* cur = arr[idx];
    int cnt = 1;
    while (cur != NULL)
    {
        if (cur->num == i)
        {
            return cnt;
        }
        cnt++;
        cur = cur->next;
    }
    return 0;
}

int deleteNODE(NODE** arr, int i, int n)
{
    int idx = i % n;
    if (arr[idx] == NULL)
    {
        return 0;
    }
    if (arr[idx]->num == i)
    {
        arr[idx] = arr[idx]->next;
        return 1;
    }
    NODE* cur = arr[idx];
    int cnt = 1;
    while (cur != NULL)
    {
        if (cur->next!=NULL&&cur->next->num == i)
        {
            NODE* temp = cur->next;
            cur->next = cur->next->next;
            free(temp);
            return cnt+1;
        }
        cnt++;
        cur = cur->next;
    }
    return 0;
}

void print_ALL(NODE** arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == NULL)
        {
            continue;
        }
        NODE* cur = arr[i];
        while (cur != NULL)
        {
            printf(" %d", cur->num);
            cur = cur->next;
        }
    }
    printf("\n");
}

void free_all(NODE** arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == NULL)
        {
            continue;
        }
        NODE* cur = arr[i];

        while (cur != NULL)
        {
            NODE* next = cur->next;
            free(cur);
            cur = next;
        }
    }
    free(arr);
}

int main()
{
    int n = 0;
    scanf("%d", &n);
    NODE** arr = (NODE*)malloc(sizeof(NODE)*n);//투 포인터
    for (int i = 0; i < n; i++)//아래 작업 중요
    {
        arr[i] = NULL;
    }
    while (1)
    {
        char e = 0;
        scanf(" %c", &e);
        switch (e)
        {
        case 'i':
        {
            int input = 0;
            scanf("%d", &input);
            insertNODE(arr, input, n);
            break;
        }
        case 's':
        {
            int input = 0;
            scanf("%d", &input);
            printf("%d\n",searchNODE(arr, input, n));
            break;
        }
        case 'd':
        {
            int input = 0;
            scanf("%d", &input);
            printf("%d\n",deleteNODE(arr, input, n));
            break;
        }
        case 'p':
        {
            print_ALL(arr, n);
            break;
        }
        case 'e':
        {
            free_all(arr,n);

            return;
        }
        }
    }
}
