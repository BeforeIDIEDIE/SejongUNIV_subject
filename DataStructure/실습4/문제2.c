#include <stdio.h>//표준 입출력 헤더파일입니다.

#pragma warning(disable:4996)//scanf()함수로 인한 보안상의 경고 4996을 발생시키지 않도록 지시합니다.

int main() 
{
	int arr[100] = { 0 }, command[100] = { 0 };//command는 위치바꿈정보가 저장될 배열입니다.

	int input1 = 0,input2 = 0, pre = 0, cur = 0;
	
	scanf("%d", &input1);// 배열의 요소들을 입력받습니다.
	for (int i = 0; i < input1; i++) {
		scanf("%d", &arr[i]);
	}
	
	scanf("%d", &input2);

	for (int i = 0; i < input2; i++) {
		scanf("%d", &command[i]);// 위치바꿈정보를 입력받습니다.
	}

	for (int i = 0; i < input2; i++) {
		if (i == 0){// 위치바꿈정보의 첫번째 요소는 따로 처리됩니다.
			pre = pre = arr[command[0]];
			continue;
		}
		cur = arr[command[i]];//현재 입력된 위치바꿈정보를 저장합니다.
		arr[command[i]] = pre;// 이전 위치바꿈정보를 현재 입력받은 인덱스 위치에 저장합니다. 
		pre = cur;//이전 위치바꿈정보를 갱신합니다.

	}

	printf(" ");//배열을 출력합니다.
	for (int i = 0; i < input1; i++) {
		printf("%d ", arr[i]);
	}

	return 0;
}
