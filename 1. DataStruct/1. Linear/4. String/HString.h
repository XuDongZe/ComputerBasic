#ifndef _STRING_H_
#define _STRING_H_ 

#include "../../Commen/commen.h"

/**
 * 堆分配的 基于 ASIIC字符集的字符串结构
 */
typedef struct HeapString
{
	char * ch;
	int length;
}HeapString, *HString;

/**
 * 串的生命周期
 */
HString initStr(); //初始化一个空串
Status clearStr(HString ); //清空为空串 -> status for str is null
void destoryStr(HString *);

/**
 * 两串之间的操作
 */
//c 语言中 字符串常量做函数参数怎末写？？？
Status assignStr(HString, const char *); 
void copyStr(HString, const HString);
CmpType compareStr(const HString, const HString);

/**
 * 子串操作
 */
HString getSubStr(HString, int begin, int length);
int querySubStr(const HString, int, const HString);
int querySubStrKMP(const HString src, int begin, const HString sub);

/**
 * 串信息
 */
int getLength(HString);
char getIdx(HString, int);
Status setIdx(HString, int, const char);

#endif