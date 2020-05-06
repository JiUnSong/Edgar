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
 /* �ʿ��� ������� �߰� if necessary */


typedef struct Node {
	int key;		// value
	struct Node* llink;			// ���� ��ũ
	struct Node* rlink;			// ������ ��ũ
} listNode;



typedef struct Head {
	struct Node* first;			//HeadNode
}headNode;

/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ����
		 singly-linked-list�� initialize�� �������� ���� �Ұ� */
int initialize(headNode** h);

/* note: freeList�� �̱������͸� �Ű������� ����
		- initialize�� �� �ٸ��� ���� �Ұ�
		 - ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */
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
	setvbuf(stdout, NULL, _IONBF, 0);      // ���� ���
	printf("[2019038028]    [������]\n");	// �� �̸�
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


int initialize(headNode** h) {			// ���� �����ͷ� ���� initialize �Լ�
	headNode* temp = (headNode*)malloc(sizeof(headNode));		// ���� �����带 �ʱ�ȭ ��ų ����
	if (*h != NULL)		// ���� ��尡 ������� ������ free
		freeList(*h);
	temp->first = NULL;			// temp->first�� �ʱ�ȭ
	*h = temp;		// �����忡 �ֱ�
	return 1;
}

int freeList(headNode* h) {			// �޸� ���� �Լ�
	listNode* p = h->first;		// p = h->first

	listNode* prev = NULL;		// ��� ������ ���
	while (p != NULL) {		// ����� ������
		prev = p;		// �����带 ����
		p = p->rlink;		// p�� �̵��ϸ鼭
		free(prev);		// �޸� ����
	}
	free(h);		// ��嵵 ����
	return 0;		// 0���� ��ȯ
}


void printList(headNode* h) {		//����Ʈ �Լ�
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
 /* list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {
	if (h->first == NULL) {		// ��尡 ���������
		insertFirst(h, key);		// ù ��忡 insert
		return 0;		// �Լ����� ����
	}
	listNode* lastNode = h->first;		// lastNode = h->first
	listNode* add_last = malloc(sizeof(listNode));		// �������� ���� ���
	add_last->rlink = NULL;		// rlink�� NULL�� �ʱ�ȭ
	add_last->key = key;		// key�� �ʱ�ȭ
	while (lastNode->rlink != NULL)		// ����� ������ ��
		lastNode = lastNode->rlink;

	lastNode->rlink = add_last;		// ������ ����� rlink�� ��带 �߰�
	add_last->llink = lastNode;		// �߰��� ����� llink�� lastNode�� ����
	return 0;		// 0���� ��ȯ
}


/**
 * list�� ������ ��� ����
 */

int deleteLast(headNode* h) {
	if (h->first == NULL)		// ��尡 ��� ������
		return 0;		// ����
	if (h->first->rlink == NULL) {		// ��尡 1����
		deleteFirst(h);		// ù ��带 ����
		return 0;		// ����
	}

	listNode* trail = h->first;		// trail = h->first
	while (1) {		// ���ѷ���
		if (trail->rlink->rlink == NULL) {		// ���� trail->rlink->rlink == NULL �̸�
			trail->rlink = NULL;		// �� ��� �ϳ��� ����
			return 0;		// 0���� ��ȯ
		}
		trail = trail->rlink;		// �ƴϸ� ��带 �̵��Ѵ�.
	}

	return 0; // 0���� ��ȯ
}


/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));		// �߰��� ���
	node->key = key;		// ���key�� key ����
	node->rlink = h->first;		// ��� rlink�� h->first����
	h->first = node;		// h->first�� �߰��� ��� ����
	return 0;		// 0 ���� ��ȯ
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {
	h->first = h->first->rlink;	// ù ��� ����

	return 0;
}



/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {
	if (h->first == NULL)		// ����Ʈ�� ���������
		return 0;		// ����
	listNode* born = h->first->rlink;		// born = h->first->rlink
	listNode* node = h->first;		// node = h->first
	int key;		// ��� ������ key
	if (born == NULL)		// ���� ��尡 1�����
		return 0;		// �״�� ����
	while (born != NULL) {		// ����Ʈ ������
		key = born->key;		// key ����
		insertFirst(h,key);		// �������� ù ��忡 ����
		born = born->rlink;		// ��ũ �Űܰ���
	}
	node->rlink = NULL;		// ������ ����� rllink = NULL
	return 0;		// 0���� ��ȯ
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {
	if (h->first == NULL) {		// ��尡 ���������
		insertFirst(h, key);		// ù��忡 ����
		return 0;		// 0���� ��ȯ
	}
	listNode* temp = malloc(sizeof(listNode));		// �߰��� ���
	listNode* trail = h->first;		// trail = h->first
	temp->key = key;		// temp�� key�� ����
	if (trail->key > key) {		// ù ����� key�� �� key���� ũ��
		insertFirst(h, key);		// first�� ����
		return 0;		// 0���� ��ȯ
	}
	while (1)		// ���ѷ���
	{
			if (trail->rlink != NULL && trail->rlink->key >= key) {		// ��������尡 �ƴϰ�, ����� key�� �� key���� ũ��
				temp->rlink = trail->rlink;		// temp�� rlink�� ������ rlink�� ����
				trail->rlink = temp;		// ������ rlink�� temp�� ����Ű����
				temp->llink = trail;		// temp�� llink�� ������ ��带 ����Ŵ
				return 0;		// 0���� ��ȯ
			}
			if (trail->rlink == NULL) {		// ������ ����� ������ ����
				insertLast(h, key);		// ��������忡 ����
				return 0;		// 0���� ��ȯ
			}
				trail = trail->rlink;		// ����Ʈ�� ������ �̵��ϸ鼭
	}
	return 0;		// 0���� ��ȯ
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {
	if (h->first == NULL)		// ����Ʈ�� ���������
		return 0;		// 0���� ��ȯ
	listNode* node = h->first;		// node = h->first
	if (node->key == key) {		// ���� ó������ ã�� key�� ������
		deleteFirst(h);		// ù ��� ����
		return 0;		// 0���� ��ȯ
	}
	while (1) {		// ���ѷ���
		if (node->rlink->rlink == NULL)			// ������ ����� �ٷ� ������忡 ��ġ�ϰ�
			if (node->rlink->key == key) {		// ������ ����� key�� ���� key���̸�
				deleteLast(h);		// ������ ��� ����
				return 0;		// 0���� ��ȯ
			}
		if (node->rlink->rlink != NULL && node->rlink->key == key) {		// ��������尡 �ƴϰ� ã�� key�̸�
			node->rlink = node->rlink->rlink;		// �߰� ��� ����
			return 0;		// 0���� ��ȯ
		}
		else {		// �ƴϸ�
			node = node->rlink;		// ��� �̵�
		}
	}
	return 1;
}
