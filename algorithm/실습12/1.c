/*
[ 문제 1 ] (위상순서 찾기) 주어진 방향그래프 G에 대해 다음과 같이 수행하는 프로그램을
작성하라. 1) G가 방향 비싸이클 그래프(directed acyclic graph: DAG)면 위상순서(topological
order)를 구해 인쇄. 2) G에 방향 싸이클(directed cycle)이 존재하면 위상순서를 구할 수 없으므로 0을 인쇄. 힌트:
1. 이 문제의 경우 그래프를 인접리스트 구조로 표현하는 것이 시간 성능 면에서
유리하며 배열로 구현하는 편이 코딩에 용이하다. 아래의 “알고리즘 설계 팁” 역시
이 기준으로 제공된다.
2. 위상 정렬 알고리즘에는 두 가지 버전이 있다. 첫째 깊이우선탐색(DFS)을 응용하는
버전, 둘째 각 정점의 진입차수(in-degree)를 이용하는 버전이다. 본 문제 해결을
위해 두 번째 버전을 사용하라. 이 버전은 그래프 G가 DAG면 위상순서를 구하고
그렇지 않으면(즉, 방향싸이클이 존재하면) 일부 정점에 대해 순위를 매기지 않은
채로 정지하므로 DAG가 아님을 알 수 있다. 상세 내용은 아래의 “알고리즘 설계
팁”을 참고할 것. 주의:
1. 방향싸이클의 존재여부 검사와 위상순서 구하기를 별도 작업으로 수행하면 전체
실행시간이 늘어나므로, 위상순서를 구하는 과정에서 방향싸이클의 존재 여부를
확인할 수 있도록 작성해야 한다.
2. 원래 어떤 그래프에 대한 위상순서는 여러 개 있을 수 있다. 하지만 채점편의 상, 이
문제는 그 가운데 단 한 개의 위상순서만 출력 가능하도록 다음 사항을 준수해야
한다. 아래의 “알고리즘 설계 팁”도 이에 맞게 작성되어 있다. 1) 그래프의 부착리스트 구축 시, 새로 입력되는 간선에 대한 노드를 리스트의 맨
앞에 삽입해야 한다(이전 실습에서는 정점번호의 오름차순으로 부착리스트 유지).
2) 위상 정렬 알고리즘에서 최초로 진입간선의 개수가 0인 정점을 찾을 때, 정점번호
순서대로 조사해야 한다.
<알고리즘 실습> 방향그래프- 2 -
입출력 형식:
1) main 함수는 아래 형식으로 방향그래프를 표준입력 받는다. 입력 : 첫 번째 라인 : 정점 수(n)
두 번째 라인 : 정점들의 이름(단순 문자 - 예: 영문자, 숫자 등)
세 번째 라인 : 방향간선 수(m)
이후 m개의 라인 : 방향간선 정보

입력1
3 ↦ n = 정점 수
A B C ↦ 정점들
3 ↦ m = 간선 수
A B ↦ 간선 정보
C A ↦ 간선 정보
C B ↦ 간선 정보

출력1
C A B

입력2
4 ↦ n = 정점 수
A B C D ↦ 정점들
6 ↦ m = 간선 수
A B ↦ 간선 정보
C A ↦ 간선 정보
C B ↦ 간선 정보
A D ↦ 간선 정보
B D ↦ 간선 정보
D C ↦ 간선 정보
출력2
0

입력3
8 ↦ n = 정점 수
A B C D E F G H ↦ 정점들
11 ↦ m = 간선 수
A B ↦ 간선 정보
C B ↦ 간선 정보
A D ↦ 간선 정보
C D ↦ 간선 정보
B D ↦ 간선 정보
D E ↦ 간선 정보
E F ↦ 간선 정보
E H ↦ 간선 정보
E G ↦ 간선 정보
F G ↦ 간선 정보
H G ↦ 간선 정보
출력3
A C B D E H F G
  */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#pragma warning(disable : 4996)


typedef struct EDGE 
{
    int dest;
    struct EDGE* next;
} EDGE;


typedef struct NODE 
{
    char name;      
    int in_degree;  
    EDGE* out_edges; 
} NODE;

NODE* G = NULL; 
int n, m;           
int* queue;         
int front = 0, rear = 0;
int* topOrder;      

// 함수 선언
int indexOf(char vName);
void insertVertex(char vName, int i);
void insertDirectedEdge(int uIndex, int wIndex);
void enqueue(int v);
int dequeue();
bool isEmpty();
void buildGraph();
void topologicalSort();
void freeGraph();

int main() 
{
    buildGraph();
    topologicalSort();
    if (topOrder[0] == 0) 
    {
        printf("0\n");
    }
    else
    {
        for (int i = 1; i <= n; i++) 
        {
            printf("%c ", G[topOrder[i]].name);
        }
        printf("\n");
    }
    freeGraph();
    return 0;
}

int indexOf(char vName) 
{
    for (int i = 0; i < n; i++)
    {
        if (G[i].name == vName) 
        {
            return i;
        }
    }
}

void buildGraph() 
{
    scanf("%d", &n);
    G = (NODE*)malloc(n * sizeof(NODE));

    for (int i = 0; i < n; i++) 
    {
        char vName;
        scanf(" %c", &vName);
        insertVertex(vName, i);
    }
    //간선처리
    scanf("%d", &m);

    // 간선 데이터 입력
    for (int i = 0; i < m; i++) 
    {
        char uName =0, wName= 0;
        scanf(" %c %c", &uName, &wName);
        int uIndex = indexOf(uName);
        int wIndex = indexOf(wName);
        insertDirectedEdge(uIndex, wIndex);
    }
}
void insertVertex(char vName, int i) 
{
    G[i].name = vName;
    G[i].in_degree = 0;
    G[i].out_edges = NULL;
}
void insertDirectedEdge(int uIndex, int wIndex) 
{
    EDGE* newEdge = (EDGE*)malloc(sizeof(EDGE));
    newEdge->dest = wIndex;
    newEdge->next = G[uIndex].out_edges;
    G[uIndex].out_edges = newEdge;
    G[wIndex].in_degree++;
}

void enqueue(int v) 
{
    queue[rear++] = v;
}

int dequeue() 
{
    return queue[front++];
}

bool isEmpty() 
{
    return front == rear;
}


void topologicalSort()
{
    queue = (int*)malloc(n * sizeof(int));
    topOrder = (int*)malloc((n + 1) * sizeof(int));
    front = rear = 0;

    for (int i = 0; i < n; i++) 
    {
        if (G[i].in_degree == 0) 
        {
            enqueue(i);
        }
    }

    int t = 1;
    while (!isEmpty()) 
    {
        int u = dequeue();
        topOrder[t++] = u;
        EDGE* cur = G[u].out_edges;
        while (cur != NULL) 
        {
            int v = cur->dest;
            G[v].in_degree--;
            if (G[v].in_degree == 0) 
            {
                enqueue(v);
            }
            cur = cur->next;
        }
    }
    if (t <= n) 
    {
        topOrder[0] = 0;
    }
    else 
    {
        topOrder[0] = 1;
    }
}

void freeGraph() 
{
    for (int i = 0; i < n; i++) 
    {
        EDGE* cur = G[i].out_edges;
        while (cur != NULL) 
        {
            EDGE* temp = cur;
            cur = cur->next;
            free(temp);
        }
    }
    free(G);
    free(queue);
    free(topOrder);
}
