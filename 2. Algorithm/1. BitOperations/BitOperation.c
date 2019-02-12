#include <stdio.h>
#include "../../1. DataStruct/1. Linear/1. ListTable/ArrayList.h"

/**
 *  & | ^ ~
 *  1101 >> 2 = 11
 *  1101 << 3 = 1101000
 *
 *  x = 5 -> 101 if(x > 0)
 *  x = -5 -> ~x + 1 -> 010 + 1 -> 011
 *  即 -5 -> 11111111111111011(32 bit).
 */
/**
	 *  x = 10111001
	 *  -x= 01000111 (~x+1)
	 *  & = 00000001
	 *
	 *  即(x & -x) 表示 x的二进制表示中最低位的1保持不变, 其余为置0
	 *  		-> 最靠右的1.
	*/
int isPowerOfTwo(int n) {
	return (n > 0 && (n & -n) == n);
}

/**init res = 0;
 * while(n != 0), do:
 * 	res += n & 1;
 *  n >> = 1;
 * end while;
*/
int getOneNumsInBinaryStream(int n) {
	int res = 0;
	for(int k=n; k; k >>= 1) res += k & 1;
	return res;
}

/**
 * a list : which the data will occur twice except one. and find the one.
 * use ^ 异或运算
 * 异或：不进位加法
 * 结合律：(a ^ b) ^ c = a ^ (b ^ c)
 * 交换律：a ^ b = b ^ a
 * 真值表：
 * 0 0 0
 * 0 1 1
 * 1 0 1
 * 1 1 0
 *
 * 所以list中出现twice的元素会两两相消，只剩下the once.
 */
int singleNumber(ArrayList* list) {
	int res = 0, r;
	int i = 0, size = getSize(list);
	while(i < size) {
		getIdx(list, i++, &r);
		res ^= r;
	}

	return res;
}

/**
 * given a number, and return it's complete number, remember it don't care the 0 in the front.
 * 在不考虑前导0的情况下 返回 一个数字的 反码。
 * 5(101) -> 2(010)
 * 1 -> 0
 *
 * using (&, >>) 遍历num的二进制数位
 * 对于每一位，取反，并放置到相应的数位上。
 */
int findComplement(int num) {
	int res = 0, t = 0;
	while(num) {
		/**
		 *  ! 与 ~
		 *  ~ 按位反，每一位取反
		 *  ！逻辑非，非0值返回1，
		 */
		res += !(num & 1) << t;
		num >>= 1; t++;
	}
	return res;
}

/**
 * a list each element occur 3 times except one, find the very one.
 * 4 4 4 5 6 6 6 -> 5
 * assume the data is x. and now we will find it.
 * first think that if we remove x from the list. so each data occur 3 times.
 * if we calculate the bit-sum for each bit loop each data.
 * each bit-sum from 0(th) -> 31(th) is %3 == 0.
 *
 * now we add x to the bit-sum.
 * consider the i(th) bit is 1, so the bit-sum(i_th) will be: 3*k+1.
 * if the i(th) is 0, so the bit-sum(i-th) will be 3*k.
 *
 * so we can get x by get each bit of it:
 * x(i-bit) = bit- sum(i-th) % 3.
 *
 * and we can use the bits to calculate x.
 */
int singleNumberII(ArrayList* list) {
	int res = 0, sum = 0;
	int size = getSize(list), r=0;
	//outer loop for get each bit: for 32-bit int.
	for(int bit=0; bit < 32; bit++) {
		sum = 0;
		//inner loop for i-th bit-sum in list. 
		for(int i=0; i<size; i++) {
			getIdx(list, i, &r);
			sum += (r >> bit) & 1; 
		}
		res += (sum % 3) << bit;
	}

	return res;
}
/**
 * calculate the sum a and b. please do not use + 
 * then we can use ^: remember that ^ is a operation that don't include carry bit.
 * now assume that in 10:
 * 1234 + 9876:
 *   1 2 3 4
 * + 9 8 7 6
 * ---------
 *   0 0 0 0 -> don't consider the carry bit : in binary -> a ^ b
 *   1 1 1 1 -> just consider the carry bit  : in binary -> (a & b) << 1
 * 1 1 1 1 0 -> carry bit left-shift one bit 
 * 1 0 0 0 0
 */
int getSum(int a, int b) {
	if(!b) return a;
	int sum = a ^ b, carry = (a & b) << 1;
	return getSum(sum, carry);
}

int getHammingDistance(int a, int b) {
	int res = 0;
	for(int bit = 0; bit < 32; bit++) {
		res += (a>>bit)&1 ^ (b>>bit)&1;
	}
	return res;
}

/*
	given a list of int. each of a pair will get a hammingdistance.
	the pairs will be n*(n-1)/2.
	and calculate the sum of the hammingdistance.

	we can easily get the sum by get each distance and then add to res which inited use 0.
	in this way, the time compelex is 32 * n * (n-1) /2 => O(n^2).

	now consider another method.in this method we consider one bit,and add each bit-sum.
	assume the bit list is:
	list = 1 0 1 0
	the distance(list) = SumOf( distance(a, b): for(a in list, b in list) ) / 2.
	
	but consider distance(a, b) = a ^ b. using this:
	we can easily get the sum of m * n, in which m is the num of 1, n is the nums of 0.
	this can be certify:  we choose one in m-heap, and another one in n-heap. the distance bettewn
	this two heap is 1, and in a heap we choose two bits the distance will be 0.
	
	so we change the sum calculate into a 
 */
int totalHammingDistance(ArrayList * list) {
	int size = getSize(list);
	int m, n, r;
	int res = 0;
	for(int bit = 0; bit < 32; bit++) {
		 m = n = 0;
		for(int i=0; i<size; i++) {
			getIdx(list, i, &r);
			if( (r >> bit)&1 ) m++;
			else n++;
		}
		res += m * n;
	}

	return res;
}

int main() {
	int n;
	int a, b;
	// scanf("%d,%d", &a, &b);
	// printf("getHammingDistance(%d,%d) = %d\n",a, b, getHammingDistance(a, b)); 
	ArrayList* list = initList(10);
	append(list, 1);
	append(list, 2);
	append(list, 2);
	append(list, 3);
	printf("totalHammingDistance(list) = %d\n", totalHammingDistance(list));

	// printf("isPowerOfTwo(%d) :%d, getOneNumsInBinaryStream(%d): %d\n"
	// 	,n, isPowerOfTwo(n), n, getOneNumsInBinaryStream(n) );
	// printf("singleNumberII(list) = %d\n", singleNumberII(list));
	// printf("findComplement(%d) = %d\n", n, findComplement(n) );

	return  0;
}