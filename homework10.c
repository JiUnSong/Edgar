/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;			// 스택의 최상위 원소

Node* pop();		// 스택의 최상위 원소를 삭제하면서 반환
void push(Node* aNode);		// 스택 최상위에 원소 push

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


void printStack();



int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);      // 버퍼 허용
	printf("[2019038028]    [송지운]\n");   // 내 이름
	char command;
	int key;
	Node* head = NULL;

	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)			// 재귀 방식의 중위 순회
{
	if (ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224
 */			// stack
void iterativeInorder(Node* node)
{
	top = -1;
	for (;;) {
		for (; node; node = node->left)
			push(node);				// 스택에 잘린 노드들이 저장
		node = pop(); // 스택 top의 값을 node에 저장하고 트리 상위 값 pop()
		if (!node) break; // 공백이면 break;
		printf(" [%d] ", node->key);			// print
		node = node->right;		// 중위 순회
	}
}

/**
 * textbook: p 225
 */			// Queue
void levelOrder(Node* ptr)
{
	if (!ptr) return; /* 공백 트리 */
	enQueue(ptr);			// 큐에 노드 삽입

	while (1) {		// 무한루프
		ptr = deQueue();		// ptr = ptr
		if (ptr) {			// 트리 끝까지
			printf(" [%d] ", ptr->key);		// 일단 첫 노드 값 출력
			if (ptr->left)			// 만약 왼쪽에 값이 있으면
				enQueue(ptr->left);		// 다음 레벨 왼쪽노드부터 삽입
			if (ptr->right)		// 오른쪽 존재하면
				enQueue(ptr->right);		// 오른쪽 삽입
		}
		else break;		// 끝나면 break

	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while (ptr != NULL) {

		/* if there is a node for the key, then just return */
		if (ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if (ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if (parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}

// 찾았을 때 중간에 존재하면 바꾸고 리프노드이면 마지막만 삭제
int deleteNode(Node* head, int key)
{
	Node* root = head;		// 부모노드
	Node* son = head->left;		// 자식노드
	Node* temp = malloc(sizeof(Node));		// 임시 대입 노드
	if (son == NULL) {		// 비어있을경우
		printf("Insert를 먼저 하시오\n");		// errot message
		return 0;		// 함수 나감
	}
	while (1) {		// 무한루프
		if (son->key == key) {		// 만약 키를 찾으면
			if (son->left == NULL && son->right == NULL) {		// 리프노드면
				if (root->left == son)		// 왼쪽이 son이면
					root->left = NULL;		// 왼쪽 노드 NULL
				if (root->right == son)		// 오른쪽이 son이면
					root->right = NULL;		// 오른쪽 노드 NULL
				return 0;		// 함수 나감
			}
			if (son->left != NULL) {		// 왼쪽 중간노드 삭제
				temp = son;
				son = son->left;
				if (temp->right == NULL)
					son->right = NULL;
				else
					son->right = temp->right;
				root->left = son;

				return 0;
			}
			if (son->right != NULL) {		// 오른쪽 중간노드 삭제
				temp = son;
				son = son->right;
				if (root->right == temp)
					root->right = son;
				if (root->left == temp)
					root->left = son;

				return 0;
			}
		}
		if (son->left == NULL && son->right == NULL && son->key != key) {		// 다 돌렸는데 key가 없으면
			printf("찾는 key가  없습니다."); // error message
			return 0;
		}
		if (key < son->key) {		// key의 위치탐색
			son = son->left;
			root = root->left;
		}
		if (key > son->key) {		// key의 위치탐색
			root = son;
			son = son->right;
		}
	}
	return 0;
}


void freeNode(Node* ptr)
{
	if (ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if (head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()		// 스택 pop
{
	if (top == -1)
		return NULL;
	return stack[top--];		// 제일 위에있는 노드 리턴해주고 삭제
}

void push(Node* aNode)			// 스택 push
{
	if (top >= MAX_STACK_SIZE) {
		printf("error!!\n");
		return 0;
	}
	stack[++top] = aNode;			// top하나 올리고 스택쌓음
}


Node* deQueue()		// 큐 삭제
{
	if (front == rear)
		return NULL;
	front = (front + 1) % MAX_QUEUE_SIZE;		// 맨 앞 위치 올리고
	return queue[front];		// 그 위치 반환
}

void enQueue(Node* aNode)		// 큐 삽입
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;		// 맨 뒤의  인덱스 올리고
	if (front == rear)
		return 0;
	queue[rear] = aNode;		// 맨뒤에 삽입
}

void printStack() {

}
