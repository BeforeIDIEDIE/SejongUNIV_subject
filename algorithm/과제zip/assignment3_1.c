#include<stdio.h>
#include<stdlib.h>

#pragma warning(disable:4996)

#define max(a,b) (((a)>(b))?(a):(b))

typedef struct NODE
{
	int value;
	int height; 
	struct NODE* parent; //부모 노드
	struct NODE* lChild; //왼쪽 자식 노드
	struct NODE* rChild; //오른쪽 자식 노드
}NODE;

NODE* getNODE()//새로운 노드를 할당하고 초기화하는 함수
{
	NODE* brandNew = (NODE*)malloc(sizeof(NODE));
	brandNew->parent = NULL; 
	brandNew->lChild = NULL;
	brandNew->rChild = NULL;
	return brandNew;
}

int isExternal(NODE* w);//외부 노드 여부 확인함수
int isInternal(NODE* w);//내부 노드 여부 확인함수
NODE* treeSearch(NODE* w, int k);//트리에서 특정 값을 검색하는 함수
int findElement(NODE* root, int k);//특정 값을 찾는 함수
void print_tree(NODE* root);//트리를 전위 순회하는 함수
void expandExternal(NODE* w);//외부 노드를 확장하는 함수
int updateHeight(NODE* w);//노드의 높이를 갱신하는 함수
int isBalanced(NODE* w);//노드의 균형 상태를 확인하는 함수
NODE* restructure(NODE** pq, NODE* x, NODE* y, NODE* z);//트리의 구조를 재구성하는 함수
void searchAndFixAfterInsertion(NODE** q, NODE* w);//삽입 후 트리의 균형을 재조정하는 함수
void insertItem(NODE** p, int k);//트리에 새 항목을 삽입하는 함수
void freeTree(NODE* root);//모든 트리의 노드를 후위순위순서로 메모리 해제시키는 함수


void main()
{
	int input = 0;
	char cmd = 0;
	NODE* root = getNODE();

	while (1)
	{
		scanf(" %c", &cmd);
		switch (cmd)
		{
		case 'i'://삽입 기능
		{
			scanf("%d", &input);
			insertItem(&root, input);
			break;
		}
		case 's'://검색 기능
		{
			scanf("%d", &input);
			if (findElement(root, input))
			{
				printf("%d\n", input);
			}
			else
			{
				printf("X\n");//값이 없으면 X 출력
			}
			break;
		}
		case 'p'://전위 순회
		{
			print_tree(root);
			printf("\n");
			break;
		}
		case 'q'://프로그램 종료
		{
			freeTree(root);
			return 0;
			break;
		}
		}
	}
	return;
}

int isExternal(NODE* w)
{
	if (w->lChild == NULL && w->rChild == NULL)//자식 노드가 없으면 외부 노드
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int isInternal(NODE* w)
{
	return !isExternal(w);
}

NODE* treeSearch(NODE* w, int k)//트리에서 특정 값을 찾는 재귀 함수
{
	if (isExternal(w))//외부 노드에 도달한 경우
	{
		return w;
	}
	if (w->value == k)//값이 찾고자 하는 값과 같으면 노드 반환
	{
		return w;
	}
	else if (k < w->value)//찾고자 하는 값이 현재 노드 값보다 작으면 왼쪽으로 이동
	{
		return treeSearch(w->lChild, k);
	}
	else//찾고자 하는 값이 현재 노드 값보다 크면 오른쪽으로 이동
	{
		return treeSearch(w->rChild, k);
	}
}

int findElement(NODE* root, int k)//특정 값이 트리에 있는지 확인하는 함수
{
	NODE* w = treeSearch(root, k);
	if (isExternal(w))//외부 노드에 도달하면 값이 없음
	{
		return 0;
	}
	else
	{
		return 1;//내부 노드에 값이 있음
	}
}

void print_tree(NODE* root)//트리를 전위 순회하는 함수
{
	if (isExternal(root))//외부 노드에 도달하면 종료
	{
		return;
	}
	printf(" %d", root->value);
	if (isInternal(root->lChild))//왼쪽 자식 순회
	{
		print_tree(root->lChild);
	}
	if (isInternal(root->rChild))//오른쪽 자식 순회
	{
		print_tree(root->rChild);
	}
}

void expandExternal(NODE* w)//외부 노드를 내부 노드로 확장하는 함수
{
	w->lChild = getNODE(); 
	w->rChild = getNODE();
	w->lChild->parent = w; 
	w->rChild->parent = w; 
	return;
}


int updateHeight(NODE* w)//노드의 높이를 갱신하는 함수
{
	int h = 0;
	h = max(w->lChild->height, w->rChild->height) + 1;//자식 높이 중 큰 값 + 1
	if (h != w->height)//높이가 변경되었으면
	{
		w->height = h;//새로운 높이로 설정
		return 1;
	}
	else
	{
		return 0;//높이에 변화가 없으면 0 반환
	}
}

int isBalanced(NODE* w)//노드의 균형 상태 확인
{
	if (w->lChild->height >= w->rChild->height)
	{
		return (w->lChild->height) - (w->rChild->height) < 2;//차이가 2보다 작으면 균형
	}
	else
	{
		return (w->rChild->height) - (w->lChild->height) < 2;
	}
}

NODE* restructure(NODE** pq, NODE* x, NODE* y, NODE* z)//트리의 구조를 재조정하는 함수
{
	NODE* a = NULL;
	NODE* b = NULL;
	NODE* c = NULL;
	NODE* T0 = NULL;
	NODE* T1 = NULL;
	NODE* T2 = NULL;
	NODE* T3 = NULL;
	if (z->value < y->value && y->value < x->value)//단일 회전: LL
	{
		a = z, b = y, c = x;
		T0 = a->lChild, T1 = b->lChild, T2 = c->lChild, T3 = c->rChild;
	}
	else if (z->value > y->value && y->value > x->value)//단일 회전: RR
	{
		a = x, b = y, c = z;
		T0 = a->lChild, T1 = a->rChild, T2 = b->rChild, T3 = c->rChild;
	}
	else if (y->value > x->value && x->value > z->value)//이중 회전: RL
	{
		a = z, b = x, c = y;
		T0 = a->lChild, T1 = b->lChild, T2 = b->rChild, T3 = c->rChild;
	}
	else//이중 회전: LR
	{
		a = y, b = x, c = z;
		T0 = a->lChild, T1 = b->lChild, T2 = b->rChild, T3 = c->rChild;
	}

	if (z->parent == NULL)//z가 루트 노드인 경우
	{
		*pq = b;
		b->parent = NULL;
	}
	else if (z->parent->lChild == z)//z가 부모의 왼쪽 자식일 때
	{
		z->parent->lChild = b;
		b->parent = z->parent;
	}
	else//z가 부모의 오른쪽 자식일 때
	{
		z->parent->rChild = b;
		b->parent = z->parent;
	}

	a->lChild = T0;//T0를 a의 왼쪽 자식으로 설정
	T0->parent = a;
	a->rChild = T1;//T1을 a의 오른쪽 자식으로 설정
	T1->parent = a;
	updateHeight(a);

	c->lChild = T2;//T2를 c의 왼쪽 자식으로 설정
	T2->parent = c;
	c->rChild = T3;//T3을 c의 오른쪽 자식으로 설정
	T3->parent = c;
	updateHeight(c);

	b->lChild = a;//a를 b의 왼쪽 자식으로 설정
	a->parent = b;
	b->rChild = c;//c를 b의 오른쪽 자식으로 설정
	c->parent = b;
	updateHeight(b);

	return b;
}

void searchAndFixAfterInsertion(NODE** q, NODE* w)//삽입 후 균형 조정
{
	NODE* z = NULL;
	NODE* y = NULL;
	NODE*x= NULL;
	w->lChild->height = 0;//새 노드 자식들의 높이를 0으로 설정
	w->rChild->height = 0;
	w->height = 1;//새 노드의 높이 설정
	if (w->parent == NULL)//루트 노드일 때
	{
		return;
	}
	z = w->parent;//부모 노드로 이동
	while (updateHeight(z) && isBalanced(z))//높이 갱신 및 균형 확인
	{
		if (z->parent == NULL)
		{
			return;
		}
		z = z->parent;
	}
	if (isBalanced(z))//균형이 유지되면 종료
	{
		return;
	}
	if (z->lChild->height > z->rChild->height)//y 선택
	{
		y = z->lChild;
	}
	else
	{
		y = z->rChild;
	}

	if (y->lChild->height > y->rChild->height)//x 선택
	{
		x = y->lChild;
	}
	else
	{
		x = y->rChild;
	}
	restructure(q, x, y, z);//재조정
	return;
}

void insertItem(NODE** p, int k)//트리에 새 값을 삽입하는 함수
{
	NODE* w = treeSearch(*p, k);//트리에서 삽입 위치 찾기

	if (isInternal(w))//이미 값이 있으면 종료
	{
		return;
	}
	else
	{
		w->value = k;//값 설정
		expandExternal(w);//외부 노드를 확장하여 자식 노드 생성
		searchAndFixAfterInsertion(p, w);//삽입 후 균형 조정
		return;
	}
}


void freeTree(NODE* root) 
{
	if (isExternal(root))//외부노드일시 바로 root 메모리 해제
	{
		free(root);
		return;
	}
	if (root->lChild != NULL)//왼쪽 자식노드 메모리 해제 
	{
		freeTree(root->lChild);
	}
	if (root->rChild != NULL) //오른쪽 자식노드 메모리 해제 
	{
		freeTree(root->rChild);
	}
	free(root);//root 메모리 해제
}
