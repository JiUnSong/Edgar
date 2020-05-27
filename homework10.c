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
int top = -1;			// ������ �ֻ��� ����

Node* pop();		// ������ �ֻ��� ���Ҹ� �����ϸ鼭 ��ȯ
void push(Node* aNode);		// ���� �ֻ����� ���� push

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
	setvbuf(stdout, NULL, _IONBF, 0);      // ���� ���
	printf("[2019038028]    [������]\n");   // �� �̸�
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



void recursiveInorder(Node* ptr)			// ��� ����� ���� ��ȸ
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
			push(node);				// ���ÿ� �߸� ������ ����
		node = pop(); // ���� top�� ���� node�� �����ϰ� Ʈ�� ���� �� pop()
		if (!node) break; // �����̸� break;
		printf(" [%d] ", node->key);			// print
		node = node->right;		// ���� ��ȸ
	}
}

/**
 * textbook: p 225
 */			// Queue
void levelOrder(Node* ptr)
{
	if (!ptr) return; /* ���� Ʈ�� */
	enQueue(ptr);			// ť�� ��� ����

	while (1) {		// ���ѷ���
		ptr = deQueue();		// ptr = ptr
		if (ptr) {			// Ʈ�� ������
			printf(" [%d] ", ptr->key);		// �ϴ� ù ��� �� ���
			if (ptr->left)			// ���� ���ʿ� ���� ������
				enQueue(ptr->left);		// ���� ���� ���ʳ����� ����
			if (ptr->right)		// ������ �����ϸ�
				enQueue(ptr->right);		// ������ ����
		}
		else break;		// ������ break

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

// ã���� �� �߰��� �����ϸ� �ٲٰ� ��������̸� �������� ����
int deleteNode(Node* head, int key)
{
	Node* root = head;		// �θ���
	Node* son = head->left;		// �ڽĳ��
	Node* temp = malloc(sizeof(Node));		// �ӽ� ���� ���
	if (son == NULL) {		// ����������
		printf("Insert�� ���� �Ͻÿ�\n");		// errot message
		return 0;		// �Լ� ����
	}
	while (1) {		// ���ѷ���
		if (son->key == key) {		// ���� Ű�� ã����
			if (son->left == NULL && son->right == NULL) {		// ��������
				if (root->left == son)		// ������ son�̸�
					root->left = NULL;		// ���� ��� NULL
				if (root->right == son)		// �������� son�̸�
					root->right = NULL;		// ������ ��� NULL
				return 0;		// �Լ� ����
			}
			if (son->left != NULL) {		// ���� �߰���� ����
				temp = son;
				son = son->left;
				if (temp->right == NULL)
					son->right = NULL;
				else
					son->right = temp->right;
				root->left = son;

				return 0;
			}
			if (son->right != NULL) {		// ������ �߰���� ����
				temp = son;
				son = son->right;
				if (root->right == temp)
					root->right = son;
				if (root->left == temp)
					root->left = son;

				return 0;
			}
		}
		if (son->left == NULL && son->right == NULL && son->key != key) {		// �� ���ȴµ� key�� ������
			printf("ã�� key��  �����ϴ�."); // error message
			return 0;
		}
		if (key < son->key) {		// key�� ��ġŽ��
			son = son->left;
			root = root->left;
		}
		if (key > son->key) {		// key�� ��ġŽ��
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



Node* pop()		// ���� pop
{
	if (top == -1)
		return NULL;
	return stack[top--];		// ���� �����ִ� ��� �������ְ� ����
}

void push(Node* aNode)			// ���� push
{
	if (top >= MAX_STACK_SIZE) {
		printf("error!!\n");
		return 0;
	}
	stack[++top] = aNode;			// top�ϳ� �ø��� ���ý���
}


Node* deQueue()		// ť ����
{
	if (front == rear)
		return NULL;
	front = (front + 1) % MAX_QUEUE_SIZE;		// �� �� ��ġ �ø���
	return queue[front];		// �� ��ġ ��ȯ
}

void enQueue(Node* aNode)		// ť ����
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;		// �� ����  �ε��� �ø���
	if (front == rear)
		return 0;
	queue[rear] = aNode;		// �ǵڿ� ����
}

void printStack() {

}
