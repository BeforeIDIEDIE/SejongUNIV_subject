#include <stdio.h>
#pragma warning(disable:4996)

void ABC(int arr[], int k){
    int max = arr[k];
    int max_index = k;
    int temp = 0;
    
    for (int i = k; i < 10; i++){
        if (max < arr[i]){//반복문 내에서 배열의 k번째 부터 마지막까지 각요소들을 max에 저장된 값과 비교하며, max에 저장되는 최댓값과 최대값의 인덱스를 갱신합니다.
            max = arr[i];
            max_index = i;
        }
    }
    temp = arr[k];//k번째 요소와 최대값의 요소를 바꿉니다.
    arr[k] = arr[max_index];
    arr[max_index] = temp;
}

int main(void){
    int arr[10] = { 0 };
    for (int i = 0; i < 10; i++){
        scanf("%d", &arr[i]);// 배열의 요소를 입력받습니다.
    }

    for (int i = 0; i < 10; i++){
        ABC(arr, i);//배열의 첫요소부터 마지막까지 ABC함수를 수행합니다. 그 결과 배열은 내림차순으로 정렬됩니다.
    }


    for (int i = 0; i < 10; i++){
        printf(" %d", arr[i]);//ABC함수의 결과를 출력합니다.
    }

    return 0;
}
