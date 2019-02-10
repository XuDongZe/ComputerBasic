
#include "CycleQueue.h"

SCQueue initQueue() {
	SCQueue queue = (SCQueue) assert(malloc(sizeof(SeqCycleQueue)));

	queue->head = queue->tail = 0;
	return queue;
}

void destoryQueue(SCQueue queue) {
	free(queue); queue = NULL;
}

int getSize(SCQueue queue) {
	return (queue->tail + MAX_SEQCYCLEQUEUE_SIZE - queue->head) % MAX_SEQCYCLEQUEUE_SIZE;
}

Boolean isEmptyQueue(SCQueue queue) {
	return queue->tail == queue->head;
}
/**
 * [isFullQueue 当前尾指针的下一个位置是头指针时]
 * @param  SCQueue [description]
 * @return         [description]
 */
Boolean isFullQueue(SCQueue queue) {
	// %表示溢出折返了
	return (queue->tail + 1) % MAX_SEQCYCLEQUEUE_SIZE == queue->head ;
}

Status pop(SCQueue queue, ElemType* rp) {
	if(isEmptyQueue(queue))
		return FALSE;

	*rp = (queue->data)[queue->head];
	queue->head = (queue->head + 1) % MAX_SEQCYCLEQUEUE_SIZE;
	return TRUE;
}

Status push(SCQueue queue, ElemType data) {
	if(isFullQueue(queue)) {
		printf("queue is full not, can't push data\n");
		return FALSE;
	}
	(queue->data)[queue->tail] = data;
	queue->tail = (queue->tail + 1) % MAX_SEQCYCLEQUEUE_SIZE;
	return TRUE;
}

int main() {
	SCQueue queue = initQueue();
	printf("init over, head=%d, tail=%d, size=%d\n", queue->head, queue->tail, getSize(queue));

	int i = 0;
	while(!isFullQueue(queue)) {
		push(queue, i++);
	}
	printf("push over, head=%d, tail=%d, size=%d\n", queue->head, queue->tail, getSize(queue));

	while(!isEmptyQueue(queue)) {
		pop(queue, &i);
		printf("%d\t", i);
	}
	printf("\npop over, head=%d, tail=%d, size=%d\n", queue->head, queue->tail, getSize(queue));

	//angin push & pop op
	while(!isFullQueue(queue)) {
		push(queue, i++);
	}
	printf("push over, head=%d, tail=%d, size=%d\n", queue->head, queue->tail, getSize(queue));

	while(!isEmptyQueue(queue)) {
		pop(queue, &i);
		printf("%d\t", i);
	}
	return 0;
}











