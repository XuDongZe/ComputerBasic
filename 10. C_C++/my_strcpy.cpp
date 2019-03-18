#include<iostream>
#include<cassert>
#include <cstring>

using namespace std;

static char * my_memcpy(char * dst, const char * src, int cnt);
char * my_strcpy(char * dst, const char * src);

/*
	没有内存重叠的版本。
char * my_strcpy(char * dst, const char * src) {
	assert(dst != NULL && src != NULL);
	
	char * ret = dst;
	while( (*dst++ = *src++) != '\0' )
		NULL ;

	return ret;
}
*/

/*
	自动检测内存重叠，并处理之：从后往前(自高地址开始)复制。
 */
char * my_strcpy(char * dst, const char * src) {
	assert(dst != NULL && src != NULL);
	const char * s = src;
	
	int len = 0;
	// 注意此处更改了src指针，所以要将src实现保存下来；要么就使用偏移量 i。
	while(* s++ != '\0' ) len ++;	//不包括 '\0'的长度

	return my_memcpy(dst, src, len + 1); //加上 '\0'
}

/*
	dst[0 : cnt) = src[0 : cnt)(全闭区间) src[cnt - 1] == '\0'
	内存重叠：
		复制过程中，src未复制到dst的内存单元被覆盖。
	内存重叠原因：dst 起始位置 位于有效的src内存空间中。
		src <= dst <= src + cnt - 1. 
	重叠解决方法：从后往前复制，返回src的地址。
		dst[cnt - 1 : 0] = src[cnt - 1 : 0]
 */
static char * my_memcpy(char * dst, const char * src, int cnt) {
	assert(dst != NULL && src != NULL);

	char *s = (char *)(src), * ret = dst;

	if( dst >= src && dst <= src + cnt - 1) {
		dst = dst + cnt - 1;
		src = src + cnt - 1;
		// dst(cnt : 0] = src(cnt : 0], 总共cnt 次。src[cnt - 1] == '\0'
		while(cnt --)
			* dst-- = * src--;
		ret = s;
	}else {
		while(cnt --)
			* dst++ = * src++;
	}

	return ret;
}

int main() {
 	char s[10] = "hello";
 	char * d;
	
	cout << my_strcpy(s, s + 1) << endl;

	cout << my_strcpy(s + 1, s) << endl;

	return 0;
}
