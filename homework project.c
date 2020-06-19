#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1
#define MAX_VERTEX 20 /* you can change value 20 */
int V = 0;			// �������� V ������ ����
int s_top = -1;		// ������ top
int q_top = -1;		// ť�� top
int stack[MAX_VERTEX];	// ����
int queue[MAX_VERTEX];	// ť
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
	setvbuf(stdout, NULL, _IONBF, 0);      // ���� ���
	printf("[2019038028]    [������]\n");   // �� �̸�
	char command;
	int key, v;
	int a1, a2;
	Graph* G = NULL;	// �׷��� ���� �� �ʱ�ȭ

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
		scanf(" %c", &command);			// command �Է�

		switch (command) {
		case 'z': case 'Z':
			G = createGraph(G);		// �׷��� ����
			break;
		case 'q': case 'Q':
			destroyGraph(G);		// �׷��� ����
			break;
		case 'i': case 'I':
			printf("Your Key = ");		// Ű �Է� ��
			scanf("%d", &key);
			insertVertex(G, key);		// ���� insert
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteVertex(G, key);		// ���� ����
			break;

		case 'e': case 'E':
			printf("insert a1->a2\n");		// ���� insert
			printf("a1 : ");
			scanf("%d", &a1);
			printf("a2 : ");
			scanf("%d", &a2);				// a1->a2
			insertEdge(G, a1, a2);
			break;
		case 't': case 'T':
			printf("delete a1->a2\n");		// ���� ����
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

// �׷��� ����
Graph* createGraph(Graph* g) {
	int i;
	if (g != NULL) {			// �׷����� �̹� ���� �� ���
		destroyGraph(g);		// �׷��� �ı�
		printf("������� �ʽ��ϴ� �ٽ� z �������� \n");		// ������ ���
		return NULL;		// return
	}
	g = (Graph*)malloc(sizeof(Graph));		// �׷��� ����
	printf("Graph Size : ");		// ������ �Է��϶�� ��¹�
	scanf("%d", &V);				// ������ �Է�
	g->vlist = (VertexHead*)malloc(V * sizeof(VertexHead));		// ������ ��ŭ ���� �Ҵ�
	for (i = 0; i < V; i++) {		// for�� ���ư��鼭
		g->vlist[i].head = NULL;		// ��带 NULL�� �ʱ�ȭ
	}
	return g;		// �׷��� return
}

/* Free Graph */
int destroyGraph(Graph* h) {
	Vertex* temp = (Vertex*)malloc(sizeof(Vertex));		// �̵���ų ���
	Vertex* prev = (Vertex*)malloc(sizeof(Vertex));		// �� ���� �� ���
	int i;		// for���� ����
	for (i = 0; i < V; i++) {			// prev, temp�� �̵���Ű�� �� ��� free
		temp = h->vlist[i].head;		// ���� �ʱ�ȭ
		prev = h->vlist[i].head;		// ���� �ʱ�ȭ
		while (temp) {					// temp�� NULL�ϋ�����
			prev = temp;				// prev = temp
			temp = temp->link;			// temp �̵�
			free(prev);					// prev �ʱ�ȭ
		}
	}
	return 0;
}

// ���� �߰�
void insertVertex(Graph* h, int key) {
	Vertex* node = (Vertex*)malloc(sizeof(Vertex));		// node ����
	int i;
	node->num = key;		// node�� key ����
	node->link = NULL;
	// ���� ���� V
	for (i = 0; i < V; i++) {		// �׷��� size ����
		if (h->vlist[i].head == NULL) {		// ���� head�� ���������
			h->vlist[i].head = node;		// node ����
			break;	//break
		}
		if (h->vlist[i].head->num == key) {		// �̹� key�� ���� �� ���
			printf("Already exist key!!\n");		// ������
			break;		//break;
		}
	}

}
// ��ũ�� �̾��� ������ �����ϰ� ��ĭ�� �ڿ� ���� �մ��
void deleteVertex(Graph* h, int key) {
	int i, j;
	for (i = 0; i < V; i++) {				// ���� ����, head->link = NULL
		if (h->vlist[i].head != NULL && h->vlist[i].head->num == key) {			// vertex�� �����ϸ�
				h->vlist[i].head = NULL;		// ���� head ���
				for (j = i; j < V-1; j++) {
					h->vlist[j].head = h->vlist[j + 1].head;		// ���� head �Ʒ��� ���
					deleteEdge(h, h->vlist[j].head->num, key);		// ���� edge ������ key�� �ش��ϴ� edge ����
				}
				h->vlist[j].head = NULL;				// ������ �ߺ��Ǵ� head = NULL
		}
	}
}

int insertEdge(Graph* h, int a1, int a2) {
	int i, j, t1, t2;
	Vertex* node1 = (Vertex*)malloc(sizeof(Vertex));		// a1�� �̾��� ���
	Vertex* node2 = (Vertex*)malloc(sizeof(Vertex));		// a2�� �̾��� ���
	Vertex* temp = (Vertex*)malloc(sizeof(Vertex));			// �̵��� ����
	Vertex* prev = (Vertex*)malloc(sizeof(Vertex));			// ������ ����
	t1 = -1;		//t1, t2�ʱ�ȭ
	t2 = -1;
	for (i = 0; i < V; i++) {					// �����ϰ��� �ϴ� ��尡 �����ϴ��� Ȯ��
		if (h->vlist[i].head == NULL) {			// head�� ���������
			continue;							// i++
		}
		if (h->vlist[i].head->num == a1)		// a1�� �ش��ϴ� ���� ����
			t1 = i;
		else if (h->vlist[i].head->num == a2)	// a2�� �ش��ϴ� ���� ����
			t2 = i;
	}
	node1->num = a1;		// node1->num�� a1 ����
	node1->link = NULL;
	node2->num = a2;		// node2->num�� a2 ����
	node2->link = NULL;


	// ����
	if (t1 != -1 && t2 != -1) {			// ���� a1, a2 �Ѵ� �����ϸ�
		prev = h->vlist[t1].head;
		temp = h->vlist[t1].head->link;
		for (j = 0; j < MAX_VERTEX; j++) {	// �Ȱ����� �� ������ ���� ��ó��
			if (prev->num == node2->num) {
				printf("Already exist key!!\n");
				return 0;
			}
			if (temp == NULL) {		// temp�� NULL�̸�
				prev->link = node2;		// ���� �߰�
				break;
			}
			else {
				prev = temp;		// �̵�
				temp = temp->link;	// �̵�
			}
		}
		prev = h->vlist[t2].head;		// prev = ����
		temp = h->vlist[t2].head->link;	// temp = ���� ��ġ
		for (j = 0; j < MAX_VERTEX; j++) {
			if(prev->num == node1->num)		// delte ���� ��ó��
				return 0;
			if (temp == NULL) {		// �� ����
				prev->link = node1;
				return 0;
			}
			else {
				prev = temp;		// prev = ����
				temp = temp->link;	// temp = ���� ��ġ
			}
		}

	}
	if(t1 == -1 || t2 == -1)		// ���ų� �̹� �����ϴ� �����̶�� ������
		printf("Not or Already Your Vertex in Graph!!\n");
	return 0;
}
int deleteEdge(Graph* h, int a1, int a2) {
	if (h->vlist[a1].head == NULL) {			// ��ó��
		return 0;
	}
	Vertex* temp = (Vertex*)malloc(sizeof(Vertex));
	Vertex* temp2 = (Vertex*)malloc(sizeof(Vertex));
	Vertex* prev = (Vertex*)malloc(sizeof(Vertex));
	int i, t1,t2;
	t1 = -1;		// t1, t2 �ʱ�ȭ
	t2 = -1;
	for (i = 0; i < V; i++) {					// �����ϰ��� �ϴ� ��尡 �����ϴ��� Ȯ��
		if (h->vlist[i].head == NULL) {
			continue;
		}
		if (h->vlist[i].head->num == a1)
			t1 = i;
		else if (h->vlist[i].head->num == a2)
			t2 = i;
	}
	if (t1 != -1 && t2 != -1) {
		prev = h->vlist[t1].head;		// prev = ����
		temp = h->vlist[t1].head->link;	// temp = ���� ��ġ
		for (i = 0; i < MAX_VERTEX; i++) {
			if (temp->num == a2) {		// ���� ���� �� ���� �����ϸ�
				if (temp->link == NULL) {		// ���� temp ������ NULL�̸�
					prev->link = NULL;			// prev->link = NULL
					return 0;
				}
				else {
					temp2 = temp;		// temp2�� �� ���� ��
					prev->link = temp->link;		// prev->link = ���� ���
					free(temp2);		// temp2 free
					return 0;
				}
			}
			else if (temp->link != NULL) {
				prev = temp;				// prev �̵�
				temp = temp->link;			// temp �̵�
			}

		}
	}
	if (t1 == -1 || t2 == -1)		// ã�� ���� ������
		return 0;		// return
	return 0;
}
int printGraph(Graph* h) {
	int i;
	Vertex* temp = (Vertex*)malloc(sizeof(Vertex));
	for (i = 0; i < V; i++) {					// ���� ��尡 ä������ �ʾ��� ���
		if (h->vlist[i].head == NULL) {				// i++�� �� for�� ����
			continue;
		}
		printf("%d ", h->vlist[i].head->num);		// head->num���
		temp = h->vlist[i].head->link;		// �̵���ų �غ�
		while(temp != NULL){		//while( temp != NULL )
			printf("->");
			printf("%d ", temp->num);		// ���� ���
			temp = temp->link;		// temp  = temp->link
		}
		printf("\n");		// �ٹٲ�
	}
	return 0;		// return
}

void depthFS(Graph* h, int v) {		// v = ���� ������ ��

	printf("������ ���ϰڽ��ϴ�....\n");
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
