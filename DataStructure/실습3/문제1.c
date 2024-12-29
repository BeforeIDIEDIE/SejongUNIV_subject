//1~n까지의 합 문제
#include<stdio.h>

#pragma warning(disable:4996)

int sum(int n)//1부터 n까지의 수의 합을 구하는 sum입니다.
{
    if (n == 1){//n이 재귀를 통해 1이 되면 1을 반환합니다.
        return 1;
    }
    else{
        return sum(n - 1) + n;//이전의 1부터 n-1까지의 합에 현재의 n을 더합니다.
    }
}

int main()
{
    int input = 0;
    scanf("%d", &input);//입력을 변수 input에 입력받습니다.
    printf("%d", sum(input));//1부터 n까지의 합을 sum함수로 계산하여 출력합니다.
}
