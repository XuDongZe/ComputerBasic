#ifndef _CYCLEQUEUE_H_
#define _CYCLEQUEUE_H_

#include "../../Commen/commen.h"

typedef int ElemType;
#define MAX_SEQCYCLEQUEUE_SIZE 20

typedef struct SeqCycleQueue
{
	//we will not use an element space.
	ElemType data[MAX_SEQCYCLEQUEUE_SIZE + 1];
	int head;
	int tail;
}SeqCycleQueue, *SCQueue;

SCQueue initQueue();
void destoryQueue(SCQueue );

int getSize(SCQueue queue);

/**
 *  you will find that when empty the head==tail || head+MAXSIZE==tail and so as when the
 *  queue is full.
 *  so we define that the last one of the queue is not used, may you will store other info...
 *  on this condition, we will init the queue: head==tail.
 *  and when the tail+1 == head, the queue is full.
 */
Boolean isEmptyQueue(SCQueue );
Boolean isFullQueue(SCQueue );

Status pop(SCQueue, ElemType*);
Status push(SCQueue, ElemType);

#endif
