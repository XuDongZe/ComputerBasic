#include "ArrayList.h"

/**
 * for static inner functions
 */
static void expansion(ArrayList * plist);

void print(ArrayList * list) {
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
ArrayList* initList(int capacity) {
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

Status append(ArrayList* list, int data) {
	return insert(list, getSize(list), data);
}

Status removeIdx(ArrayList* list, int idx, int* rp) {
	if(list==NULL || idx < 0 || idx >= getSize(list))
		return FALSE;
	int i, size = getSize(list);
	for(i=idx; i+1<size; i++) {
		list->array[i] = list->array[i+1];
	}
	list->size--;

	*rp = *(list->array + idx);
	return TRUE;
}

Status removeData(ArrayList * list, int data, int* rp) {
	return removeIdx(list, query(list, data), rp);
}

Status removeLast(ArrayList* list, int *rp) {
	return removeIdx(list, getSize(list)-1, rp);
}
Status removeFirst(ArrayList* list, int* rp) {
	return removeIdx(list, 0, rp);
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
	
	return idx == size ? NOTFIND : idx;
}

//idx range: 0->size-1
Status getIdx(ArrayList* list, int idx, int *rp) {
	if(list == NULL || idx < 0 || idx >= getSize(list))
		return FALSE;
	*rp = *(list->array + idx);
	return true;
}

// int main() {
// 	printf("ArrayList Test\n");

// 	ArrayList * list = initList(1);
// 	int i;
// 	for(i=0; i<10; i++) {
// 		append(list, i);
// 	}

// 	int idx = query(list, 6);
// 	printf("%d\n", idx);
// 	print(list);

// 	while(getSize(list) != 0) {
// 		removeLast(list, &i);
// 		printf("%d, ",i);
// 	}
// 	printf("\nafter remove list is empty? %d\n", isEmpty(list));
// 	printf("\n");
// 	return 0;
// }
