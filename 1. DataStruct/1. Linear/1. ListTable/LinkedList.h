/**
 * 支持泛型的节点类型LinkedNode和双向循环链表LinkedList
 */

#ifndef _LINKLIST_H_
#define _LINKLIST_H_

#include "../../Commen/commen.h"
  
//for memset(void* ptr, int ch, int size_t);
#include <memory.h>

/*
	double cycled linked list node
	when you use this struct, you must write the following user-functions:
		Status printNode();
		Node newNode(const void*, int); //int for dataSize malloc
		Status freeNode(Node);		// destory an existed node 
	
	and if you want the node can be compared with each other
	then you must reWrite the following user-defined functions:
		CmpType compareTo(const Node a, const Node b);
 */
typedef struct LinkedNode {
	void * data;		//for arbitrary(任意的) type
	struct LinkedNode * prev;
	struct LinkedNode * next;
}LinkedNode;

typedef struct LinkedList {
	//for vritual head node
	struct LinkedNode * head;
	struct LinkedNode * tail;	//for insert_tial
	struct LinkedNode * it; 	//for current iterator
	int length;	// for idx; size-1 for the max idx, size for the current amount of elem
	int dataSize;		//节点数据所占内存大小

	//assign from one node to another; for that the struct of node is fixed
	//so this func is fixed too. so as the destory func.
	void (* assign) (void* dst, const void* src);
	//for destory one node;
	void (* destory) (struct LinkedNode * node);
}LinkedList;

typedef LinkedNode * Iterator;
typedef LinkedNode * Node;
typedef LinkedList * List;

/*
	for iterator move
 	the follow will change the current iteratorgit
 	when it is null then do nothing 
*/ 	
#define next(it) ((it == NULL) ? NULL:((it) = (it)->next))
#define prev(it) ((it == NULL) ? NULL:((it) = (it)->prev))

/*
	when use these, user must check the it or list is not null
	use isNullPtr(ptr) in "commmen.h"
 */
#define getNextIt(it) (((it) == NULL)? NULL : (it)->next)
#define getPrevIt(it) (((it) == NULL)? NULL : (it)->prev)
#define getData(it) ((it)->data)

#define getHeadIt(list) ((list)->head)	//equal with Iterator
#define getFirstIt(list) ((list)->head->next)
#define getLastIt(list) ((list)->tail)
#define getLength(list) ((list)->length)
#define getDataSize(list) ((list)->dataSize)
#define Iterator(list) ((list)->head)	//first is the vritual head

#define isEmptyList(list) ((list)==NULL ? TRUE: \
				((list)->length==0 && (list)->head==(list->tail) && (list->head->next)==NULL))

//for init & destroy
Status initList(List * plist, int dataSize);
Status traverse(List list, Status (*visit)(Node ));
Status destroyList(List * plist, Status (*destroy)(Node));

/*
	for insert, 内部调用一个函数指针assign进行节点间赋值
	insertBeforeIt 	-> 插入到指定的it之前
	insertAfterIt 	-> 插入到指定的it之后

	insertIdx 		-> 模拟idx，插入到第idx下标
	insertLast 		-> 插入到尾节点之后
	insertFirst 	-> 插入到头节点之后
 */
Status insertBeforeIt(List list, Iterator it, Node newNode);
Status insertAfterIt(List list, Iterator it, Node newNode);
Status insertIdx(List list, int idx, Node newNode);

Status insertFirst(List list, Node newNode);
Status insertLast(List list, Node newNode);

/*
	for delete will return the deleted node with rIt.
 */
Status removeIt(List list, Iterator it);
Status removeIdx(List list, int idx, Iterator rIt);
Status removeFirst(List list, Iterator rIt);
Status removeLast(List list, Iterator rIt);

/**
 * for update
 */
Status updateIt(List list, Iterator it, Node newNode);
Status updataIdx(List list, int idx, Node newNode);

/*
	for query & get
 */
//寻找第一个在[begin, end)之间与给定数据data满足compare条件下cmpRes关系的
Iterator queryFirst(Iterator begin, Iterator end, Node newNode, CmpType cmpRes,
	CmpType (*compare)(const void*, const void*));

//find the idx of the data that equals with the very data
int indexOf(List, Node newNode, 
	CmpType (*compare)(const void*, const void*));

/*
	for special operations
 */
List reverseList(List list);
Status exchangeNode(List dst, Iterator it_dst, List src, Iterator it_src); 


#endif