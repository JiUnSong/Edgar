/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
 /* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;		// value
	struct Node* llink;			// 왼쪽 링크
	struct Node* rlink;			// 오른쪽 링크
} listNode;



typedef struct Head {
	struct Node* first;			//HeadNode
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
		 singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
		- initialize와 왜 다른지 이해 할것
		 - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);      // 버퍼 허용
	printf("[2019038028]    [송지운]\n");	// 내 이름
	char command;
	int key;
	headNode* headnode = NULL;

	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {			// 이중 포인터로 받은 initialize 함수
	headNode* temp = (headNode*)malloc(sizeof(headNode));		// 받은 헤더노드를 초기화 시킬 변수
	if (*h != NULL)		// 만약 헤드가 비어있지 않으면 free
		freeList(*h);
	temp->first = NULL;			// temp->first를 초기화
	*h = temp;		// 헤더노드에 넣기
	return 1;
}

int freeList(headNode* h) {			// 메모리 해지 함수
	listNode* p = h->first;		// p = h->first

	listNode* prev = NULL;		// 잠시 저장할 노드
	while (p != NULL) {		// 노드의 끝까지
		prev = p;		// 현재노드를 저장
		p = p->rlink;		// p를 이동하면서
		free(prev);		// 메모리 해지
	}
	free(h);		// 헤드도 해지
	return 0;		// 0값을 반환
}


void printList(headNode* h) {		//프린트 함수
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 /* list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	if (h->first == NULL) {		// 노드가 비어있으면
		insertFirst(h, key);		// 첫 노드에 insert
		return 0;		// 함수에서 나감
	}
	listNode* lastNode = h->first;		// lastNode = h->first
	listNode* add_last = malloc(sizeof(listNode));		// 마지막에 넣을 노드
	add_last->rlink = NULL;		// rlink를 NULL로 초기화
	add_last->key = key;		// key를 초기화
	while (lastNode->rlink != NULL)		// 노드의 끝으로 감
		lastNode = lastNode->rlink;

	lastNode->rlink = add_last;		// 마지막 노드의 rlink에 노드를 추가
	add_last->llink = lastNode;		// 추가된 노드의 llink에 lastNode를 대입
	return 0;		// 0값을 반환
}


/**
 * list의 마지막 노드 삭제
 */

int deleteLast(headNode* h) {
	if (h->first == NULL)		// 노드가 비어 있으면
		return 0;		// 나감
	if (h->first->rlink == NULL) {		// 노드가 1개면
		deleteFirst(h);		// 첫 노드를 지움
		return 0;		// 나감
	}

	listNode* trail = h->first;		// trail = h->first
	while (1) {		// 무한루프
		if (trail->rlink->rlink == NULL) {		// 만약 trail->rlink->rlink == NULL 이면
			trail->rlink = NULL;		// 끝 노드 하나를 지움
			return 0;		// 0값을 반환
		}
		trail = trail->rlink;		// 아니면 노드를 이동한다.
	}

	return 0; // 0값을 반환
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));		// 추가될 노드
	node->key = key;		// 노드key에 key 대입
	node->rlink = h->first;		// 노드 rlink에 h->first대입
	h->first = node;		// h->first에 추가된 노드 대입
	return 0;		// 0 값을 반환
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	h->first = h->first->rlink;	// 첫 노드 지움

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	if (h->first == NULL)		// 리스트가 비어있으면
		return 0;		// 나감
	listNode* born = h->first->rlink;		// born = h->first->rlink
	listNode* node = h->first;		// node = h->first
	int key;		// 잠시 저장할 key
	if (born == NULL)		// 만약 노드가 1개라면
		return 0;		// 그대로 놔둠
	while (born != NULL) {		// 리스트 끝까지
		key = born->key;		// key 저장
		insertFirst(h,key);		// 들어갈때마다 첫 노드에 저장
		born = born->rlink;		// 링크 옮겨가며
	}
	node->rlink = NULL;		// 마지막 노드의 rllink = NULL
	return 0;		// 0값을 반환
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	if (h->first == NULL) {		// 노드가 비어있으면
		insertFirst(h, key);		// 첫노드에 저장
		return 0;		// 0값을 반환
	}
	listNode* temp = malloc(sizeof(listNode));		// 추가할 노드
	listNode* trail = h->first;		// trail = h->first
	temp->key = key;		// temp에 key를 저장
	if (trail->key > key) {		// 첫 노드의 key가 들어갈 key보다 크면
		insertFirst(h, key);		// first에 저장
		return 0;		// 0값을 반환
	}
	while (1)		// 무한루프
	{
			if (trail->rlink != NULL && trail->rlink->key >= key) {		// 마지막노드가 아니고, 노드의 key가 들어갈 key보다 크면
				temp->rlink = trail->rlink;		// temp의 rlink를 기존의 rlink에 대입
				trail->rlink = temp;		// 기존의 rlink는 temp를 가리키도록
				temp->llink = trail;		// temp의 llink는 기존의 노드를 가리킴
				return 0;		// 0값을 반환
			}
			if (trail->rlink == NULL) {		// 마지막 노드일 경우까지 오면
				insertLast(h, key);		// 마지막노드에 대입
				return 0;		// 0값을 반환
			}
				trail = trail->rlink;		// 리스트의 끝까지 이동하면서
	}
	return 0;		// 0값을 반환
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	if (h->first == NULL)		// 리스트가 비어있으면
		return 0;		// 0값을 반환
	listNode* node = h->first;		// node = h->first
	if (node->key == key) {		// 만약 처음부터 찾는 key가 나오면
		deleteFirst(h);		// 첫 노드 삭제
		return 0;		// 0값을 반환
	}
	while (1) {		// 무한루프
		if (node->rlink->rlink == NULL)			// 마지막 노드의 바로 이전노드에 위치하고
			if (node->rlink->key == key) {		// 마지막 노드의 key가 지울 key값이면
				deleteLast(h);		// 마지막 노드 삭제
				return 0;		// 0값을 반환
			}
		if (node->rlink->rlink != NULL && node->rlink->key == key) {		// 마지막노드가 아니고 찾는 key이면
			node->rlink = node->rlink->rlink;		// 중간 노드 삭제
			return 0;		// 0값을 반환
		}
		else {		// 아니면
			node = node->rlink;		// 노드 이동
		}
	}
	return 1;
}
