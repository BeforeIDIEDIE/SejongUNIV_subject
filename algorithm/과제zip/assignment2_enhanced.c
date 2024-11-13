#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable: 4996)

void merge(int* L, int f, int s, int r) 
{
    int i = f;//왼쪽 부분의 시작 인덱스
    int j = s;//오른쪽 부분의 시작 인덱스
    int k = 0;//임시 배열의 인덱스

    int size = r - f;//합병할 크기
    int* temp = (int*)malloc(size * sizeof(int));//임시 배열 할당

    //두 부분을 합병
    while (i < s && j < r) 
    {
        if (L[i] <= L[j]) 
        {
            temp[k++] = L[i++];
        }
        else 
        {
            temp[k++] = L[j++];
        }
    }

    //남은 요소를 임시 배열에 추가
    while (i < s) 
    {
        temp[k++] = L[i++];
    }
    while (j < r) 
    {
        temp[k++] = L[j++];
    }

    //임시 배열을 원래 배열에 복사
    for (int m = 0; m < size; m++) 
    {
        L[f + m] = temp[m];
    }

    //임시 배열 메모리 해제
    free(temp);
}

void mergeSort(int* L, int len) 
{
    int h = 1;//합병될 부분 공간의 크기

    while (h < len) 
    {
        for (int i = 0; i < len; i += h * 2) 
        {
            int left = i; //왼쪽 시작 인덱스
            int mid = (i + h < len) ? (i + h) : len; //오른쪽 시작 인덱스
            int right = (i + h * 2 < len) ? (i + h * 2) : len; //오른쪽 끝 인덱스

            merge(L, left, mid, right);
        }

        //현재 상태 출력
        for (int j = 0; j < len; j++) 
        {
            printf(" %d", L[j]);
        }
        printf("\n");

        h *= 2; //합병할 크기 두 배로 증가
    }
}

int main() 
{
    int n = 0;
    scanf("%d", &n); //정렬할 원소 개수 입력

    int* arr = (int*)malloc(sizeof(int) * n); //동적 메모리 할당

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
