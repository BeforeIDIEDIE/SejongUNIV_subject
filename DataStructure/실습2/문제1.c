/*
[ 문제 1 ] 나머지 연산
‘%’(modulo) 연산자는 나눗셈의 나머지를 반환한다. 덧셈과 뺄셈 연산자만을 사용하여 a를 b로
나눈 나머지를 반환하는 modulo(a, b) 함수와 이를 테스트할 프로그램을 작성하시오. 단, a ≥ 0,
b > 0 인 정수다
*/

#include<stdio.h>

#pragma warning(disable:4996)

int modulo(int a, int b){
    while (a >= 0)
    {
        a -= b;//a가 음수가 될때 까지 a에 b를 반복하여 뺍니다.
    }
    return a+b;//a mod b의 값을 출력하기 위해 음수가 된 a값에 b를 더합니다.
}

int main()
{
    int a = 0;
    int b = 0;
    
    
    scanf("%d %d", &a, &b);

    int result = modulo(a, b); //a mod b의 결과가 저장될 정수형 변수 result에 a mod b를 수행하는 함수인 modulo를 실행한 값을 저장합니다. 

    printf("%d", result);
}
