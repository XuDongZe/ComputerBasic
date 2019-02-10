#include "LinkedList.h"

/*
	plist: LinkedList **.
	节点数据域的大小由dataSize指定。
	使用带有头节点的双向链表
	头节点仅为链表入口，单向向后链到第一个实际节点。
	模拟idx时，头节点不计入。从第一个实际节点开始计0 -> length-1
 */
Status initList(List * plist, int dataSize) {
	*plist = (List )assert(malloc(sizeof(LinkedList)));
	
	Node head = (Node )assert(malloc(sizeof(LinkedNode)));
	head->next = head;
	head->prev = head;
	head->data = NULL;

	(*plist)->head = head;
	(*plist)->tail = head;
	(*plist)->it = head;	//初始化it指向头节点，也就是第一个真实数据的前驱
	(*plist)->dataSize = dataSize;
	(*plist)->length = 0;	//头节点不计入length

	return TRUE;
}

/**
 * 由于没有到头节点就停下来了，所以这个遍历方式是从前向后；
 * 不支持自定义的遍历方式
 */
Status traverse(List list, Status (*visit)(Node)){
	Iterator it = Iterator(list);
	while(next(it) != getHeadIt(list)) {
		if(visit(it) == FALSE)	return FALSE;
	}
	printf("\ntraverse over\n");
	return TRUE;
}

Status destroyList(List * plist, Status (*destroy)(Node)) {
	if( !traverse(*plist, destroy) )
		return FALSE;
	
	free((*plist)->head), (*plist)->head = NULL;
	free((*plist)->tail), (*plist)->tail = NULL;
	free((*plist)->it), (*plist)->it = NULL;
	free(*plist), *plist = NULL;

	return TRUE;
}

//can't insert at the last one
Status insertBeforeIt(List list, Iterator it, Node node) {
	if(it == getHeadIt(list))
		return FALSE;	//virtual head node can't insert before

	node->prev = getPrevIt(it);
	node->next = it;
	node->prev->next = node;
	node->next->prev = node;

	list->length++;
	return TRUE;
}

Status insertAfterIt(List list, Iterator it, Node node) {
	static int i = 0;
	node->prev = it;
	node->next = getNextIt(it);
	node->prev->next = node;
	node->next->prev = node;

	if(it == getLastIt(list))	list->tail = node;
	list->length++;
	return TRUE;
}

Status insertFirst(List list, Node node) {
	return insertAfterIt(list, getHeadIt(list), node);
}

Status insertLast(List list, Node node){
	return insertAfterIt(list, getLastIt(list), node);
}

Status insertAfterIdx(List list, int idx, Node node) {
	if(idx<0 || idx>=getLength(list)) 
		return FALSE;

	int i = 0;
	Iterator it = getFirstIt(list);
	while(i++ < idx && next(it))
		;
	return insertAfterIt(list, it, node);
}