#include <stdio.h>

#include <stdlib.h>

#pragma warning(disable: 4996)

void merge(int* L, int len, int f, int s, int h)//두 부분을 합치는 함수
{
    int mid = f + h/2;//중간 인덱스 계산
    int i = f;//왼쪽 부분의 시작 인덱스
    int j = mid;//오른쪽 부분의 시작 인덱스
    int idx = 0;//임시 배열의 인덱스

    int size = (s < len) ? (s - f) : (len - f);//합병할 크기 계산

    int* dummy = (int*)malloc(sizeof(int) * size);//임시 배열 

    //두 부분을 합병
    while (i < mid && j < s) 
    {
        if (L[i] <= L[j]) 
        {
            dummy[idx++] = L[i++];
        }
        else 
        {
            dummy[idx++] = L[j++];
        }
    }

    //남아있는 요소를 임시 배열에 추가
    while (i < mid) 
    {
        dummy[idx++] = L[i++];
    }
    while (j < s) 
    {
        dummy[idx++] = L[j++];
    }

    //임시 배열을 원래 배열에 복사
    for (int k = 0; k < size; k++) 
    {
        L[f + k] = dummy[k];
    }

    //임시 배열 메모리 해제
    free(dummy);
}

//반복적 합병 정렬 함수
void mergeSort(int* L, int len) 
{
    int h = 1; //초기 합병할 크기/2

    while (1) 
    {
        h *= 2; //합병할 크기 두 배로 증가
        for (int i = 0; i < len; i += h) 
        {
            int s = i + h; //오른쪽 부분의 끝 인덱스
            if (s > len) 
            {
                s = len; //배열 범위를 초과하지 않도록 조정
            }
            merge(L, len, i, s, h);
        }

        //현재 상태 출력
        for (int j = 0; j < len; j++) 
        {
            printf(" %d", L[j]);
        }
        printf("\n");

        if (h >= len)//조건을 탈출하기 위한 조건
        {
            break;
        }
    }
}

int main() 
{
    int n = 0;
    scanf("%d", &n); //정렬할 원소 개수 입력

    int* arr = (int*)malloc(sizeof(int) * n);//동적 메모리 할당

    //배열 원소 입력
    for (int i = 0; i < n; i++) 
    {
        scanf("%d", &arr[i]);
    }

    //반복적 합병 정렬 수행
    mergeSort(arr, n);

    //메모리 해제
    free(arr);
    return 0;
}
