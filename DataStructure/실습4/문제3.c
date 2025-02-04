#include<stdio.h>//표준 입출력 헤더파일입니다.

#pragma warning(disable:4996)//scanf()함수로 인한 보안상의 경고 4996을 발생시키지 않도록 지시합니다.

int main()
{
    int arr[100][100];
    int input = 0;
    scanf("%d", &input);

    int count = 1;
    for (int i = 0; i < input; i++){
        if (i % 2 == 0){//만약 행이 짝수(0포함)라면 오름차순으로 배열에 요소를 추가합니다.
            for (int j = 0; j < input; j++){
                arr[i][j] = count;
                count++;
            }
        }
        else{//만약 행이 홀수라면 내림차순으로 배열에 요소를 추가합니다.
            for (int j = input-1; j >= 0; j--){
                arr[i][j] = count;
                count++;
            }
        }
    }
    //배열의 요소를 출력합니다.
    for (int i = 0; i < input; i++){
        for (int j = 0; j < input; j++){
            printf(" %d", arr[i][j]);
        }
        printf("\n");
    }

}
