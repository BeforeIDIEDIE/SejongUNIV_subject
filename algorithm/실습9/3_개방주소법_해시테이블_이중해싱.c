//◦ 구현 조건
//- 해시테이블은 크기가 M인 배열로 동적 할당한다(종료 시 해제). - n은 M보다 작은 자연수로 최대 삽입 개수다. - 입력 키는 중복이 없는 2자리 이상의 자연수다. - 키 x에 대한 첫 번째 해시함수 h(x) = x % M, 두 번째 해시함수 h‘(x) = q –(x % q) 를
//사용한다.q는 M보다 조금 작은 소수로 입력으로 주어진다. - 저장된 키가 없는 빈 버켓은 0으로 처리한다.◦ 입력
//- M, n, q를 입력받는다. - 삽입(i), 탐색(s), 출력(p) 명령어를 순서에 상관없이 반복하여 입력받는다.
//i <x> : 키 x를 입력받아 해시테이블에 삽입
//<알고리즘 실습> 해시테이블 - 4 -
//s <x> : 키 x가 해시테이블에 존재하는지 탐색
//p : 현재의 해시테이블 인쇄
//e : 해시테이블 인쇄 후 프로그램 종료
//◦ 출력
//- 키를 삽입하였을 때, 저장된 주소(배열 인덱스)를 인쇄한다. - 삽입할 때 충돌이 일어나면 두 번째 해시함수로부터 얻은 셀로 이동하여 충돌 검사를
//계속한다.충돌 횟수만큼 C를 인쇄한 후, 삽입에 성공한 주소를 인쇄한다. - 탐색한 키가 테이블에 존재할 경우, 키가 저장된 주소와 값을 인쇄한다(없을 경우 –1을
//    인쇄한다).

#include<stdio.h>

#include<stdlib.h>

#pragma warning(disable:4996)

void insertINT(int* arr, int m,int q, int i)
{
    int idx = i % m;
    if (arr[idx] == 0)
    {
        arr[idx] = i;
        printf("%d\n", idx);
        return;
    }
    int second_idx = q - (i % q);
    while (1)
    {
        if (arr[idx] == 0)
        {
            arr[idx] = i;
            printf("%d\n", idx);
            return;
        }
        printf("C");
        idx = (idx + second_idx) % m;
    }
}

void searchINT(int* arr, int m, int q, int i)
{
    int idx = i % m;
    int first_idx = idx;
    if (arr[idx] == 0)
    {
        printf("-1\n");
        return;
    }
    int second_idx = q - (i % q);
    while (1)
    {
        
        if (arr[idx] == i)
        {
            printf("%d %d\n", idx, i);
            return;
        }
        idx = (idx + second_idx) % m;
        if (idx == first_idx)
        {
            printf("-1\n");
            return;
        }
    }
}

void printArr(int* arr, int m)
{
    for (int i = 0; i < m; i++)
    {
        printf(" %d", arr[i]);
    }
    printf("\n");
}

int main()
{
    int m = 0, n = 0, q = 0;
    scanf("%d %d %d", &m, &n, &q);
    int* arr = (int*)calloc(m, sizeof(int));
    while (1)
    {
        char cmd = 0;
        scanf(" %c", &cmd);
        switch (cmd)
        {
        case 'p':
        {
            printArr(arr, m);
            break;
        }
        case 'i':
        {
            int input = 0;
            scanf("%d", &input);
            insertINT(arr, m,q, input);
            break;
        }
        case 's':
        {
            int input = 0;
            scanf("%d", &input);
            searchINT(arr, m,q, input);
            break;
        }
        case 'e':
        {
            printArr(arr, m);
            free(arr);
            return;
        }
        }
    }
}
