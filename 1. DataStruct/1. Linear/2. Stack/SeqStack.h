#ifndef _SEQSTACK_H_
#define _SEQSTACK_H_

#include "../../Commen/commen.h"

typedef int ElemType;

struct StructSeqStack
{
	ElemType * base;
	int top;
	int size;
	int capacity;
};

typedef struct StructSeqStack StructSeqStack, * SeqStack;

SeqStack initStack();
void destoryStack(SeqStack );

Boolean isFullStack(SeqStack );
Boolean isEmptyStack(SeqStack );
int getSize();

//Status for stack is empt, rp(return_ptr) for return
Status pop(SeqStack stack, ElemType* rp);
Status push(SeqStack stack, ElemType data);

/**
 * for special operations
 */

#endif