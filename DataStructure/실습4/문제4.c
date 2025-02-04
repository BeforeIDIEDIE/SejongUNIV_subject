#include<stdio.h>//표준 입출력 헤더파일입니다.

#pragma warning(disable:4996)//scanf()함수로 인한 보안상의 경고 4996을 발생시키지 않도록 지시합니다.

int main() 
{
	int row = 0, col = 0, in_row = 0, in_col = 0, count = 2;
	int arr[100][100] = { 0 };
	scanf("%d %d", &row, &col);
	arr[0][0] = 1;// 이후 배열을 완성시킬 코드가 0행0열의 요소는 처리하지 못하므로 따로 처리합니다, 배열요소를 채울 count변수가 1이 아닌 2에서 시작하는 이유도 같습니다. 


	while (count < (row * col)-1) {
		while (in_col + 1 < col && arr[in_row][in_col + 1] == 0) {//만약 다음 수를 입력할 자리의 열이 배열의 열 크기보다 작고 아직 기입이 되지 않았다면 해당 자리에 수를 기입합니다.
			in_col++;
			arr[in_row][in_col] = count++;
		}
		while (in_row + 1 < row && arr[in_row + 1][in_col] == 0) {//만약 다음 수를 입력할 자리의 행이 배열의 0보다 크거나 같고 아직 기입이 되지 않았다면 해당 자리에 수를 기입합니다
			in_row++;
			arr[in_row][in_col] = count++;
		}
		while (in_col - 1 >= 0 && arr[in_row][in_col - 1] == 0) {//만약 다음 수를 입력할 자리의 열이 배열의 열 크기보다 작고 아직 기입이 되지 않았다면 해당 자리에 수를 기입합니다
			in_col--; 
			arr[in_row][in_col] = count++;
		}
		while (in_row - 1 >= 0 && arr[in_row - 1][in_col] == 0) {//만약 다음 수를 입력할 자리의 행이 배열의 0보다 크거나 같고 아직 기입이 되지 않았다면 해당 자리에 수를 기입합니다
			in_row--;
			arr[in_row][in_col] = count++;
		}
	}

	//배열 전체 요소를 출력합니다.
	for (int i = 0; i < row; i++) 
	{
		for (int j = 0; j < col; j++) 
		{
			printf(" %d", arr[i][j]);
		}
		printf("\n");
	}
	return 0;
}
