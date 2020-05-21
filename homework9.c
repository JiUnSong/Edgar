#include <stdio.h>
#include <stdlib.h>

typedef struct node {
   int key;
   struct node *left;
   struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);     /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);     /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
   setvbuf(stdout, NULL, _IONBF, 0);      // 버퍼 허용
   printf("[2019038028]    [송지운]\n");   // 내 이름
   char command;
   int key;
   Node* head = NULL;
   Node* ptr = NULL;   /* temp */

   do {
      printf("\n\n");
      printf("----------------------------------------------------------------\n");
      printf("                   Binary Search Tree #1                        \n");
      printf("----------------------------------------------------------------\n");
      printf(" Initialize BST       = z                                       \n");
      printf(" Insert Node          = n      Delete Node                  = d \n");
      printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
      printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
      printf(" Postorder Traversal  = t      Quit                         = q\n");
      printf("----------------------------------------------------------------\n");

      printf("Command = ");
      scanf(" %c", &command);

      switch (command) {
      case 'z': case 'Z':
         initializeBST(&head);
         break;
      case 'q': case 'Q':
         freeBST(head->left);
         break;
      case 'n': case 'N':
         printf("Your Key = ");
         scanf("%d", &key);
         insert(head, key);
         break;
      case 'd': case 'D':
         printf("Your Key = ");
         scanf("%d", &key);
         deleteLeafNode(head, key);
         break;
      case 'f': case 'F':
         printf("Your Key = ");
         scanf("%d", &key);
         ptr = searchIterative(head, key);
         if (ptr != NULL)
            printf("\n node [%d] found at %p\n", ptr->key, ptr);
         else
            printf("\n Cannot find the node [%d]\n", key);
         break;
      case 's': case 'S':
         printf("Your Key = ");
         scanf("%d", &key);
         ptr = searchRecursive(head->left, key);
         if (ptr != NULL)
            printf("\n node [%d] found at %p\n", ptr->key, ptr);
         else
            printf("\n Cannot find the node [%d]\n", key);
         break;

      case 'i': case 'I':
         inorderTraversal(head->left);
         break;
      case 'p': case 'P':
         preorderTraversal(head->left);
         break;
      case 't': case 'T':
         postorderTraversal(head->left);
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
   (*h)->left = NULL;   /* root */
   (*h)->right = *h;
   (*h)->key = -9999;
   return 1;
}



void inorderTraversal(Node* ptr)      // inorder 방식의 순회
{

   if (ptr != NULL) {            // ptr이 NULL이 아니면
      inorderTraversal(ptr->left);      // 재귀호출-> left 부터
      printf("%d ", ptr->key);      //부모  print
      inorderTraversal(ptr->right);      // 재귀호출->right
   }

}

void preorderTraversal(Node* ptr)      // preorder 방식의 순회
{

   if (ptr) {      // ptr != NULL 이면
      printf("%d ", ptr->key);      // 부모부터 print
      preorderTraversal(ptr->left);      // 왼쪽부터
      preorderTraversal(ptr->right);      // 다음 오른쪽
   }

}

void postorderTraversal(Node* ptr) // postorder 방식의 순회
{

   if (ptr) {      // ptr != NULL 이면
      postorderTraversal(ptr->left);      // 왼쪽부터
      postorderTraversal(ptr->right);      // 다음 오른쪽
      printf("%d ", ptr->key);      // PRINT
   }

}


int insert(Node* head, int key)      // BST방식의 insert
{
   Node* temp = head->left;      // temp = h->left
   Node* node = malloc(sizeof(Node));      // 추가할 노드
   node->key = key;      // 노드에 key 대입
   node->right = NULL;      // node->right = NULL
   node->left = NULL;      // node->left = NULL
   if (temp == NULL) {      // 만약 처음 대입하는 경우면
      head->left = node;      // head->left = node
      return 0;      // 함수 나감
   }
   while (1) {      // 무한루프
      if (node->key == temp->key) {      // 만약 트리에 값이 이미 존재한다면
         printf("값이 이미 존재합니다.\n");      // error message
         return 0;      // 함수 나감
      }
      if (temp->left == NULL && node->key < temp->key) {      // 만약 node->key < temp->key 이면
         temp->left = node;      // temp->left = node
         return 0;      // 함수 나감
      }
      if (temp->right == NULL && node->key > temp->key) {      // 만약 node->key > temp->key 이면
         temp->right = node;      // temp->right = node
         return 0;      // 함수 나감
      }
      if (temp->left != NULL && node->key < temp->key)      // 노드가 들어갈 위치 탐색
         temp = temp->left;
      if (temp->right != NULL && node->key > temp->key)      // 노드가 들어갈 위치 탐색
         temp = temp->right;
   }
   return 0;
}

int deleteLeafNode(Node* head, int key)      // delte Leaf Node
{
   Node* root = head;      // 부모노드
   Node* temp = head->left;      // 자식노드
   if (temp == NULL) {      // 만약 노드가 비어있으면
      printf("insert를 먼저 하시오\n");      // error message
      return 0;      // 함수 나감
   }
   while (1) {      // 무한루프
      if (temp->key == key) {      // 만약 사용자가 입력한 key를 찾았고,
         if (temp->left == NULL && temp->right == NULL) {      // 그것이 Leaf Node 이면,
            if (root->left == temp)            // 각 경우에 맞게 delete
               root->left = NULL;
            else if(root->right == temp)
               root->right = NULL;
            return 0;      // 함수 나감
         }
         else {                        // 그것이 Leaf Node가 아니면
            printf("leaf Node가 아닙니다.\n");      // error message
            return 0;      // 함수 나감
         }
      }
      if (temp->left == NULL && temp->right == NULL && temp->key != key) {      // 만약 끝까지 갔는데 찾는 노드가 없다면
         printf("찾는 key가 없습니다.\n");         // error message
         return 0;      // 함수 나감
      }
      if (key < temp->key) {      // key의 위치 탐색하는 if문 2개
         temp = temp->left;
         root = root->left;

      }
      if (key > temp->key) {
         root = temp;
         temp = temp->right;
      }
   }
   return 0;
}

Node* searchRecursive(Node* ptr, int key)         // Recursive
{
   if(ptr == NULL)      // 만약 head가 비어있으면
      return 0;      // 함수 나감
   if (key == ptr->key)      // 만약 key를 찾으면
      return ptr;      // 위치 return
   if (key < ptr->key)      // key의 위치 탐색하는 if문
      return searchRecursive(ptr->left, key);      // 재귀호출
   return searchRecursive(ptr->right, key);      // 재귀호출

}

Node* searchIterative(Node* head, int key)      // Iterative
{
   Node* temp = head->left;      // temp = h->left
   if (temp == NULL) {      // 만약 노드가 없다면
      printf("트리가 비어있습니다.\n");      // error message
      return 0;      // 함수 나감
   }
   while (temp) {      // 노드 끝까지 반복
      if (temp->key == key)      // key를 찾으면
         return temp;      // 위치 return
      if (key < temp->key)      // key의 위치 탐색하는 if문
         temp = temp->left;
      else
         temp = temp->right;
   }
   printf("없는 key 입니다.\n");      // 끝까지 갔는데 없으면 error message
   return 0;// return
}


int freeBST(Node* head)      // 할당 해제
{
   Node* p = head;
   if (p) {      // postorder 형식의 해제
      freeBST(p->left);      // 왼쪽부터
      freeBST(p->right);      // 다음 오른쪽
      free(p);
   }
   return 0;      // 0값을 반환
}
