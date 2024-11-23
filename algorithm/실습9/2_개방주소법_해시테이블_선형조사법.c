//◦ 구현 조건
//- 해시테이블은 크기가 M인 배열로 동적 할당한다. - n은 M보다 작은 자연수로 최대 삽입 개수다. - 입력 키는 중복이 없는 6자리 또는 8자리의 임의의 자연수(학번)다. - 키 x에 대한 해시함수 h(x) = x % M 을 사용한다. - 저장된 키 값이 없는 빈 버켓은 0으로 처리한다.◦ 입력
//- 해시테이블의 크기 M과 입력 데이터의 크기 n을 입력받는다. - 삽입(i), 탐색(s) 명령어를 순서에 상관없이 반복하여 입력받는다.
//i <x> : 키 x를 해시테이블에 삽입
//s <x> : 키 x가 해시테이블에 존재하는지 탐색
//e : 프로그램 종료
//◦ 출력 - 키를 삽입하였을 때, 저장된 주소(배열 인덱스)를 인쇄한다.
//<알고리즘 실습> 해시테이블 - 3 -
//-삽입할 때 충돌이 일어나면 선형조사법에 의해 다음 셀로 이동하여 충돌 검사를 계속한다.충돌 횟수만큼 C를 인쇄한 후, 삽입에 성공한 주소를 인쇄한다. - 탐색한 키가 테이블에 존재할 경우, 키가 저장된 주소와 값을 인쇄한다(없을 경우 –1을
//    인쇄한다).

#include<stdio.h>

#include<stdlib.h>

#pragma warning(disable:4996)

void insertINT(int* arr, int n, int i)
{
    int idx = i % n;
    if (arr[idx] == 0)
    {
        arr[idx] = i;
        printf("%d\n", idx);
        return;
    }
    while (1)
    {
        if (arr[idx] == 0)
        {
            arr[idx] = i;
            printf("%d\n", idx);
            return;
        }
        printf("C");
        idx = (idx + 1) % n;
    }
}

void searchINT(int* arr, int n, int i)
{
    int idx = i % n;
    int first_idx = idx;
    if (arr[idx] == 0)
    {
        printf("-1\n");
        return;
    }
    
    while (1)
    {
        if (arr[idx] == i)
        {
            printf("%d %d\n", idx, arr[idx]);
            return;
        }
        idx = (idx + 1) % n;
        if (idx == first_idx)
        {
            printf("-1\n");
            return;
        }
    }
}


int main()
{
    int m = 0, n = 0;
    scanf("%d %d", &m, &n);

    int* arr = (int*)calloc(m, sizeof(n));
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
            insertINT(arr, m, input);
            break;
        }
        case 's':
        {
            int input = 0;
            scanf("%d", &input);
            searchINT(arr, m, input);
            break;
        }
        case 'e':
        {
            free(arr);
            return;
        }
        }
    }
}
