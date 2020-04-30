/*
 ============================================================================
 Name        : homework6-singly-linked-list.c
 Author      : Ji Un Song
 Version     :
 Copyright   :
 Description :
 ============================================================================
 */
 /*
  * single linked list
  *
  *  Data Structures
  *  Department of Computer Science
  *  at Chungbuk National University
  */


#include<stdio.h>
#include<stdlib.h>

  /* 필요한 헤더파일 추가 */

typedef struct Node {			// 각각의 노드
	int key;
	struct Node* link;
} listNode;

typedef struct Head {			// 헤드 노드
	struct Node* first;
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);			// 헤드노드를 initialize 하기위한 함수 선언
int freeList(headNode* h);				// 메모리 해제

int insertFirst(headNode* h, int key);		// 헤드노드에 값 대입하느 함수 선언
int insertNode(headNode* h, int key);		// 리스트에 오름차순으로 값을 넣는 함수 선언
int insertLast(headNode* h, int key);		// 리스트의 마지막 노드에 값을 넣는 함수 선언

int deleteFirst(headNode* h);			// 헤드노드의 값을 지우는 함수 선언
int deleteNode(headNode* h, int key);	// 지정 노드의 값을 지우는 함수 선언
int deleteLast(headNode* h);			// 마지막 노드의 값을 지우는 함수 선언
int invertList(headNode* h);			// 리스트를 역순으로 재 배치하는 함수 선언

void printList(headNode* h);			// 리스트의 값들을 순서대로 출력하는 함수 선언

int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);		// 버퍼 허용
	printf("[2019038028]    [송지운]\n");		// 내 이름
	char command;		// 커맨드 변수
	int key;		// 사용자가 입력할 key 변수
	headNode* headnode = NULL;		// 헤드노드 변수를 null로 초기화

	do {			//do-while문
		printf("----------------------------------------------------------------\n");					// 메뉴판
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");			// 사용자에게 커맨드 입력하라는 출력문
		scanf(" %c", &command);			// 사용자가 커맨드를 입력

		switch (command) {					// 각 커맨드에 맞는 함수 호출
		case 'z': case 'Z':
			headnode = initialize(headnode);
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

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h) {
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while (p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));		// 한 node를 listnode의 크기만큼 할당
	node->key = key;			// node에 key값을 대입

	node->link = h->first;		// node의 link에 h->first를 가리키도록함
	h->first = node;		// h->first = node

	return 0;	// 0값을 반환
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */

int insertNode(headNode* h, int key) {
	if (h->first == NULL) {		// 만약 리스트가 비어있으면
		insertFirst(h, key);		// insertfirst 함수 호출
		return 0;
	}
	listNode* temp = malloc(sizeof(listNode));		// 들어갈 노드를 저장할 temp 동적 할당
	listNode* src_list = h->first;		// 리스트에 저장된 key의 값을 찾아낼 src_list
	temp->key = key;		// temp노드의 key에 key를 저장
	while (1) {		// 무한루프

		if (src_list != NULL) {		// 리스트가 비어있지 않으면
			if (src_list->key > key) {	// 만약 처음 비교한 값이 들어갈 값보다 크면
				insertFirst(h, key);		// 헤드노드에 들어감
				return 0;		// 함수에서 나감
			}
			if (src_list->link == NULL || src_list->link->key >= key) {		// 만약 마지막이거나 리스트의 중간에 값이 있으면
				temp->link = src_list->link;	// temp->link 를 src_list가 가리키던 link에 대입
				src_list->link = temp;		// src_list가 가리키던 link를 temp로 대입
				return 0;		// 함수에서 나감
			}
			else
				src_list = src_list->link;		// 앞의 것이 아닐 시에 다음 링크로 이동
		}
		else {
			temp->link = NULL;		// 비어있다는 것이으면 temp를 헤드노드로 대입
			src_list = temp;
			return 0;		// 함수에서 나감
		}

	}

	return 0;		// 0값을 반환
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	listNode* temp = malloc(sizeof(listNode));		// 입력받은 값을 받기위한 새로운 노드
	listNode* last = h->first;		// 마지막에 대입하기 위해 last라는 노드를 h->first로 대입
	temp->key = key;		// temp에 값을 저장
	temp->link = NULL;		// 마지막에 넣기 때문에 temp->link를 NULL로 저장
	if (h->first == NULL) {		// 만약 h->first가 NULL이라면
		h->first = temp;	// 헤드 노드에 temp를 대입
		return 0;	// 함수에서 나감
	}
	while (1) {		// 무한루프
		if (last->link == NULL) {		// 만약 last node가 리스트 끝에 도착했다면
			last->link = temp;		// last->link에 temp를 대입
			break;		// 무한루프에서 나감
		}
		else {		// 그게 아니면, 다음 link로 이동
			last = last->link;
		}
	}

	return 0;		// 0값을 반환
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	if(h->first == NULL)		// 만약 리스트가 비어 있으면
		return 0;		// 함수에서 나감

	h->first = h->first->link;		// 첫번째 노드를 지움

	return 0;		// 0값을 반환
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	if(h->first == NULL)		// 만약 헤드노드가 비어있으면
		return 0;		// 함수에서 나감
	listNode* trail = h->first;		// 뒤따라오는 리스트
	listNode* del = trail->link;	// 메인 리스트
	if (trail->key == key) {		// 만약 처음의 값이 key와 같다면
		deleteFirst(h);		// delete first
		return 0;		// 함수에서 나감
	}
	while (1) {		// 무한 루프
		if (del->key == key) {		// 만약 메인 리스트의 key가 key와 같다면
			trail->link = del->link;		// 이전의 link = 현재 link
			del->link = NULL;			// 현재 link 를 연결 해제
			return 0;		// 함수를 나감
		}
		else {		// 그게 아니면
			trail = trail->link;		// link 이동
			del = del->link;		// link 이동
		}
	}
	return 0;	// 0값을 반환
}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	if(h->first == NULL)			// 만약 헤드노드가 비어 있다면,
		return 0;		// 함수를 나감
	listNode* del_last = h->first;		// 마지막에 지울 노드
	if (del_last->link == NULL) {		// 만약 처음노드부터 null이라면
		deleteFirst(h);		// deletefirst
		return 0;	// 함수를 나감
	}
	while (1) {		// 무한루프
		if (del_last->link->link == NULL) {		// 만약 현재노드 다음의 노드의 link가 null이라면
			del_last->link = NULL;		// 현재노드의 link를 null로 대입해서 이후의 노드를 삭제
			return 0;		// 함수에서 나감
		}
		del_last = del_last->link;		// 그게 아니면 link 이동
	}
	return 0;	// 0값을 반환
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	if(h->first == NULL)		// 만약 헤드노드가 비어있으면
		return 0;		// 함수에서 나감
	listNode* born = h->first->link;		// 헤드노드가 가리키는 link 를 born으로 선언
	listNode* trail = h->first;		// 헤드노드를 trail로 선언
	int key;		// 역순으로 하기 전에 저장할 key
	if (born == NULL)		// 만약 처음 link부터 비어있다면,
		return 0;		// 아무것도 안하고 return 0
	while (born != NULL) {		// link가 null일때까지
		key = born->key;		// key를 born-> key로 일단 저장
		insertFirst(h, key);		// key를 리스트 맨 앞으로 일단 저장
		born = born->link;		// link 이동
	}							// 현재 상태: 만약 원래 리스트 값이 1 2 3 이었으면 3 2 1 2 3이 되어있음
	trail->link = NULL;			// 거기서 처음 지정된 link를 null로 해서 3 2 1만 남도록 함
	return 0;		// 0값을 반환
}


void printList(headNode* h) {
	int i = 0;			// item의 개수
	listNode* p;		// 리스트 이동하면서 출력할 변수

	printf("\n---PRINT\n");

	if (h == NULL) {		// 만약 리스트가 비어있다면,
		printf("Nothing to print....\n");		// 없다는걸 출력
		return;		// 함수 나감
	}

	p = h->first;		// p를 h->first로 대입

	while (p != NULL) {		// 리스트 끝까지
		printf("[ [%d]=%d ] ", i, p->key);		// 값과 리스트 item의 개수 출력
		p = p->link;		// link이동
		i++;		// i += 1
	}

	printf("  items = %d\n", i);		// item의 개수 출력
}
