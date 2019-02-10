#ifndef COMMENH
#define COMMENH
#include <stdio.h>
#include <stdlib.h>
/**
 * for status
 */
typedef int Status;	// return type
#define OK 1
#define ERROR -1

/**
 * for boolean value
 */
typedef int Boolean;
#define TRUE 1
#define FALSE 0

/**
 * for query
 */
#define NOTFIND -1

/**
 * for mem malloc
 */
#define OVERFLOW -1

/**
 * for compare
 */
typedef int CmpType;
#define LESSTHAN -1
#define MORETHAN 1
#define EQUAL 0

/**
 * for NULL check
 */
#define isNullPtr(ptr) ((ptr)==NULL)
static void * assert(void * ptr) {
	if(ptr == NULL) {
		printf("in commen.h ptr==null, exit\n");
		exit(FALSE);
	}
	return (void *)ptr;
}

/**
 * for typeExchange
 */
#define typeExchange(type, voidPtr) (*((type*)(voidPtr)))

#endif
