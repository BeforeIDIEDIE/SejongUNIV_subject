#include<stdio.h>
#pragma warning(disable:4996)

int sum(int n)
{
    int sum_all = 0;
    for (int i = 1; i <= n; i++)
    {
        sum_all += i;//반복문을 이용하여 1부터 n까지의 수를 모두 sum_all 변수에 저장합니다.
    }
    return sum_all;
}

int main(void)
{
    int input = 0, output = 0;
    scanf("%d", &input);
    for (int i = 1; i <= input; i++)
    {
        output += sum(i);//반복문을 이용하여 1부터 input까지의 수를 sum함수의 인자로 수행하고 그 값을 output에 저장합니다. 
    }
    printf("%d", output);//output에 저장된 수를 출력합니다.

    return 0;
}
