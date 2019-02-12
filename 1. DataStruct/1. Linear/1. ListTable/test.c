#include <stdio.h>
#include "LinkedList.h"

static Node newNode(const void *data, int dataSize) {
	Node node = (Node) assert(malloc(sizeof(LinkedNode)));
	
	/**
	 * you must malloc the dataSize space for node->data before you memcpy
	 * for memcpy require avilable src & dst mem space
	 */
	node->data = assert(malloc(sizeof(dataSize)));
	memcpy(node->data, data, dataSize);
	node->prev = NULL;
	node->next = NULL;

	return node;
}

static Status printNode(const Node node) {
	printf("%d\t", typeExchange(int, node->data));
}

int main() {
	List list;
	initList(&list, sizeof(int));
	
	int i = 0, *p = &i;
	Node node = NULL;
	while(++i < 10){
		node = newNode((void *)p, list->dataSize);
		insertLast(list, node);
	}
	traverse(list, printNode);

	list = reverseList(list);
	printf("after reverseList list:\n");
	traverse(list, printNode);
	
	printf("dataSize = %d, length = %d\n", list->dataSize, list->length);
	return 0;
}
