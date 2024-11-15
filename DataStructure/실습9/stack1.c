#include <stdio.h> // 표준 입출력 함수를 사용하기 위한 헤더 파일입니다.
#include <stdlib.h> // 동적 메모리 할당을 위한 함수들을 사용하기 위한 헤더 파일입니다.
#include <string.h> // 문자열 관련 함수를 사용하기 위한 헤더 파일입니다
#pragma warning(disable:4996) // scanf() 함수 사용 시 발생할 수 있는 보안 경고를 비활성화합니다.

int t = -1; // 스택의 top 위치를 나타내는 변수. 스택이 비었을 때는 -1입니다.


void emptyStackException(); // 스택이 비었을 때 호출되는 함수입니다.
void fullStackException(); // 스택이 가득 찼을 때 호출되는 함수입니다.
void duplicate(char stack[], int N); // 스택의 최상단 요소를 복제하는 함수입니다.
void push(char stack[], char e, int N); // 스택에 요소를 추가하는 함수입니다.
int isEmpty(); // 스택이 비어 있는지 검사하는 함수입니다.
char pop(char stack[]); // 스택의 최상단 요소를 제거하고 반환하는 함수입니다.
int size(); // 스택에 저장된 요소의 수를 반환하는 함수입니다.
void upRotate(char stack[], int n); // 스택의 상단 n개 요소를 위로 회전시키는 함수입니다.
void downRotate(char stack[], int n); // 스택의 상단 n개 요소를 아래로 회전시키는 함수입니다.
void print(char stack[]); // 스택의 모든 요소를 출력하는 함수입니다.
void peek(char stack[]); // 스택의 최상단 요소를 출력하는 함수입니다.

int main() {
	char cmd[8], input; // 사용자로부터 입력받은 명령어와 문자를 저장할 변수입니다.
	int N = 0; // 스택의 최대 크기입니다.
	scanf("%d", &N); // 사용자로부터 스택의 최대 크기를 입력받습니다.
	char* stack = (char*)malloc(sizeof(char)*N); // 스택으로 사용할 동적 배열입니다.
	int cmd_count = 0; // 실행할 명령어의 수입니다.
	scanf("%d", &cmd_count); // 사용자로부터 명령어의 수를 입력받습니다.

	for (int i = 0; i < cmd_count; i++) {
		scanf("%s", cmd); // 명령어를 입력받습니다.

		if (strcmp(cmd, "PUSH") == 0) 
		{
			getchar();
			scanf("%c", &input); // 문자 하나를 입력받습니다.
			getchar();
			push(stack, input, N); // 입력받은 문자를 스택에 PUSH합니다
		}
		else if (strcmp(cmd, "POP") == 0) 
		{
			getchar();
			pop(stack); // 스택에서 POP 연산 수행합니다.
		}
		else if (strcmp(cmd, "PEEK") == 0) 
		{
			getchar();
			peek(stack); // 스택의 최상단 요소를 출력합니다.
		}
		else if (strcmp(cmd, "DUP") == 0) 
		{
			getchar();
			duplicate(stack, N); // 스택의 최상단 요소를 복제합니다.
		}
		else if (strcmp(cmd, "UpR") == 0) 
		{
			int up;
			getchar();
			scanf("%d", &up); // 회전할 요소의 수를 입력받습니다.
			getchar();
			upRotate(stack, up); // 스택의 상단 요소를 위로 회전합니다.
		}
		else if (strcmp(cmd, "DownR") == 0) 
		{
			int down;
			getchar();
			scanf("%d", &down); // 회전할 요소의 수를 입력받습니다.
			getchar();
			downRotate(stack, down);// 스택의 하단 요소를 아래로 회전합니다.
		}
		else if (strcmp(cmd, "PRINT") == 0)
		{
			getchar();
			print(stack);//스택의 모든 요소를 출력합니다.
		}
	}
	
}



void emptyStackException()// 스택이 비었을 때 호출되는 함수입니다.
{
	printf("Stack Empty\n");
}

void fullStackException()// 스택이 가득 찼을 때 호출되는 함수입니다.
{
	printf("Stack FULL\n");
}

void duplicate(char stack[], int N)// 스택의 최상단 요소를 복제하는 함수입니다.
{
	if (t == N - 1)//스택이 꽉차있는 경우 예외를 출력합니다.
	{
		fullStackException();
		return;
	}
	char e = pop(stack);//스택의 최상단 요소를 얻어 두번 넣습니다.
	push(stack, e, N);
	push(stack, e, N);
}

void push(char stack[], char e, int N)// 스택에 요소를 추가하는 함수입니다.
{
	if (t == N - 1)//스택이 꽉차있는 경우 예외를 출력합니다.
	{
		fullStackException();
		return;
	}
	t += 1;
	stack[t] = e;//스택 최상단에 문자를 넣습니다.
}

int isEmpty()// 스택이 비어 있는지 검사하는 함수입니다.
{
	if (t == -1)
	{
		return 0;
	}
	else
	{
		return - 1;
	}
}

char pop(char stack[])// 스택의 최상단 요소를 제거하고 반환하는 함수입니다.
{
	if (!isEmpty())//스택이 비어있는 경우 예외를 출력합니다.
	{
		emptyStackException();
		return '\0';
	}
	t -= 1;
	return stack[t + 1];//이전 스택의 최상단에 위치했던 문자를 반환합니다.
}

int size()// 스택에 저장된 요소의 수를 반환하는 함수입니다.
{
	return t + 1;
}

void upRotate(char stack[], int n)// 스택의 상단 n개 요소를 위로 회전시키는 함수입니다.
{
	if ((t + 1) < n || n <= 0)
	{
		return;
	}
	char temp = stack[t];//최상단의 문자를 따로 저장하고 한칸씩 문자들을 옮깁니다.
	for (int i = t - 1; i > t - n; i--)
	{
		stack[i + 1] = stack[i];
	}
	stack[t - n + 1] = temp;//따로 저장한 문자를 t-n+1위치에 기입합니다.
}
void downRotate(char stack[], int n)// 스택의 상단 n개 요소를 아래로 회전시키는 함수입니다.
{
	if ((t + 1) < n || n <= 0)
	{
		return;
	}
	char temp = stack[t - n + 1];//t-n+1 위치의 문자를 따로 저장하고 한칸씩 문자들을 옮깁니다.
	for (int i = t - n + 1; i < t; i++)
	{
		stack[i] = stack[i + 1];
	}
	stack[t] = temp;//따로 저장한 문자를 최상단에 기입합니다.
}
void print(char stack[])// 스택의 모든 요소를 출력하는 함수입니다.
{
	for (int i = t; i >= 0; i--)
	{
		printf("%c", stack[i]);
	}
	printf("\n");
}
void peek(char stack[])// 스택의 최상단 요소를 출력하는 함수입니다.
{
	if (!isEmpty())//스택이 비어있는 경우 예외를 출력합니다.
	{
		emptyStackException();
		return;
	}
	printf("%c\n", stack[t]);//스택의 최상단 요소를 출력합니다.
}
