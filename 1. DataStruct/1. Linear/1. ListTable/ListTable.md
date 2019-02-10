## 线性表

### 逻辑结构
* 数据元素之间是一对一的关系，线性结构的基本属性
* 第一个元素有且仅有一个后继
* 最后一个元素有且仅有一个前驱
* 其余元素有一个前驱和一个后继

### 存储结构
* 顺序
	* 数组: 常用程序设计语言已经实现
		* -> 编译器中的数组支持
	* 可变数组 -> 自实现
		* -> Java的ArrayList分析
* 链式
	* 静态链表 -> 自实现
		* -> 静态链表的思想分析
	* 动态链表 -> 自实现
		* -> Java的LinkedList分析

### 动态数组ArrayList
```c
	typedef struct ArrayList {
		int * array;
		int capacity;	//the max amount of element which the list allow
		int length;		//the current amount of element
	}ArrayList;
	//init
	ArrayList* init(int capacity);
```
### 静态链表StaticList
```c
	typedef struct StaticListNode {
		int data;
		int next;
	}SNode, *psNode;

	SNode StaticList[MAX_STATICLIST_SIZE];
```
### 动态链表LinkedList
```c
	typedef struct LinkListNode {
		int data;
		struct LinkListNode * next;
	}LNode, *plNode;

	//泛型两种实现形式
	//first void*
	typedef struct GenericLinkNode {
		void * data;
		struct GLNode * next;
	}GenericLinkNode, *GLNode;
	typedef struct GenericLinkList {
		GLNode head;
		//other info you want to store
	}GenericLinkList, *GList;
	
	//second 反向寻址 + user-defined GLNode
	#define getStartAddr(type, subAddr, member)	\
		( (char *)(subAddr) - (char *)(&(((type *)0)->member)) )

	typedef struct GenericLink {
		sturct GenericLink * link;
		//other links;
	}GenericLink, *GLink;
	typedef struct GenericLinkNode {
		int iData;	//you will change this
		GLink link;	//just add this in the last element in the GenericLinkNode Struct.
	}GenericLinkNode, *GLNode;
	typedef struct GenericLinkList {
		GLNode head;
		//other info you want to store
	}GenericLinkList, *GList; 

```

### 操作API
```c
	//insert, Status for idx	
	Status insert(int data, int idx);	//after the very idx

	//delete, Status for data not exsit
	Status delete(int data);

	//update, Status for idx
	Status update(int idx, int newData);

	//query, int include not find -> NULL
	int query(int data);
	
	//for data access by idx
	int getData(int idx);
```

### 分析：存储-操作-复杂度
* ArrayList:
	* 连续存储空间，支持随机访问: getData(idx)、update(idx, data) -> O(1)
	* insert(idx, data)、delete(idx)、 query(data) -> O(n)
* StaticList、LinkedList:
	* 不支持随机访问，getData(idx)、update(idx, data)-> O(n)
	* insert(node)、delete(node) -> O(1)
	* query(data) -> O(n)

### 代码目录结构
* 代码仓库
	* 
* 顺序存储结构
	* ArrayList.h
	* ArrayList.c 	包括测试main
* 链式存储结构	支持泛型 void * 存储数据
	* LinkedList.h
	* LinkedList.c
	* test.c
* 泛型结点	可用于链式结构中
	* Generic.h
	* Generic.c 	包括测试main

### 问题
* 关于循环链表中的头节点问题
	* 由于头结点是虚拟节点，并不存储实际数据，因此从链表中部遍历该链表时，会经历该头节点，这就意味着我们在遍历时需要判断每一个节点是不是头节点；即我们必须要做这样一个判断：该节点内的数据是有效的吗？
	* 如何优雅地从任意地方遍历一个，带有头节点的双向链表
