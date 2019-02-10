#include "ArrayList.h"

/**
 * for static inner functions
 */
static void expansion(ArrayList * plist);
static void print(ArrayList * list);

static void print(ArrayList * list) {
	int i = 0, size = getSize(list);
	printf("size:\t%d\n", list->size);
	printf("capacity:\t%d\n", list->capacity);
	for(i=0; i<size; i++) {
		printf("%d:\t%d\n", i, list->array[i]);
	}
}

//when size == capcity时,call this func for enlarge the capacity
static void expansion(ArrayList * list) {
	int newCap = (int) (1.5*getCap(list) + 8);
	list->array = (int*) assert(realloc(list->array, newCap*sizeof(int)));

	list->capacity = newCap;
}

//init 
ArrayList* init(int capacity) {
	ArrayList* list = (ArrayList *) assert(malloc(sizeof(ArrayList)));

	list->array = (int *) assert(malloc(capacity*sizeof(int)));
	memset(list->array, 0, capacity*sizeof(int));
	list->capacity = capacity;
	list->size = 0;

	return list;
}

/*insert data at the very idx: 0->size;
*	0 for head and size for tail
*/
Status insert(ArrayList* list, int idx, int data) {
	while(isFull(list) == TRUE)
		expansion(list);
	int size = getSize(list), capacity = getCap(list);
	if(idx>size || idx<0) 
		return FALSE;

	int i;
	for(i = size-1; i>=idx; i--) {
		list->array[i+1] = list->array[i];
	}
	list->array[idx] = data;
	list->size++;

	return TRUE;
}

Status removeIdx(ArrayList * list, int data) {
	int idx = -1, size=getSize(list);
	if((idx=query(list, data)) == -1) 
		return FALSE;

	int i;
	for(i=idx; i+1<size; i++) {
		list->array[i] = list->array[i+1];
	}
	list->size--;

	return TRUE;
}

// use newData update the very idx: 0->size-1;
Status update(ArrayList * list, int idx, int newData) {
	int size = getSize(list);
	if(idx>=size || idx<0)
		return FALSE;

	list->array[idx] = newData;

	return TRUE;
}

/* query data in the list 
	return the idx of the data
	return -1 for not find
 */
int query(ArrayList * list, int data) {
	int idx = 0, size = getSize(list);
	while(idx<size && list->array[idx++]!=data)
	
	return idx == size ? -1 : idx;
}

int main() {
	printf("ArrayList Test\n");

	ArrayList * list = init(1);
	insert(list, getSize(list), 5);
	insert(list, getSize(list), 7);
	insert(list, getSize(list), 6);

	update(list, getSize(list)/2, 3);
	removeIdx(list, getSize(list)/2);
	int idx = query(list, 6);
	printf("%d\n", idx);
	print(list);

	return 0;
}
