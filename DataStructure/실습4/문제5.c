#include<stdio.h>//표준 입출력 헤더파일입니다.

#pragma warning(disable:4996)//scanf()함수로 인한 보안상의 경고 4996을 발생시키지 않도록 지시합니다.

int main()
{
	int row = 0, col = 0;
	int arr[100][100] = { 0 };
	scanf("%d %d", &row, &col);
	int start_row = 0,start_col = 0, in_row = 0, in_col = 0, count = 1;

	while (start_col + 1 <= col) {//먼저 0행의 요소들 부터 대각선의 수를 채워나가는 반복문입니다.
		in_col = start_col;
		in_row = 0;
		if (in_row == 0){//배열의 0행의 요소들이 해당 반복문에서 처리되지 못하므로 따로 조건문으로 처리됩니다.
			arr[in_row][in_col] = count;
			count++;
		}
		while (in_col - 1 >= 0 && in_row + 1 < row){// 1행의 요소에서 해당 요소의 대각선 요소들까지 채워나가는 반복문입니다.
			in_col--;
			in_row++;
			arr[in_row][in_col] = count;
			count++;
		}
		start_col++;
	}
	start_row++;
	while (count <= row*col){//최대 열-1의 열 요소들부터 대각선의 수를 채워나가는 반복문이빈다.
		in_row = start_row;
		in_col = col - 1;
		if ((in_col == col - 1)||(in_row==row-1)){//배열의 최대 열 -1의 요소들이거나 배열의 최대 행-1의 요소들은 해당 반복문에서 처리되지 못하기에 따로 조건문으로 처리됩니다.
			arr[in_row][in_col] = count;
			count++;
		}
		while (in_col - 1 >= 0 && in_row + 1 < row) {// 배열의 최대 열 - 2의 요소들 에서 해당 요소의 대각선 요소들까지 채워나가는 반복문입니다.
			in_col--;
			in_row++;
			arr[in_row][in_col] = count;
			count++;
		}
		start_row++;
	}
	//배열을 출력합니다.
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
