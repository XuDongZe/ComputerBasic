### windows启动mysql

> net start mysql

> net stop mysql

> mysql -u root

### 数据库语句

* 创建数据库
```mysql
create database 数据库名 ;
```
* 数据库信息查看
```mysql
show databases;
```
* 删除数据库
```mysql
drop database 数据库名;
```
### 存储引擎 
* https://blog.csdn.net/huyiju/article/details/80968962
* https://blog.csdn.net/m0_37888031/article/details/80664138

* 查看数据库支持的存储引擎
```mysql
show engines ; /g /G(/g表示按序显示)
show variables like 'have_%' ;
show variables like '%storage_engine%';
```
* 查看表使用的存储引擎
```mysql
show create table 表名;
show table status from DBName;
```
* 指定表的存储引擎
```mysql 
create table 表名(
	...
	)engine/type = 引擎名;
```
* 修改表的存储引擎
```mysql
alter table 表名 engine = 引擎名;
```

