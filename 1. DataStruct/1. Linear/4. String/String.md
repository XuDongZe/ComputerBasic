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









