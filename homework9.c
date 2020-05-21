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
   setvbuf(stdout, NULL, _IONBF, 0);      // ���� ���
   printf("[2019038028]    [������]\n");   // �� �̸�
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



void inorderTraversal(Node* ptr)      // inorder ����� ��ȸ
{

   if (ptr != NULL) {            // ptr�� NULL�� �ƴϸ�
      inorderTraversal(ptr->left);      // ���ȣ��-> left ����
      printf("%d ", ptr->key);      //�θ�  print
      inorderTraversal(ptr->right);      // ���ȣ��->right
   }

}

void preorderTraversal(Node* ptr)      // preorder ����� ��ȸ
{

   if (ptr) {      // ptr != NULL �̸�
      printf("%d ", ptr->key);      // �θ���� print
      preorderTraversal(ptr->left);      // ���ʺ���
      preorderTraversal(ptr->right);      // ���� ������
   }

}

void postorderTraversal(Node* ptr) // postorder ����� ��ȸ
{

   if (ptr) {      // ptr != NULL �̸�
      postorderTraversal(ptr->left);      // ���ʺ���
      postorderTraversal(ptr->right);      // ���� ������
      printf("%d ", ptr->key);      // PRINT
   }

}


int insert(Node* head, int key)      // BST����� insert
{
   Node* temp = head->left;      // temp = h->left
   Node* node = malloc(sizeof(Node));      // �߰��� ���
   node->key = key;      // ��忡 key ����
   node->right = NULL;      // node->right = NULL
   node->left = NULL;      // node->left = NULL
   if (temp == NULL) {      // ���� ó�� �����ϴ� ����
      head->left = node;      // head->left = node
      return 0;      // �Լ� ����
   }
   while (1) {      // ���ѷ���
      if (node->key == temp->key) {      // ���� Ʈ���� ���� �̹� �����Ѵٸ�
         printf("���� �̹� �����մϴ�.\n");      // error message
         return 0;      // �Լ� ����
      }
      if (temp->left == NULL && node->key < temp->key) {      // ���� node->key < temp->key �̸�
         temp->left = node;      // temp->left = node
         return 0;      // �Լ� ����
      }
      if (temp->right == NULL && node->key > temp->key) {      // ���� node->key > temp->key �̸�
         temp->right = node;      // temp->right = node
         return 0;      // �Լ� ����
      }
      if (temp->left != NULL && node->key < temp->key)      // ��尡 �� ��ġ Ž��
         temp = temp->left;
      if (temp->right != NULL && node->key > temp->key)      // ��尡 �� ��ġ Ž��
         temp = temp->right;
   }
   return 0;
}

int deleteLeafNode(Node* head, int key)      // delte Leaf Node
{
   Node* root = head;      // �θ���
   Node* temp = head->left;      // �ڽĳ��
   if (temp == NULL) {      // ���� ��尡 ���������
      printf("insert�� ���� �Ͻÿ�\n");      // error message
      return 0;      // �Լ� ����
   }
   while (1) {      // ���ѷ���
      if (temp->key == key) {      // ���� ����ڰ� �Է��� key�� ã�Ұ�,
         if (temp->left == NULL && temp->right == NULL) {      // �װ��� Leaf Node �̸�,
            if (root->left == temp)            // �� ��쿡 �°� delete
               root->left = NULL;
            else if(root->right == temp)
               root->right = NULL;
            return 0;      // �Լ� ����
         }
         else {                        // �װ��� Leaf Node�� �ƴϸ�
            printf("leaf Node�� �ƴմϴ�.\n");      // error message
            return 0;      // �Լ� ����
         }
      }
      if (temp->left == NULL && temp->right == NULL && temp->key != key) {      // ���� ������ ���µ� ã�� ��尡 ���ٸ�
         printf("ã�� key�� �����ϴ�.\n");         // error message
         return 0;      // �Լ� ����
      }
      if (key < temp->key) {      // key�� ��ġ Ž���ϴ� if�� 2��
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
   if(ptr == NULL)      // ���� head�� ���������
      return 0;      // �Լ� ����
   if (key == ptr->key)      // ���� key�� ã����
      return ptr;      // ��ġ return
   if (key < ptr->key)      // key�� ��ġ Ž���ϴ� if��
      return searchRecursive(ptr->left, key);      // ���ȣ��
   return searchRecursive(ptr->right, key);      // ���ȣ��

}

Node* searchIterative(Node* head, int key)      // Iterative
{
   Node* temp = head->left;      // temp = h->left
   if (temp == NULL) {      // ���� ��尡 ���ٸ�
      printf("Ʈ���� ����ֽ��ϴ�.\n");      // error message
      return 0;      // �Լ� ����
   }
   while (temp) {      // ��� ������ �ݺ�
      if (temp->key == key)      // key�� ã����
         return temp;      // ��ġ return
      if (key < temp->key)      // key�� ��ġ Ž���ϴ� if��
         temp = temp->left;
      else
         temp = temp->right;
   }
   printf("���� key �Դϴ�.\n");      // ������ ���µ� ������ error message
   return 0;// return
}


int freeBST(Node* head)      // �Ҵ� ����
{
   Node* p = head;
   if (p) {      // postorder ������ ����
      freeBST(p->left);      // ���ʺ���
      freeBST(p->right);      // ���� ������
      free(p);
   }
   return 0;      // 0���� ��ȯ
}
