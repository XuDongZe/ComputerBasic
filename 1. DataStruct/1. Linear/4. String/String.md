## 串

### 逻辑结构
* 以 字符 为存储内容的 线性表。
* 串的结尾判定通常有两种做法：
	* 在结构中设置length字段并予以维护
	* 以特殊的字符结尾(如'\0')并予以维护

### 存储结构
* 顺序存储结构
```c
struct SeqString {
	unsigned char ch[MAX_STR_SIZE];
	int length;
};
```
* 堆分配存储结构
```c
struct HString {
	unsigned char * ch;
	int length;
}HString;
```
* 块链式存储结构
```c
struct Chunk {
	unsigned char ch[MAX_CHUNK_SIZE];
	struct Chunk * next;
};
struct CString {
	struct Chunk * head;
	struct Chunk * tail;
	int length;
};
```

### 操作API
* 得到串的方法
	* 初始化一个空串
	* 使用字符串常量 串赋值
	* 串复制
	* 从串中返回子串
* 串运算
	* 串连接
	* 串比较
* 串信息访问
	* 按idx, get set 某字符的访问方法
	* 串长度
* 子串查询
	* 模式匹配
* 串清空为空串
* 串销毁

### 复杂度分析
* 堆分配的存储结构
	* 复制、赋值、比较、销毁、连接(基于复制) 	-> O(n)
	* 初始化、清空、getIdx，setIdx，getLength	-> O(1)
	* 返回字串 -> O(m),m为子串长，一般为O(n)级别
	* 模式匹配	-> KMP O(m+n) 母串和子串长度之和

### 注意事项
* 注意从前往后遍历，还是从后往前遍历。取决于怎样"新鲜数据"在遍历过程中不会被覆盖。
* 顺序存储结构：串复制、串赋值、串连接 时可能会存储空间溢出。
	* 截断并返回标志
	* 报错
* 块链式存储结构
	* 串连接时要注意最后一个块是否是满的。
		* 否则需要往前移动？？？挪动？？？？
	* 一般不使用：操作复杂、空间利用率低

### 相关应用和算法
* 模式匹配KMP
	* 简单匹配
	* KPM1
	* KMP2
* 行编辑程序
* 索引字典

### KMP算法
> 避免不必要的回溯，那么需要定义 什么是不必要的呢? 这是问题的核心。
* 知道了什么是不必要的，那么如何做，才能避免不必要的回溯呢？首先回溯出现的时机是在失配时，那么通常的做法是怎样的呢？是让模式串和母串中此次匹配开始位置的下一位置进行对齐。具体做法如下：
```c
// i 匹配串当前匹配位置指针
// j 模式串当前匹配位置指针
// n 第几次匹配 
//i(n) 表示第n次匹配开始的位置，也就是第n-1次匹配失配的下一位置
i(n+1) = i(n) + 1;
j(n+1) = 0;
//i: i(n) -> i
//j: 0	-> j
// => i(n+1) = i(n)+1 = i-j+1
```
* KMP采用这样的方式：当失配发生时，使模式串T向右滑动“尽可能远的” 的距离，这是说让T[0]尽可能地和S中下标较大的元素对齐，而这是由S[i]和T[k]匹配决定的。具体做法如下：
```c
//设模式串T与主串S失配，失配时位置为j，i。寻找这样的k：
//T[0...(k-1)] = S[(i-k)...(i-1)]; 下一次匹配时，我们只需要让S[i]和T[k]匹配即可。
//也就是令：i不变，仍指向失配位置。
//j = k;
//由于j迭代为k，所以我们令next[j] = k，表示模式串中失配之后的与匹配串位置i相匹配的下一位置;
也就是 j = next[j]; (next[j] = k, 已经提前根据模式串计算出)。

//由失配我们已经有：
T[0...(j-1)] = S[(i-j)...(i-1)] && T[j] != S[i]
//所以如果模式串满足：
T[0...(k-1)] = T[(j-k)...(j-1)]时，(k<=j), 
//我们有
T[0...(k-1)] = S[(i-k)...(i-1)]成立。

//反过来，我们要找的k就是这样的，这完全是由模式串决定的。
T[0...(k-1)] = T[(j-k)...(j-1)]，(1<= k <=j).
```

* 思路启发1
```c
	0 1 2 3 4 5 6 7 8 9 
S	  i l o v e f i s h 
T	  i l o v x
T			  i l o v x
则有：
i1 = j1, i2 = j2, i3 = j3, i4 = j4
而在模式串中
j1 != j2 != j3 != j4
所以有
i1 != j2 != j3 != j4
所以当失配时，即当i5 != j5发生时：

next[j] = 0 + 1;
此时模式串中没有重复的，相当与让T[1] = S[i], 滑动的距离最远。
```
* 思路启发2
```c
	0 1 2 3 4 5 6 7 8 9
S  	  w w w . x d z . c
T	  w w .
T		w w .
则有：
i1 = j1, i2 = j2, i3 != j3
模式串属性：
j1 = j2
所以有：S[i] = T[k] = T[next[j]]
=> next[j] = 1 + 1
```
* 思路启发3
```c
	0 1 2 3 4 5 6 7 8 9
S	  b b s b b s . f i n
T	  b b s b b c
T		    b b s b b c
则有 S[1...5] == T[1...5] && S[6] != T[6]
模式串属性：
T[1...2] == T[4...5],
那么有：S[i] = T[k] = T[next[j]], (i = j = 6) 
next[j]  = 2 + 1 = 3
```
* 思路启发4
```c
	0 1 2 3 4 5 6 7 8 9
S	  s s s s s s s x
T	  s s s x

```

### KMP总结与推导
* 使用KMP：
```c
int	queryKMP(const String str1, int idx, const String str2) {
	int i = idx, j = -1;
	next[0...getLength(str2)] = getNext(str2);
	while(j<getLength(str2) && i<getLength(str1)) {
		if(j==-1 || getIdx(str2, j)==getIdx(str1, i))	{i++; j++; }
		else {j = next[j]};
	}
 	if(j == getLength(str2)) 
		return i - j;
	return NOTFIND;
}
```
* 计算模式串的next:
```c
getNext(const String str) {
	length = getLength(str);
	next[0] = -1;
	i = 0; j = -1;
	while( i < length ) {
		if(j==-1 || str[i]==str[j]) {
			i++; j++; 
			if( str[i] != str[j] )	next[i] = j;
			else next[i] = next[j];
		}
		else j = next[j]; 
	}
}
```








