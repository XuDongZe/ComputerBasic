#include "HString.h"

/**
 * 串的生命周期
 */
//初始化一个空串
HString initStr() {
	HString str = (HString ) assert(malloc(sizeof(HeapString)));

	str->ch = NULL;
	str->length = 0;

	return str;
} 

//清空为空串 -> status for str is null
//如何释放一块连续内存？？？
Status clearStr(HString str) {
	if(str == NULL)
		return FALSE;
	
	free(str->ch);	str->ch = NULL;
	str->length = 0;
	return TRUE;
}
void destoryStr(HString *pstr) {
	if(*pstr == NULL)
		return;
	clearStr(*pstr);
	free(*pstr);	*pstr = NULL;
}

/**
 * 两串之间的操作
 */
//c 语言中 字符串常量做函数参数怎末写？？？
//malloc(0)会怎么样
Status assignStr(HString dst, const char * src) {
	int i = 0, length = 0;;
	if(dst == NULL || src == NULL)
		return FALSE;
	
	while(src[length++] != '\0');
	length--;

	clearStr(dst);
	dst->ch = (char *) assert(malloc(length * sizeof(char)));
	dst->length = length;

	for(i = 0; i < length; i++) {
		*(dst->ch + i) = src[i];
	}

	return TRUE;
}

void copyStr(HString dst, const HString src) {
	int length = getLength(src);

	clearStr(dst);
	dst->ch = (char *) assert(malloc(src->length * sizeof(char)));
	dst->length = length;

	int i = 0;
	while(i < length) {
		setIdx(dst, i, (src->ch)[i]);
		i++;
	}
}

CmpType compareStr(const HString str1, const HString str2) {
	int i = 0;
	int l1 = getLength(str1), l2 = getLength(str2);
	char ch1 = '\0', ch2 = '\0';
	while(i < l1 && i < l2) {
		ch1 = getIdx(str1, i), ch2 = getIdx(str2, i);
		if(ch1 > ch2)
			return MORETHAN;
		else if(ch1 < ch2)
			return LESSTHAN;
		i++;
	}
	return (l1 - l2)>0 ? MORETHAN : (l1-l2==0 ? EQUAL : LESSTHAN);
}

/**
 * 子串操作
 */
HString getSubStr(const HString str, int begin, int length) {
	if(begin < 0 || begin+length >= str->length)
		return FALSE;
	HString sub = initStr();
	sub->ch = ( char *) assert(malloc(length * sizeof( char)));
	sub->length = length;

	int i, j;
	for(i=begin, j=0; j<length; i++, j++) {
		*(sub->ch + j) = *(str->ch + i);
	}

	return sub;
}

/**
 * 串信息
 */
int getLength(HString str) {
	return str == NULL ? 0 : str->length;
}
char getIdx(HString str, int idx) {
	if(idx < 0 || idx >= str->length) {
		printf("in getIdx, idx=%d overflow, length=%d\n", idx, str->length);
		return ERROR;
	}
	return *(str->ch + idx);
}
Status setIdx(HString str, int idx, const char ch) {
	if(idx < 0 || idx >= str->length)
		return FALSE;
	*(str->ch + idx) = ch;
	return TRUE;
}

void printStr(const HString str) {
	if(str == NULL)
		return;
	int i = 0, length = getLength(str);
	while(i < length) {
		printf("%c", *(str->ch + i));
		i++;
	}
	printf("\n");
}

/**
 * [querySubStr 模式匹配算法, 在母串中第begin下标开始寻找，返回第一个匹配的子串的下标]
 * @param  src [母串]
 * @param  sub [子串]
 * @return     [子串第一个返回的下标：begin ~ src->length-1, 未找到返回-1 NOTFIND: commen.h]
 */
int querySubStr(const HString src, int begin, const HString sub) {
	if(begin + sub->length > src->length) 
		return NOTFIND;
	int i = begin, j = 0;
	while(j<sub->length && i<src->length) {
		if(*(src->ch + i) == *(sub->ch + j)) {
			i++;
			j++;
		}
		else {
			/**
			 *  i : x -> i
			 *  j : 0 -> j
			 *  now *(src->ch+i) != *(sub->ch+j) first occur && j<sub->length
 			 *  then match false, we need try agin:
 			 *  j <- 0
			 *  i <- x+1 = i-j+1
			 */
			i = i - j + 1;
			j = 0;
		}
	}
	/**
	 *  i : x -> i
	 *  j : 0 -> j
	 *  now *(src->ch+i) != *(sub->ch+j) first occur && j==sub->length
	 *  then match success
	 *  return x: the begin idx of src string -> i-j.
	 */
	
	if(j == sub->length)	return i-j;
	return NOTFIND;
}

int querySubStrKMP(const HString src, int begin, const HString sub) {

}

// int main() {
// 	HString str1 = initStr(), str2 = initStr();
// 	printf("init over, str1->length=%d, str2->length=%d\n", getLength(str1), getLength(str2));
// 	printf("cmp str1&str2, %d\n", compareStr(str1, str2));
	
// 	assignStr(str1, "abcdefg");
// 	printf("assign over, str1->length=%d, str2->length=%d\n", str1->length, str2->length);
// 	printStr(str1);
// 	printf("cmp str1&str2, %d\n", compareStr(str1, str2));

// 	copyStr(str2, str1);
// 	printf("copy over, str1->length=%d, str2->length=%d\n", str1->length, str2->length);
	
// 	printStr(str1); printStr(str2);
// 	printf("cmp str1&str2, %d\n", compareStr(str1, str2));
	
// 	setIdx(str1, 0, 'A');
// 	printf("getIdx(%d) %c\n", 0, getIdx(str1, 0));
// 	printStr(str1);
// 	printf("cmp str1&str2, %d\n", compareStr(str1, str2));

// 	str2 = getSubStr(str1, 0, getLength(str1)/2);
// 	printf("getSub over, str1->length=%d, str2->length=%d\n", str1->length, str2->length);
// 	printStr(str2);

// 	assignStr(str1, "abcdabcdabcdabcabcabcd");
// 	assignStr(str2, "ab");
// 	printStr(str1);
// 	printStr(str2);
// 	int idx = 0;
// 	HString s = NULL;
// 	while(idx != NOTFIND && idx < getLength(str1)) {
// 		if( (idx=querySubStr(str1, idx, str2)) != NOTFIND ) {
// 			printf("%d, ", idx);
// 			idx += getLength(str2);
// 		}
// 	}
// 	printf("\n");

// 	clearStr(str1);
// 	printf("clear over, str1->length=%d, str2->length=%d\n", str1->length, str2->length);
// 	printf("cmp str1&str2, %d\n", compareStr(str1, str2));

// 	destoryStr(&str1);
// 	destoryStr(&str2);

// 	printf("test over\n");
// 	return 0;
// }

