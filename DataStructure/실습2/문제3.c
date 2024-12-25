/*
[ 문제 3 ] 누적 평균
원시 데이터값들로 구성된 배열 X의 i-번째 누적평균(prefix average)이란 X의 i-번째에
이르기까지의 (i + 1)개 원소들의 평균이다. 즉,
A[i] = (X[0] + X[1] + … + X[i])/(i + 1)
누적평균은 경제, 통계 분야에서 오르내림 변동을 순화시킴으로써 대략적 추세를 얻어내기 위해
사용된다. 일례로 부동산, 주식, 펀드 등에도 자주 활용된다.. 이 문제는 배열 X의 누적평균(prefix
average) 배열 A를 구하는 프로그램을 구현하고 테스트하는데 관한 것이다.
◦ 아래 의사코드 함수 prefixAverages1은 위 정의를 있는 그대로 이용하여 누적평균값들을 2차
시간에 구한다.
※ 참고: 각 명령문 오른 편 중괄호 내의 수식은 실행시간 분석을 위한 근거로서, 해당 명령문이
수행하는 치환, 반환, 산술 및 비교 연산 등 기본 명령들의 수행 횟수를 나타낸다.
Alg prefixAverages1(X, n) {ver.1}
input array X of n integers
output array A of prefix averages of X
1. for i ← 0 to n – 1 {n}
sum ← 0 {n}
for j ← 0 to i {1 + 2 + … + n}
sum ← sum + X[j] {1 + 2 + … + n}
A[i] ← sum/(i + 1) {n}
2. return A 
*/

#include<stdio.h>
#include<stdlib.h>

#pragma warning(disable:4996)

int* prefixAverages1(int* X, int n)
{
    int* A = (int*)malloc(n * sizeof(int));//누적 평균이 저장될 동적 배열 A입니다.
    double sum = 0;//누적 합계가 저장될 변수입니다.
    for (int i = 0; i < n; i++){
        sum = 0;
        for (int j = 0; j <= i; j++) {
            sum += X[j];
            A[i] = (int)((sum / (i + 1)) + 0.5); //배열 A에 누적 평균의 소수점 이하를 반올림한 값이 저장됩니다.
        }
    }
    return A;//배열 A가 반환 됩니다.
}

int* prefixAverages2(int* X, int n)
{
    int* A = (int*)malloc(n * sizeof(int));//누적 평균이 저장될 동적 배열 A입니다.
    double sum = 0;//누적 합계가 저장될 변수입니다.
    for (int i = 0; i < n; i++) {
        sum += X[i];
        A[i] = (int)((sum / (i + 1)) + 0.5);//배열 A에 누적 평균의 소수점 이하를 반올림한 값이 저장됩니다.
    }
    return A;//배열 A가 반환 됩니다.
}

int main()
{
    int n = 0;//배열의 크기를 입력받습니다.
    scanf("%d", &n);
    int* X= (int*)malloc(n * sizeof(int));//입력들이 저장될 동적 할당 배열인 X입니다.
    int* A;//prefixAverages1,prefixAverages2의 수행값들이 저장될 포인터 변수인 X입니다.

    for (int i = 0; i < n; i++) {
        scanf("%d", &X[i]);// 첫 번째 입력들을 X에 입력받습니다.
    }
    A = prefixAverages1(X, n);//배열 X에 prefixAverages1을 수행한 결과를 포인터 변수 A에 저장합니다.

    for (int i = 0; i < n; i++) {
        printf("%d ",A[i]);// 배열A에 저장된 prefixAverages1의 결과들을 출력합니다.
    }
    printf("\n");

    A = prefixAverages2(X, n); //배열 X에 prefixAverages2을 수행한 결과를 포인터 변수 A에 저장합니다.
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);// 배열A에 저장된 prefixAverages2의 결과들을 출력합니다.
    }

}
