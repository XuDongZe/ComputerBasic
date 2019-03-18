#include<iostream>
#include<cstdio>

using namespace std;


/*
	研究 计算机体系结构中的 float、double 的数字表示形式。
	研究 C语言的 内存:
	high addr:
		stack
		heap : increase from low to high just like a heap in the real world.
		static、global、const
			BSS : not_init -> 0 / NULL
			init_ed
		code
	low addr
 */

// 编译后的二进制代码：代码区

int global_not_init; // 全局变量 -> (未初始化的)静态存储区
int global_init = 0;	// 全局变量	-> (初始化的)静态存储区
char global_array[100]; // BSS -> 未初始化的静态存储区

int main() {
	int local_i;	// 栈
	char local_c;	// stack
	char * local_pc = "abc";	// local_pc-> stack, "abc" -> 字符常量区
	char local_array[] = "aaa";	// stack

	static int local_static_i	= 1;	// 静态变量，全局静态存储区

	int * local_malloc_pi = (int *) malloc(sizeof(int ) * 20); // heap : 20 * 4 Byte
	char * local_malloc_pc = (char *) malloc((sizeof(char ) * 20)); // heap : 20 Byte

	return 0;
}