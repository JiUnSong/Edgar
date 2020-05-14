/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
 /* 필요한 헤더파일 추가 */

typedef struct Node {      // 양방향 노드
   int key;
   struct Node* llink;
   struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
   setvbuf(stdout, NULL, _IONBF, 0);      // 버퍼 허용
   printf("[2019038028]    [송지운]\n");   // 내 이름
   char command;      // command 변수
   int key;         // 입력받을 key
   listNode* headnode = NULL;

   do {
      printf("----------------------------------------------------------------\n");         // 메뉴판
      printf("                  Doubly Circular Linked List                   \n");
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


int initialize(listNode** h) {                  // 헤드노드가 정해진 initialize

   /* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
   if (*h != NULL)
      freeList(*h);

   /* headNode에 대한 메모리를 할당하여 리턴 */
   *h = (listNode*)malloc(sizeof(listNode));
   (*h)->rlink = *h;
   (*h)->llink = *h;
   (*h)->key = -9999;
   return 1;
}

/* 메모리 해제 */
int freeList(listNode* h) {
   listNode* p = h->rlink;      // 노드 옮겨다니면서 해지할 변수

   listNode* prev = NULL;      // 임시저장 변수
   while (p->key != -9999) {      // 한바퀴 돌 때 까지
      prev = p;      // 잠시 노드 저장
      p = p->rlink;      // 위치 옮기고
      free(prev);      // 저장된 노드 해지
   }
   free(h);      // 헤드도 해지
   return 0;      // 0값을 반환
}



void printList(listNode* h) {         // 각 링크가 어디 가리키는지 key는 무엇인지 나타내는 함수
   int i = 0;
   listNode* p;

   printf("\n---PRINT\n");

   if (h == NULL) {
      printf("Nothing to print....\n");
      return;
   }

   p = h->rlink;

   while (p != NULL && p != h) {
      printf("[ [%d]=%d ] ", i, p->key);
      p = p->rlink;
      i++;
   }
   printf("  items = %d\n", i);


   /* print addresses */
   printf("\n---checking addresses of links\n");
   printf("-------------------------------\n");
   printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

   i = 0;
   p = h->rlink;
   while (p != NULL && p != h) {
      printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
      p = p->rlink;
      i++;
   }

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {      
   listNode* node = malloc(sizeof(listNode));      // 추가할 노드 생성
   listNode* temp = h->llink;      // 링크를 바꿔주기 위해 변수 생성
   if (h->rlink == h->llink && h->rlink->key == -9999) {      // 노드가 없을 경우
      insertFirst(h, key);      // insertfirst
      return 0;      // 0 값을 반환
   }
   node->key = key;      // 추가할 노드에 key 대입
   node->rlink = h->llink->rlink;      // node->rlink가 헤드노드 가리키도록
   node->llink = temp;      // node->llink가 이전 lastnode 가리키도록
   h->llink->rlink = node;      // 이전 lastnode->rlink가 node 가리키도록
   h->llink = node;      // 헤드노드의 llink가 추가된 lastnode 가리킴
   return 1;      // 함수 나감
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
   if (h->rlink == h->llink && h->rlink->key == -9999) {      // 노드가 없을 경우
      printf("insert를 먼저 하시오.\n");      // insert를 먼저 하라는 오류 메시지 출력
      return 0;      // 함수 나감
   }
   listNode* src = h->llink;      // src가 마지막 노드가 되도록 하는 변수
   h->llink = h->llink->llink;      // h->llink가 lastnode 이전의 노드를 가리키도록 함
   src->llink->rlink = src->rlink;      // lastnode의 이전의 노드의 rlink가 헤드노드를 가리키도록 함
   free(src);      // 임시 저장 해지
   return 1;      // 함수 나감
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
   listNode* next = h->rlink;      // next가 첫 노드 가리키도록 함

   listNode* node = (listNode*)malloc(sizeof(listNode));      // 새로 만든 node
   node->key = key;      // node->key에 key대입
   node->llink = h;      // node->link가 헤드노드 가리키도록
   node->rlink = next;      // node->rlink가 이전의 firstnode 가리키도록 함

   h->rlink = node;      // h->rlink가 새로 생긴 node를 가리키도록 함
   next->llink = node;      // 기존의 firstnode->llink가 새로 생긴 노드를 가리키도록 함
   return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
   if (h->rlink == h->llink && h->rlink->key == -9999) {      // 노드가 없을 경우
      printf("insert를 먼저 하시오.\n");// insert를 먼저 하라는 오류 메시지 출력
      return 0; // 함수 나감
   }
   listNode* src = h->rlink;      // 기존의 h->rlink를 가진 src 선언
   
   h->rlink = h->rlink->rlink;      // h->rlink를 옆 노드로 변경
   src->rlink->llink = src->llink;      // 옆 노드의 llink가 헤드를 가리키도록 함
   free(src);      // 기존의 firstnode 삭제
   return 1;      // 함수 나감
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
   if (h->rlink == h->llink)      // 노드가 없거나 1개인 경우
      return 0;      // 함수 나감
   int temp;      // key를 임시 저장할 변수
   listNode* inv = h->llink;      // inv = h->llink
   listNode* inv2 = h->rlink;      // inv2 = h->rlink
   while (1) {      // 무한 루프
      temp = inv2->key;      // h->rlink의 key를 임시 저장
      inv2->key = inv->key;      // h->rlink->key = h->llink의 키
      inv->key = temp;      // h->llink->key = h->rlink->key
      if (inv->llink == inv2 || inv == inv2)      // 만약 h->llink와 h->rlink가 바로 옆이거나 같다면
         return 0;      // 함수 나감
      inv = inv->llink;      // 옆으로 이동
      inv2 = inv2->rlink;      // 옆으로 이동
   }
   return 0;      // 함수 나감
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {
   if (h->rlink == h->llink && h->rlink->key == -9999) {      // 노드가 없다면
      insertFirst(h, key);      // insertfirst
      return 0;      // 함수 나감
   }
   listNode* node = malloc(sizeof(listNode));      // 새로 추가할 노드 생성
   listNode* src = h->rlink;      // src = h->rlink
   node->key = key;      // node에 key 대입
   while (1) {      // 무한 루프
      if (src->key >= key) {      // src->key가 key보다 크거나 같으면
         node->rlink = src;               // 현재 위치 이전에 값 대입
         node->llink = src->llink;
         src->llink->rlink = node;
         src->llink = node;
         return 0;            // 함수 나감
      }
      else
         src = src->rlink;      // 옆으로 이동
      if (src == h) {      // 만약 끝까지 왔다면
         insertLast(h, key);      // insertlast
         return 0;      // 함수 나감
      }
   }
   return 0;      // 함수 나감
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
   if (h->rlink == h->llink && h->rlink->key == -9999) {      //만약 노드가 없으면
      printf("insert를 먼저 하시오.\n");      // 오류메세지
      return 0;      // 함수 나감
   }
   listNode* src = h->rlink;      // 이동하면서 찾아다닐 변수
   while (1) {      // 무한 루프
      if (src->key == key) {      // 만약 src->key == key 이면
         src->llink->rlink = src->rlink;      // 이전 노드를 다음 노드로 연결해서 현재 노드 삭제
         src->rlink->llink = src->llink;
         return 0;
      }
      else
         src = src->rlink;      // 이동
   }
   free(src);      // 노드 해지
   return 0;      // 함수 나감
}
