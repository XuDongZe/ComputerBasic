/**
 * generic list
 */
#ifndef _GENERIC_LINKLIST_H_
#define _GENERIC_LINKLIST_H_

#include "../../Commen/commen.h"


/**
 * you can extend this struct then you can create a doubled-link list.
 * when you change this, you must rewrite the method in GList.
 */
typedef struct GenericLink {
	struct GenericLink * next;
}GenericLink, *GLink;

GLink newGLink();
GLink newGLink() {
	GLink link = (GLink) assert(malloc(sizeof(GenericLink)));

	link->next = NULL;

	return link;
}

/**
 * [getOffAddr(type, ptr, member) 
 * 		类型为type的结构的其中一个子属性member的地址subAddr已知
 * 		找到该结构首地址(也就是该结构的引用)，单位为 字节]
 * 	type 为实际结构类型， 就像在malloc中的sizeof()填写的类型一样
 * 	不能为指向该类型的指针就像sizeof(double *)一样
 * 	
 */
#define getStartAddr(type, subAddr, member) ( ((char *)(subAddr)) - (char *)(&(((type *) 0)->member)) )

#endif
