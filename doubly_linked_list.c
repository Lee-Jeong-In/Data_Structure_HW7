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

typedef struct Node 		// doubly linked list의 특징은 포인터가2개여서 2개의 노드를 가리킨다는 것이다.
{
	int key;				// 노드 안에 들어가는 value
	struct Node* llink;		// 이전 노드 가리키기
	struct Node* rlink;		// 다음 노드 가리키기
} listNode;



typedef struct Head 		// 이전 과제와 같이 doubly linked list가 어디에 있는지 알려주는 Head이다.
{
	struct Node* first;
}headNode;

int initialize(headNode** h);			// 포인터의 주소를 보냈으므로, 이중포인터로 받는다.

int freeList(headNode* h);				// HeadNode 포인터로 매개변수를 보냈으므로 single pointer로 받는다.

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;

	headNode* headnode=NULL;			// doubly linked list의 위치를 알려주는 HeadNode 생성

	printf("[----- [이정인] [2019038015] -----]\n");

	do{
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

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);			// 위에서 만든 HeadNode를 초기화 해준다.
			break;
		case 'p': case 'P':					// 여태까지 만든 node를 화면에 출력한다.
			printList(headnode);
			break;
		case 'i': case 'I':					// 노드 추가하기
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':					// 노드 삭제하기
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':					// 마지막 노드 뒤에 삽입하기
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':					// 마지막 노드 삭제하기
			deleteLast(headnode);
			break;
		case 'f': case 'F':					// 첫번째 노드 앞에 노드 삽입하기
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':					// 첫번째 노드 삭제하기
			deleteFirst(headnode);
			break;
		case 'r': case 'R':					// 노드 뒤집기
			invertList(headnode);
			break;
		case 'q': case 'Q':					// 노드 해제하기
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(headNode** h) 						// HeadNode 초기화하기 (포인터의 주소를 보냈으므로, 이중포인터로 받는다.)
{
	if(*h != NULL)									// 남아있는 노드가 있을 때
		freeList(*h);								// 여기서 *h를 사용했다. (*h는 h에 있는 값, 여기서는 HeadNode의 주소)

	*h = (headNode*)malloc(sizeof(headNode));		// HeadNode가 없을 때, 만들어준다.
	(*h)->first = NULL;								
	return 1;
}

int freeList(headNode* h)						// 리스트에 연결된 node메모리 해제
{
	printf("Free doubly linked list...\n");
	listNode* p = h->first;						// 첫번째 노드를 가리키는 p노드를 만든다.

	listNode* prev = NULL;						// 임시 노드 prev를 생성한다.

	while(p != NULL) 							// 아직 연결되어 있는 노드가 있다면
	{
		prev = p;								// prev에 p를 연결하고(해제할 노드를 저장)
		p = p->rlink;							// p를 다음 노드로 연결
		free(prev);								// prev 해제하기
	}

	free(h);									// 연결되어 있는 노드를 모두 해제 했으면 마지막으로 HeadNode를 해제한다.

	return 0;
}


void printList(headNode* h) 					// 만든 노드 출력하기
{
	int i = 0;		
	listNode* p;								// 출력을 위해 만든 임시 노드p

	printf("\n---PRINT\n");

	if(h == NULL) 								// 만든 노드가 없을 때 출력
	{
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;								// 임시 노드p를 첫번째 노드로 이동

	while(p != NULL) 							// 첫번째 노드 내용 출력
	{
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;							// 다음 노드로 이동
		i++;									// 노드 개수를 확인하기 위함
	}

	printf("  items = %d\n", i);				// 여태까지 만든 노드 수 출력
}

int insertLast(headNode* h, int key) 							// 맨뒤에 새로운 노드 삽입
{

	listNode* node = (listNode*)malloc(sizeof(listNode));		// 새로운 노드 생성
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	if (h->first == NULL)										// HeadNode에 붙어있는 노드가 없을 때
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;										// 임시 노드 생성

	while(n->rlink != NULL) 									// 임시 노드가 맨 끝부분이 아닐 때
	{
		n = n->rlink;											// 계속이동
	}

	n->rlink = node;											// 끝부분으로 이동한 n의 rlink가 새로운 node를 가리키게한다.
	node->llink = n;											// doubly linked list 이니까 서로 연결

	return 0;
}

int deleteLast(headNode* h) 				//list의 마지막 노드 삭제
{
	if (h->first == NULL)					// 만든 리스트가 없을 때
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;					// 임시 노드n 생성
	listNode* trail = NULL;					// 임시 노드 trail 생성

	if(n->rlink == NULL) 					// 만든 노드가 1개 일때,
	{
		h->first = NULL;					// HeadNode가 NULL을 가리키게 하면 자동 해제
		free(n);							// 처음 노드 메모리 해제
		return 0;
	}

	while(n->rlink != NULL) 				//마지막 노드까지 이동
	{
		trail = n;
		n = n->rlink;
	}

	trail->rlink = NULL;					// 마지막 노드가 NULL를 가리키게 한다.
	free(n);								// 그리고 메모리 해제

	return 0;
}

int insertFirst(headNode* h, int key) 						// HeadNode 다음에 node를 삽입함
{

	listNode* node = (listNode*)malloc(sizeof(listNode));	// Node생성
	node->key = key;
	node->rlink = node->llink = NULL;

	if(h->first == NULL)									// HeadNode에 연결된 노드가 없을 때
	{
		h->first = node;									// 바로 연결
		return 1;
	}

	node->rlink = h->first;									// 새로운 node가 기존의 처음 노드를 가리킨다.
	node->llink = NULL;										// 맨 앞 노드가 되기 때문에 NULL

	listNode *p = h->first;									// p는 기존 노드의 처음노드가 된다.
	p->llink = node;										// 이제는 2번째 노드가 됬으니 새로생긴 노드와 연결
	h->first = node;										// 기존에 연결된 처음노드를 해제하고 새로운 처음과 연결

	return 0;
}

int deleteFirst(headNode* h) 				// 첫번째 노드 삭제하기
{

	if (h->first == NULL)					// 만들어 놓은 노드가 없을 때
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;					// 임시 노드 n생성 + 첫번째 노드 가리킴(free 할려면 잡아놔야 함)
	h->first = n->rlink;					// HeadNode가 두번째 노드를 가리키면 자동으로 연결 해제

	free(n);								// 첫번째 노드 해제

	return 0;
}

int invertList(headNode* h) 
{
	if(h->first == NULL) 					// 만들어 놓은 노드가 없을 때
	{
		printf("nothing to invert...\n");
		return 0;
	}

	listNode *n = h->first;					// 임시 노드 n 생성
	listNode *trail = NULL;					// 임시 노드 trail 생성		(n을 따라감)
	listNode *middle = NULL;				// 임시 노드 middle 생성	(trail과 headNode사이를 이어줌)

	while(n != NULL)						// HeadNode뒤에 노드가 있을 때
	{
		trail = middle;						
		middle = n;							// middle은 n을 가리키니까 여기서는 h->first이다.
		n = n->rlink;						// n노드을 오른쪽으로 이동
		middle->rlink = trail;				// middle 오른쪽 포인터로 trail넣기
		middle->llink = n;					// middle이 왼쪽 포인터에 n넣기
	}

	h->first = middle;						// HeadNode가 middle을 가리키면 마지막 노드가 HeadNode와 연결된다.

	return 0;
}

int insertNode(headNode* h, int key) 		
{

	listNode* node = (listNode*)malloc(sizeof(listNode));		// 노드을 만든다.
	node->key = key;											// 사용자가 입력한 key를 생성한 node에 넣는다.
	node->llink = node->rlink = NULL;							// 양쪽에 NULL을 가리키게해서 아직 연결시키진 않는다.

	if (h->first == NULL)										// 여기서 이게 처음으로 연결되는 노드 일때,,
	{
		h->first = node;										// first는 node포인터 이기 때문에 노드를 가리킬 처음 노드를 가리킨다.
		return 0;
	}

	listNode* n = h->first;										// 임시로 사용할 n node를 HeadNode에 연결한다.

	while(n != NULL) 											// 임시 Node가 NULL이 아니다 == HeadNode에 연결된 노드가 있다
	{
		if(n->key >= key) 										// 연결된 노드가 사용자가 입력한 key보다 클때...
		{
			if(n == h->first) 									// HeadNode 첫번째 노드가 삽입될 때
				insertFirst(h, key);
			
			else 
			{
				node->rlink = n;								// 새로운 노드가 작기 때문에 n노드 이전으로 삽입
				node->llink = n->llink;							// 기존 n노드 이전 노드를 새로운 노드가 가리킨다.
				n->llink->rlink = node;							// 기존 n노드 이전 노드가 새로운 노드를 가리킨다.
			}
			return 0;
		}

		n = n->rlink;											// n노드를 이동시킨다.
	}

	insertLast(h, key);											// 맨끝에 삽입
	return 0;
}

int deleteNode(headNode* h, int key) 			// 사용자가 입력한 값을 가진 노드를 삭제한다.
{

	if (h->first == NULL)						// 만들어진 노드가 없을 때
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* n = h->first;						// 임시 노드 n생성

	while(n != NULL) 							// 만들어진 노드가 있을 때
	{
		if(n->key == key) 						// 삭제해야할 노드를 찾은 경우 + 삭제도 그냥 막 하는게 아니다.
		{
			if(n == h->first) 					// 첫번째 노드 삭제할 때
			 	deleteFirst(h);
			else if (n->rlink == NULL)			// 마지막 노드인 경우
				deleteLast(h);
			else 								// 중간인 경우
			{ 
				n->llink->rlink = n->rlink;		// n이전 노드가 n다음 노드를 가리키고
				n->rlink->llink = n->llink;		// n다음 노드가 n이전 노드를 가리킨다.
				free(n);						// n노드 해제
			}
			return 1;
		}

		n = n->rlink;							// 다음으로 이동한다.
	}

	printf("cannot find the node for key = %d\n", key);		// 사용자가 입력한 Key 값을 못찾았을 때
	return 1;
}