#include<stdio.h>//표준 입출력 헤더파일입니다.

#pragma warning(disable:4996)//scanf()함수로 인한 보안상의 경고 4996을 발생시키지 않도록 지시합니다.

void swap_arr(int arr[], int first, int end)//배열과 범위를 입력받으면 "뒤집기"를 수행하는 함수입니다.
{
    int temp = 0;
    while (first<end)//입력받은 범위의 양끝인덱스를 가운데로 좁혀나가며 "뒤집기"를 수행하는 반복문입니다.
    {
        temp = arr[first];
        arr[first] = arr[end];
        arr[end] = temp;
        first++;
        end--;
    }
}
int main()
{
    int arr[100];
    int input1 = 0;
    scanf("%d", &input1);//배열의 크기를 입력받습니다.
    for (int i = 0; i < input1; i++)
    {
        scanf("%d", &arr[i]);//배열의 요소를 입력받습니다.
    }

    int input2 = 0;
    scanf("%d", &input2);//뒤집을 구간의 개수를 입력받습니다.
    for (int i = 0; i < input2; i++)//뒤집을 구간을 입력받고 뒤집기를 수행할 반복문입니다.
    {
        int first = 0, end = 0;
        scanf("%d %d", &first, &end);
        swap_arr(arr, first, end);
    }

    //배열의 요소를 출력합니다.
    printf(" ");
    for (int i = 0; i < input1; i++)
    {
        printf("%d ", arr[i]);
    }

}
