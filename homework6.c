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

  /* �ʿ��� ������� �߰� */

typedef struct Node {			// ������ ���
	int key;
	struct Node* link;
} listNode;

typedef struct Head {			// ��� ���
	struct Node* first;
}headNode;


/* �Լ� ����Ʈ */
headNode* initialize(headNode* h);			// ����带 initialize �ϱ����� �Լ� ����
int freeList(headNode* h);				// �޸� ����

int insertFirst(headNode* h, int key);		// ����忡 �� �����ϴ� �Լ� ����
int insertNode(headNode* h, int key);		// ����Ʈ�� ������������ ���� �ִ� �Լ� ����
int insertLast(headNode* h, int key);		// ����Ʈ�� ������ ��忡 ���� �ִ� �Լ� ����

int deleteFirst(headNode* h);			// ������� ���� ����� �Լ� ����
int deleteNode(headNode* h, int key);	// ���� ����� ���� ����� �Լ� ����
int deleteLast(headNode* h);			// ������ ����� ���� ����� �Լ� ����
int invertList(headNode* h);			// ����Ʈ�� �������� �� ��ġ�ϴ� �Լ� ����

void printList(headNode* h);			// ����Ʈ�� ������ ������� ����ϴ� �Լ� ����

int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);		// ���� ���
	printf("[2019038028]    [������]\n");		// �� �̸�
	char command;		// Ŀ�ǵ� ����
	int key;		// ����ڰ� �Է��� key ����
	headNode* headnode = NULL;		// ����� ������ null�� �ʱ�ȭ

	do {			//do-while��
		printf("----------------------------------------------------------------\n");					// �޴���
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");			// ����ڿ��� Ŀ�ǵ� �Է��϶�� ��¹�
		scanf(" %c", &command);			// ����ڰ� Ŀ�ǵ带 �Է�

		switch (command) {					// �� Ŀ�ǵ忡 �´� �Լ� ȣ��
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

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if (h != NULL)
		freeList(h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h) {
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
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
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));		// �� node�� listnode�� ũ�⸸ŭ �Ҵ�
	node->key = key;			// node�� key���� ����

	node->link = h->first;		// node�� link�� h->first�� ����Ű������
	h->first = node;		// h->first = node

	return 0;	// 0���� ��ȯ
}


/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */

int insertNode(headNode* h, int key) {
	if (h->first == NULL) {		// ���� ����Ʈ�� ���������
		insertFirst(h, key);		// insertfirst �Լ� ȣ��
		return 0;
	}
	listNode* temp = malloc(sizeof(listNode));		// �� ��带 ������ temp ���� �Ҵ�
	listNode* src_list = h->first;		// ����Ʈ�� ����� key�� ���� ã�Ƴ� src_list
	temp->key = key;		// temp����� key�� key�� ����
	while (1) {		// ���ѷ���

		if (src_list != NULL) {		// ����Ʈ�� ������� ������
			if (src_list->key > key) {	// ���� ó�� ���� ���� �� ������ ũ��
				insertFirst(h, key);		// ����忡 ��
				return 0;		// �Լ����� ����
			}
			if (src_list->link == NULL || src_list->link->key >= key) {		// ���� �������̰ų� ����Ʈ�� �߰��� ���� ������
				temp->link = src_list->link;	// temp->link �� src_list�� ����Ű�� link�� ����
				src_list->link = temp;		// src_list�� ����Ű�� link�� temp�� ����
				return 0;		// �Լ����� ����
			}
			else
				src_list = src_list->link;		// ���� ���� �ƴ� �ÿ� ���� ��ũ�� �̵�
		}
		else {
			temp->link = NULL;		// ����ִٴ� �������� temp�� ������ ����
			src_list = temp;
			return 0;		// �Լ����� ����
		}

	}

	return 0;		// 0���� ��ȯ
}

/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {
	listNode* temp = malloc(sizeof(listNode));		// �Է¹��� ���� �ޱ����� ���ο� ���
	listNode* last = h->first;		// �������� �����ϱ� ���� last��� ��带 h->first�� ����
	temp->key = key;		// temp�� ���� ����
	temp->link = NULL;		// �������� �ֱ� ������ temp->link�� NULL�� ����
	if (h->first == NULL) {		// ���� h->first�� NULL�̶��
		h->first = temp;	// ��� ��忡 temp�� ����
		return 0;	// �Լ����� ����
	}
	while (1) {		// ���ѷ���
		if (last->link == NULL) {		// ���� last node�� ����Ʈ ���� �����ߴٸ�
			last->link = temp;		// last->link�� temp�� ����
			break;		// ���ѷ������� ����
		}
		else {		// �װ� �ƴϸ�, ���� link�� �̵�
			last = last->link;
		}
	}

	return 0;		// 0���� ��ȯ
}


/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {
	if(h->first == NULL)		// ���� ����Ʈ�� ��� ������
		return 0;		// �Լ����� ����

	h->first = h->first->link;		// ù��° ��带 ����

	return 0;		// 0���� ��ȯ
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {
	if(h->first == NULL)		// ���� ����尡 ���������
		return 0;		// �Լ����� ����
	listNode* trail = h->first;		// �ڵ������ ����Ʈ
	listNode* del = trail->link;	// ���� ����Ʈ
	if (trail->key == key) {		// ���� ó���� ���� key�� ���ٸ�
		deleteFirst(h);		// delete first
		return 0;		// �Լ����� ����
	}
	while (1) {		// ���� ����
		if (del->key == key) {		// ���� ���� ����Ʈ�� key�� key�� ���ٸ�
			trail->link = del->link;		// ������ link = ���� link
			del->link = NULL;			// ���� link �� ���� ����
			return 0;		// �Լ��� ����
		}
		else {		// �װ� �ƴϸ�
			trail = trail->link;		// link �̵�
			del = del->link;		// link �̵�
		}
	}
	return 0;	// 0���� ��ȯ
}

/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {
	if(h->first == NULL)			// ���� ����尡 ��� �ִٸ�,
		return 0;		// �Լ��� ����
	listNode* del_last = h->first;		// �������� ���� ���
	if (del_last->link == NULL) {		// ���� ó�������� null�̶��
		deleteFirst(h);		// deletefirst
		return 0;	// �Լ��� ����
	}
	while (1) {		// ���ѷ���
		if (del_last->link->link == NULL) {		// ���� ������ ������ ����� link�� null�̶��
			del_last->link = NULL;		// �������� link�� null�� �����ؼ� ������ ��带 ����
			return 0;		// �Լ����� ����
		}
		del_last = del_last->link;		// �װ� �ƴϸ� link �̵�
	}
	return 0;	// 0���� ��ȯ
}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {
	if(h->first == NULL)		// ���� ����尡 ���������
		return 0;		// �Լ����� ����
	listNode* born = h->first->link;		// ����尡 ����Ű�� link �� born���� ����
	listNode* trail = h->first;		// ����带 trail�� ����
	int key;		// �������� �ϱ� ���� ������ key
	if (born == NULL)		// ���� ó�� link���� ����ִٸ�,
		return 0;		// �ƹ��͵� ���ϰ� return 0
	while (born != NULL) {		// link�� null�϶�����
		key = born->key;		// key�� born-> key�� �ϴ� ����
		insertFirst(h, key);		// key�� ����Ʈ �� ������ �ϴ� ����
		born = born->link;		// link �̵�
	}							// ���� ����: ���� ���� ����Ʈ ���� 1 2 3 �̾����� 3 2 1 2 3�� �Ǿ�����
	trail->link = NULL;			// �ű⼭ ó�� ������ link�� null�� �ؼ� 3 2 1�� ������ ��
	return 0;		// 0���� ��ȯ
}


void printList(headNode* h) {
	int i = 0;			// item�� ����
	listNode* p;		// ����Ʈ �̵��ϸ鼭 ����� ����

	printf("\n---PRINT\n");

	if (h == NULL) {		// ���� ����Ʈ�� ����ִٸ�,
		printf("Nothing to print....\n");		// ���ٴ°� ���
		return;		// �Լ� ����
	}

	p = h->first;		// p�� h->first�� ����

	while (p != NULL) {		// ����Ʈ ������
		printf("[ [%d]=%d ] ", i, p->key);		// ���� ����Ʈ item�� ���� ���
		p = p->link;		// link�̵�
		i++;		// i += 1
	}

	printf("  items = %d\n", i);		// item�� ���� ���
}
