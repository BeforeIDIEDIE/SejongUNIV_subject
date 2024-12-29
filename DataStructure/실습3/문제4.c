//N개의 수를 입력받아 그중 최댓값을 출력
#include<stdio.h>
#include<limits.h>

#pragma warning(disable:4996)

int rMax(int N, int max) {
	int a = 0;// 입력을 변수 a에 입력받습니다.
	scanf("%d", &a);
	if (max < a){//max값이 새로 받은 a보다 크다면 max값을 갱신합니다.
		max = a;
	}
	if (N == 1){//만약 전부 입력 받았다면 max값을 반환합니다. 
		return max;
	}
	else{
		rMax(N - 1, max);//만약 아직 입력을 전부 받지 못하였다면 다시 rMax함수를 재귀 호출합니다.
	}
}

int main() 
{
	int N = 0;
	scanf("%d", &N);
	printf("%d", rMax(N, INT_MIN));// N의 수만큼 정수를 입력받고 그중 최댓값을 구하는 rMax함수의 반환값을 출력합니다
	//INT_MIN은 32비트 signed int자료형이 가질수있는 가장 작은 수인 -2147483648가 주어집니다.

}
