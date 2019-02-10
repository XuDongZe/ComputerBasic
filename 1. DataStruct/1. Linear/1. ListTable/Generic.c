#include "Generic.h"

/**
 * when you want to use the link, then you just include in the last element.
 */
typedef struct GenericLinkNode {
	int iData;
	GLink next;
}GenericLinkNode, *GLNode;

GLNode newGLNode(int iData);
void destoryNode(GLNode *pNode);
void printNode(GLNode *pNode);

typedef struct GenericLinkList {
	GLNode head;
	GLNode tail;
	GLNode current;
	int length;
}GenericLinkList, *GList;

GList newGList();
void destroyList(GList *pList);
static void traverse(GList list);

GLNode newGLNode(int iData) {
	GLNode node = (GLNode) assert(malloc(sizeof(GenericLinkNode)));

	node->iData = iData;
	node->next = NULL;
}

void destoryNode(GLNode *pNode) {
	free((*pNode));
	((*pNode)) = NULL;  
}

void printNode(GLNode * pNode) {
	printf("%d\t", (*pNode)->iData);
}


/*
	new 	destory 	traverse	printList 	insertLast
	and for list info : isEmptyList
 */
GList newGList() {
	GList list = (GList) assert(malloc(sizeof(GenericLinkList)));

	list->head = newGLNode(0);
	list->tail = list->head;
	list->current = list->head;
	list->length = 0;

	return list;
}

Boolean isEmptyList(GList list) {
	return (list==NULL) || (list->length == 0 ? TRUE : FALSE);
}

static void traverse(GList list, void (*visit)(GLNode *)) {
	GLNode node = list->head;
	GLink link = node->next;
	static int i = 0;
	while(i++ < list->length) {
		/**
		 * 这个相对位置有问题，核心所在咳咳
		 */
		node = (GLNode) getStartAddr(GenericLinkNode, link, next); // (type, ptr, member)
		printf("link = %p, node=%p\n", link, node);
		link = link->next;

		//list->current = node;
		visit(&node);
	}
}

void destroyList(GList *pList) {
	traverse(*pList, destoryNode);

	free((*pList)->head); ((*pList)->head) = NULL;
	free((*pList)->tail); ((*pList)->tail) = NULL;
	free((*pList)->current); ((*pList)->current) = NULL;

	free((*pList));	(*pList) = NULL;

	printf("destoryList over\n");
}

void printList(GList list) {
	traverse(list, printNode);
	printf("\nlist->length = %d\n", list->length);
}

/*
	the for insert delete update query
	and each for index and iterator
	and insert for after or befor
	and query for reverse and [begin, end) select, so may requre user-define func: compare().
 */
void insertLast(GList list, int iData) {
	GLNode node = newGLNode(iData);
	
	list->tail->next = (GLink)(&(node->next));
	list->tail = node;
	
	list->length++;
}

/**
 * main for test
 */
int main() {
	GList list = newGList();

	int i = 0;
	while(i++ < 10) {
		insertLast(list, i);
	}

	printList(list);
	destroyList(&list);

	printf("now list is null? %d\n", isEmptyList(list));
	return 0;
}




