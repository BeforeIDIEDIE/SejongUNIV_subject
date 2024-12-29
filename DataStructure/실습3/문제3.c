#include<stdio.h>
#include<stdlib.h>

#pragma warning(disable:4996)

void rPrintDigit(int n)//rPrintDigit는 낮은 자릿 수 부터 하나씩 차례로 출력합니다.
{
    if (n < 10) {//만약 n이 10보다 작은 경우 한자릿 수이므로 바로 출력합니다.
        printf("%d", n);
    }
    else {
        printf("%d\n", (n % 10));
        rPrintDigit(n / 10);//n이 10 보다 큰 경우 n을 10으로 나눈값을 출력하고, rPrintDigit를 (n/10)을 인자로 호출합니다.
    }
}

int main()
{
    int input = 0;
    scanf("%d", &input);//입력을 변수 input에 입력받습니다.
    rPrintDigit(input);//input의 각 자리를 낮은 자릿 수부터 rPrintDigit함수를 통해 출력합니다.
}
