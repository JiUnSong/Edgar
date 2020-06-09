k/*
 * hw5-sorting.c
 *
 *  Created on: May 22, 2019
 *
 *  Homework 5: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	setvbuf(stdout, NULL, _IOFBF, 0);		// 버퍼 허용
	printf("2019038028    송지운\n");		// 내 이름
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);		// 기존 배열 출력
			hashing(array, &hashtable);
			printArray(hashtable);	// 주소 저장된 배열 출력
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}
		// 할당 해제
int freeArray(int *a)
{
	if(a != NULL)		// 배열이 비어있지 않으면
		free(a);		// free
	return 0;		// 0값을 반환
}

void printArray(int *a)
{
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a)
{
	int min;		// Minimum value variable
	int minindex;	// Index of minimum value variable
	int i, j;		// for loop variable

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);			// Pirnt Array before selectionSorting

	for (i = 0; i < MAX_ARRAY_SIZE; i++)	
	{
		minindex = i;		// minindex = i(0~12)
		min = a[i];			// min = a[i]
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j]) // If min > a[j]
			{
				min = a[j];		// Change minimum value
				minindex = j;	// Change minimum index
			}
		}
		a[minindex] = a[i];		// insert value in array
		a[i] = min;				// insert value in array
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);			// Print Array after Selection Sorting
	return 0;		// return 0
}

int insertionSort(int *a)
{
	int i, j, t;		// variable

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);		// Print Array before InsertionSorting

	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i];		// Assign temporary variable
		j = i;			// temporary variable j = i
		while (a[j-1] > t && j > 0)  // find seat for next index
		{						
			a[j] = a[j-1];	// Change value 
			j--;			// index = index - 1
		}
		a[j] = t;			// Changed value get back to origin 
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);		// Print Array after InsertionSorting

	return 0;
}

int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);			// Print Array before Bubble Sorting

	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j] > a[j+1])		// if not Sorted
			{
				t = a[j];			// Change for sorting
				a[j] = a[j+1];
				a[j+1] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);			// Print Array after Bubble Sorting

	return 0;		// return 0
}

int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");		
	printf("----------------------------------------------------------------\n");

	printArray(a);			// Print Array before shellSort

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)		// h = 1이 될때까지 감소
	{
		for (i = 0; i < h; i++)						// 어느정도 정렬 시킴
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)			// 삽입정렬 적용
			{
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v)
				{
					a[k] = a[k-h];
					k -= h;
				}
				a[k] = v;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);			// Print Array after shellSort

	return 0;
}

int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1];					// 변수에 초기 값 대입
		i = -1;						// 변수에 초기 값 대입
		j = n - 1;					// 변수에 초기 값 대입

		while(1)
		{
			while(a[++i] < v);		// v보다 작은 key 찾기
			while(a[--j] > v);		// v보다 큰 key 찾기

			if (i >= j) break;		// 값 change
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];					// v값을 j의 위치로 옮김
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i);			// j를 중심으로 해서 재귀호출
		quickSort(a+i+1, n-i-1);
	}


	return 0;		// return 0
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;		// key의 위치 조정 후 return
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;				// initialize table value

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);			// 주소값 저장할 위치 지정
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key;		// hashtable이 비어있으면 key값 저장
		} else 	{

			index = hashcode;				// else index = hashcode

			while(hashtable[index] != -1)			// hashtable[index] 가 비어있는 곳 까지
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;		// index 의 위치 조정
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;			// 빈 자리에 key 대입
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key);				// index의 조정된 위치 반환	

	if(ht[index] == key)		// 만약 찾는 key면
		return index;			// index 반환

	while(ht[++index] != key)		// 찾을때 까지
	{
		index = index % MAX_HASH_TABLE_SIZE;		// 인덱스 조정
	}
	return index;		// 인덱스 반환
}



