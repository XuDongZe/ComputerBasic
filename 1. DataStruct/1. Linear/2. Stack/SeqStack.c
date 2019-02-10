#include "SeqStack.h"

SeqStack initStack(int initSize) {
	SeqStack stack = (SeqStack) assert(malloc(sizeof(struct StructSeqStack)));

	stack->base = (ElemType*) assert(malloc(sizeof(ElemType) * initSize));
	stack->top = 0;
	stack->size = 0;
	stack->capacity = initSize;
}

void destoryStack(SeqStack stack) {
	free(stack); 	stack = NULL;
}

Boolean isEmptyStack(SeqStack stack) {
	return (stack==NULL || stack->size == 0);
}

Boolean isFullStack(SeqStack stack) {
	return (stack->size == stack->capacity);
}

int getSize(SeqStack stack) {
	return (stack==NULL? 0:stack->size);
}

//Status for stack is empt, rp(return_ptr) for return
Status pop(SeqStack stack, ElemType* rp) {
	if(isEmptyStack(stack)) 
		return FALSE;
	*rp = (stack->base)[--stack->top];
	stack->size--;
	return TRUE;
}

static void expansion(SeqStack stack) {
	int newCap = (int)(1.5*(stack->capacity) + 8);
	stack->base = (ElemType*)assert(realloc(stack->base, newCap*sizeof(ElemType)));

	stack->capacity = newCap;
}

Status push(SeqStack stack, ElemType data) {
	if(isFullStack(stack))
		expansion(stack);
	(stack->base)[stack->top++] = data;
	stack->size++;
	return TRUE;
}

int main() {
	SeqStack stack = initStack(1);
	printf("init over, stack->size==%d, stack->capacity==%d\n", getSize(stack), stack->capacity);

	int i;
	for(i = 0; i<10; i++) {
		push(stack, i);
	}
	printf("push over, stack->size==%d, stack->capacity==%d\n", getSize(stack), stack->capacity);

	while(!isEmptyStack(stack)) {
		pop(stack, &i);
		printf("%d\t", i);
	}
	printf("\n");

	return 0;
}