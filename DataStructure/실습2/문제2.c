/*
[ 문제 2 ] 비트행렬에서 최대 1행 찾기
n × n 비트 행렬 A의 각 행은 1과 0으로만 구성되며, A의 어느 행에서나 1들은 해당 행의
0들보다 앞서 나온다고 가정하자. 행렬 A를 입력받아, 가장 많은 1을 포함하는 행을 찾는
프로그램을 작성하시오. 그러한 행이 여러 개 있을 경우 그 가운데 가장 작은 행 번호를 찾아야
Alg mostOnesButSlow(A, n) {solw versoni}
input bit matrix A[n × n]
output the row of A with most 1’s
1. row, jmax ← 0
2. for i ← 0 to n – 1
j ← 0
while ((j < n) & (A[i, j] = 1))
j ← j + 1
if (j > jmax)
row ← i
jmax ← j
3. return row 
*/

#include<stdio.h>

#pragma warning(disable:4996)

int mostOnes(int A[][100], int n)
{
    int x = 0, y = 0, row = 0;
    while ((x < n)&&(y< n)){//배열의 행과 열 둘중 하나라도 끝에 다다를시 반복문이 종료됩니다.
        //현재 배열의 위치의 값이 0이라면 행에 1을 더합니다. 그렇지 않을 경우 최다 1을 가진 행을 기록하는 row에 현재 행을 갱신하고 열에 1을 더합니다. 
        if (A[y][x] == 0) {            
            y++;
        }
        else{
            row = y;
            x++;
        }
    }
    return row;// 최다 1을 가진 행을 기록한 row를 반환합니다.
}

int main(void)
{
    int A[100][100] = { 0 };
    int n = 0;
    int result = 0;
    scanf("%d", &n);//행/열의 값을 입력받습니다.
    
    //mostOnes함수를 실행할 비트 행렬을 입력받습니다.
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &A[i][j]);
        }
    }
    result = mostOnes(A, n);//최다 1을 가진 행을 변수 result에 저장합니다.
    
    printf("%d", result);// result의 값을 출력합니다.
    return 0;
}
