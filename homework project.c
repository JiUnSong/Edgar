#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1
#define MAX_VERTEX 20 /* you can change value 20 */
int V = 0;			// 전역변수 V 정점의 개수
int s_top = -1;		// 스택의 top
int q_top = -1;		// 큐의 top
int stack[MAX_VERTEX];	// 스택
int queue[MAX_VERTEX];	// 큐
typedef struct Vertex {
	int num; /* vertex number */
	struct Vertex* link; /* link to a next adjacent vertext */
} Vertex;
typedef struct VertexHead {
	Vertex* head; /* linked list of all adjacent vertices */
} VertexHead;
typedef struct Graph {
	VertexHead* vlist; /* list of all vertices: vlist[MAX_VERTEX] */
} Graph;

Graph* createGraph(Graph* g);
int destroyGraph(Graph* g);
void insertVertex(Graph* h, int key);
void deleteVertex(Graph* h, int key);
int insertEdge(Graph* h, int a1, int a2); /* No vertax, No Edge */
int deleteEdge(Graph* h, int a1, int a2);
void depthFS(Graph* h, int v);
int printGraph(Graph* h);
void push(int key);
int pop();

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);      // 버퍼 허용
	printf("[2019038028]    [송지운]\n");   // 내 이름
	char command;
	int key, v;
	int a1, a2;
	Graph* G = NULL;	// 그래프 선언 후 초기화

	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                     #Adjacency List                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" createGraph       = z       DepthFS	=  s                   \n");
		printf(" Insert Vertex     = i       DeleteVertex      = d \n");
		printf(" Insert Edge    = e		   DeleteEdge    = t \n");
		printf(" print Graph  = p      Quit          = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);			// command 입력

		switch (command) {
		case 'z': case 'Z':
			G = createGraph(G);		// 그래프 생성
			break;
		case 'q': case 'Q':
			destroyGraph(G);		// 그래프 삭제
			break;
		case 'i': case 'I':
			printf("Your Key = ");		// 키 입력 후
			scanf("%d", &key);
			insertVertex(G, key);		// 정점 insert
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteVertex(G, key);		// 정점 삭제
			break;

		case 'e': case 'E':
			printf("insert a1->a2\n");		// 간선 insert
			printf("a1 : ");
			scanf("%d", &a1);
			printf("a2 : ");
			scanf("%d", &a2);				// a1->a2
			insertEdge(G, a1, a2);
			break;
		case 't': case 'T':
			printf("delete a1->a2\n");		// 간선 삭제
			printf("a1 : ");
			scanf("%d", &a1);
			printf("a2 : ");
			scanf("%d", &a2);		// a1->a2
			deleteEdge(G, a1, a2);
			break;
		case 'p': case 'P':
			printGraph(G);			// print graph
			break;
		case 's': case'S':
			printf("StartPoint value = ");
			scanf("%d", &v);
			depthFS(G, v);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

// 그래프 생성
Graph* createGraph(Graph* g) {
	int i;
	if (g != NULL) {			// 그래프가 이미 존재 할 경우
		destroyGraph(g);		// 그래프 파괴
		printf("비어있지 않습니다 다시 z 누르세요 \n");		// 에러문 출력
		return NULL;		// return
	}
	g = (Graph*)malloc(sizeof(Graph));		// 그래프 생성
	printf("Graph Size : ");		// 사이즈 입력하라는 출력문
	scanf("%d", &V);				// 사이즈 입력
	g->vlist = (VertexHead*)malloc(V * sizeof(VertexHead));		// 사이즈 만큼 동적 할당
	for (i = 0; i < V; i++) {		// for문 돌아가면서
		g->vlist[i].head = NULL;		// 헤드를 NULL로 초기화
	}
	return g;		// 그래프 return
}

/* Free Graph */
int destroyGraph(Graph* h) {
	Vertex* temp = (Vertex*)malloc(sizeof(Vertex));		// 이동시킬 노드
	Vertex* prev = (Vertex*)malloc(sizeof(Vertex));		// 값 저장 할 노드
	int i;		// for문의 변수
	for (i = 0; i < V; i++) {			// prev, temp를 이동시키며 각 노드 free
		temp = h->vlist[i].head;		// 헤드로 초기화
		prev = h->vlist[i].head;		// 헤드로 초기화
		while (temp) {					// temp가 NULL일떄까지
			prev = temp;				// prev = temp
			temp = temp->link;			// temp 이동
			free(prev);					// prev 초기화
		}
	}
	return 0;
}

// 정점 추가
void insertVertex(Graph* h, int key) {
	Vertex* node = (Vertex*)malloc(sizeof(Vertex));		// node 생성
	int i;
	node->num = key;		// node에 key 넣음
	node->link = NULL;
	// 전역 변수 V
	for (i = 0; i < V; i++) {		// 그래프 size 동안
		if (h->vlist[i].head == NULL) {		// 만약 head가 비어있으면
			h->vlist[i].head = node;		// node 대입
			break;	//break
		}
		if (h->vlist[i].head->num == key) {		// 이미 key가 존재 할 경우
			printf("Already exist key!!\n");		// 에러문
			break;		//break;
		}
	}

}
// 링크로 이어진 값들을 삭제하고 빈칸을 뒤에 헤드로 앞당김
void deleteVertex(Graph* h, int key) {
	int i, j;
	for (i = 0; i < V; i++) {				// 정점 삭제, head->link = NULL
		if (h->vlist[i].head != NULL && h->vlist[i].head->num == key) {			// vertex가 존재하면
				h->vlist[i].head = NULL;		// 현재 head 비움
				for (j = i; j < V-1; j++) {
					h->vlist[j].head = h->vlist[j + 1].head;		// 위의 head 아래로 당김
					deleteEdge(h, h->vlist[j].head->num, key);		// 만약 edge 있으면 key에 해당하는 edge 삭제
				}
				h->vlist[j].head = NULL;				// 마지막 중복되는 head = NULL
		}
	}
}

int insertEdge(Graph* h, int a1, int a2) {
	int i, j, t1, t2;
	Vertex* node1 = (Vertex*)malloc(sizeof(Vertex));		// a1에 이어질 노드
	Vertex* node2 = (Vertex*)malloc(sizeof(Vertex));		// a2에 이어질 노드
	Vertex* temp = (Vertex*)malloc(sizeof(Vertex));			// 이동할 변수
	Vertex* prev = (Vertex*)malloc(sizeof(Vertex));			// 저장할 변수
	t1 = -1;		//t1, t2초기화
	t2 = -1;
	for (i = 0; i < V; i++) {					// 연결하고자 하는 헤드가 존재하는지 확인
		if (h->vlist[i].head == NULL) {			// head가 비어있으면
			continue;							// i++
		}
		if (h->vlist[i].head->num == a1)		// a1에 해당하는 값이 존재
			t1 = i;
		else if (h->vlist[i].head->num == a2)	// a2에 해당하는 값이 존재
			t2 = i;
	}
	node1->num = a1;		// node1->num에 a1 대입
	node1->link = NULL;
	node2->num = a2;		// node2->num에 a2 대입
	node2->link = NULL;


	// 연결
	if (t1 != -1 && t2 != -1) {			// 만약 a1, a2 둘다 존재하면
		prev = h->vlist[t1].head;
		temp = h->vlist[t1].head->link;
		for (j = 0; j < MAX_VERTEX; j++) {	// 똑같은걸 또 연결할 때의 전처리
			if (prev->num == node2->num) {
				printf("Already exist key!!\n");
				return 0;
			}
			if (temp == NULL) {		// temp가 NULL이면
				prev->link = node2;		// 간선 추가
				break;
			}
			else {
				prev = temp;		// 이동
				temp = temp->link;	// 이동
			}
		}
		prev = h->vlist[t2].head;		// prev = 이전
		temp = h->vlist[t2].head->link;	// temp = 현재 위치
		for (j = 0; j < MAX_VERTEX; j++) {
			if(prev->num == node1->num)		// delte 후의 후처리
				return 0;
			if (temp == NULL) {		// 값 저장
				prev->link = node1;
				return 0;
			}
			else {
				prev = temp;		// prev = 이전
				temp = temp->link;	// temp = 현재 위치
			}
		}

	}
	if(t1 == -1 || t2 == -1)		// 없거나 이미 존재하는 정점이라는 에러문
		printf("Not or Already Your Vertex in Graph!!\n");
	return 0;
}
int deleteEdge(Graph* h, int a1, int a2) {
	if (h->vlist[a1].head == NULL) {			// 전처리
		return 0;
	}
	Vertex* temp = (Vertex*)malloc(sizeof(Vertex));
	Vertex* temp2 = (Vertex*)malloc(sizeof(Vertex));
	Vertex* prev = (Vertex*)malloc(sizeof(Vertex));
	int i, t1,t2;
	t1 = -1;		// t1, t2 초기화
	t2 = -1;
	for (i = 0; i < V; i++) {					// 연결하고자 하는 헤드가 존재하는지 확인
		if (h->vlist[i].head == NULL) {
			continue;
		}
		if (h->vlist[i].head->num == a1)
			t1 = i;
		else if (h->vlist[i].head->num == a2)
			t2 = i;
	}
	if (t1 != -1 && t2 != -1) {
		prev = h->vlist[t1].head;		// prev = 이전
		temp = h->vlist[t1].head->link;	// temp = 현재 위치
		for (i = 0; i < MAX_VERTEX; i++) {
			if (temp->num == a2) {		// 만약 삭제 할 값이 존재하면
				if (temp->link == NULL) {		// 만약 temp 다음이 NULL이면
					prev->link = NULL;			// prev->link = NULL
					return 0;
				}
				else {
					temp2 = temp;		// temp2에 값 저장 후
					prev->link = temp->link;		// prev->link = 다음 노드
					free(temp2);		// temp2 free
					return 0;
				}
			}
			else if (temp->link != NULL) {
				prev = temp;				// prev 이동
				temp = temp->link;			// temp 이동
			}

		}
	}
	if (t1 == -1 || t2 == -1)		// 찾는 값이 없으면
		return 0;		// return
	return 0;
}
int printGraph(Graph* h) {
	int i;
	Vertex* temp = (Vertex*)malloc(sizeof(Vertex));
	for (i = 0; i < V; i++) {					// 만약 헤드가 채워지지 않았을 경우
		if (h->vlist[i].head == NULL) {				// i++한 후 for문 진행
			continue;
		}
		printf("%d ", h->vlist[i].head->num);		// head->num출력
		temp = h->vlist[i].head->link;		// 이동시킬 준비
		while(temp != NULL){		//while( temp != NULL )
			printf("->");
			printf("%d ", temp->num);		// 간선 출력
			temp = temp->link;		// temp  = temp->link
		}
		printf("\n");		// 줄바꿈
	}
	return 0;		// return
}

void depthFS(Graph* h, int v) {		// v = 시작 정점의 값

	printf("구현을 못하겠습니다....\n");
	return;
	/*int visited[MAX_VERTEX], i,a, t = -1;
	Vertex* w;
	visited[v] = TRUE;
	push(h->vlist[v].head->num);
	printf("%d ", h->vlist[v].head->num);
	while (s_top != -1) {
		w = h->vlist[v].head;
		while (w) {
			if (!visited[w->num]) {
				push(w->num);
			}
		}
	}*/
}
void push(int key) {
	if (s_top >= MAX_VERTEX - 1)
		return;
	stack[++s_top] = key;
}
int pop() {
	if (s_top == -1)
		return 0;
	return stack[s_top--];
}
