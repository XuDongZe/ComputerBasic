#ifndef ARRAYLISTH
#define ARRAYLISTH

#include "../../Commen/commen.h"

//for memset(void* ptr, int ch, int size_t);
#include <memory.h>

typedef struct ArrayList {
	int * array;
	int capacity;
	int size;	// size-1 for the max idx, size for the current amount of elem
}ArrayList, *SeqList;

#define getCap(arraylist) ((arraylist)->capacity)
#define getSize(arraylist) ((arraylist)->size)  
#define isFull(arraylist) (((arraylist)->size==(arraylist)->capacity)? TRUE:FALSE)

//init 
ArrayList * init(int capacity);

//insert, Status for idx
Status insert(ArrayList* list, int data, int idx);	//after the very idx

//delete, Status for data not exsit
Status removeIdx(ArrayList* list, int idx);

//update, Status for idx
Status update(ArrayList* list, int idx, int newData);

//query, int include not find -> NULL
int query(ArrayList* list, int data);

//for random access： idx: 0->size-1
int getData(ArrayList *list, int idx);

#endif