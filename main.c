/*
 * main.c
 *
 *  Created on: 2011-10-10
 *      Author: liyajie
 */
#include <stdio.h>
#include "source/sqlithandle.h"
#include "source/xmemory.h"
#include "source/sqlite3more.h"

#define DATABASE_NAME "mytest.db"

sqlite3 *db = NULL;
/**
 * 回调函数
 */
void open_callback(sqlite3* database) {
	db = database;
}
/**
 * 打印数据
 * @head the meta header datas
 */
void printList(Table *head) {
	Table * p = head;
	while (p) {
		printf("The tables head name = %s, type = %s\n", p->name, p->type);
		p = p->next;
	}
}
/**
 * the function is invoked when the exec is invoke
 * query data
 */
extern int query(void* data, int colcount, char **values, char**colnames) {
	// 每条记录回调一次该函数,有多少条就回调多少次
	int i;
	for (i = 0; i < colcount; i++) {
		printf("%s = %s\n", colnames[i], values[i] == 0 ? "NULL" : values[i]);
	}
	return 0;
}

void file_opr_test() {
	FILE *file = NULL;
	file = fopen("test.jpg", "r");
	if (file == NULL) {
		printf("file open failure\n");
		return;
	}
	fseek(file, 0, SEEK_END);//移到文件结束
	long int fsize = ftell(file);
	printf("file length is %ld\n", fsize);
	fseek(file, 0, SEEK_SET);
	int len;
	char buff[fsize];
	len = fread(buff, sizeof(char), fsize, file);
	printf("the len= %d\n", len);
	printf("the file msg %s\n", buff);

	FILE * newFile = fopen("back.jpg", "w");
	fprintf(newFile, "%s", buff);
}
int main(int argv, char * agrs[]) {
	file_opr_test();
//	db_open(db, DATABASE_NAME, open_callback);
//	printf("the db is null %s\n", db == NULL ? "true" : "false");
//	printf("the db address is %p\n", db);
	//	//create database/
	//	const char * create_table = "create table userinfo(id integer,"
	//													"uname text not null,"
	//													"pwd text not null,"
	//													"uno integer,"
	//													"rdate text,"
	//													"mblog blob,"
	//													"primary key(id)"
	//													");";
	//
	//	boolean isOk = db_create(db,create_table);
	//	if (isOk) {
	//		printf("table create ok!\n");
	//	} else {
	//		printf("table already exists\n");
	//	}

	// get the database headers
	//	const char* meta_headers = "select * from userinfo";
	//	Table* table = db_meta_names(db,meta_headers);
	//	printList(table);
	//	free_table(table);
	//
	//	//插入数据
	//	const char * sql = "insert into userinfo(id,uname,pwd,uno,rdate) values(?,?,?,?,?);";
	//	char *datas[]  = {
	//			"liyajie",
	//			"123456",
	//			"93283",
	//			"19348723"
	//	};
	//	db_insert_data(db,sql,1,datas,4);
	/*//下面是事务处理插入数据
	 void *datas[] = { { 2, "Alger", "123456", 93283, "you know?" }, { 3,
	 "Li", "123456", 93283, "you know?" }, { 4, "Jack", "123456",
	 93283, "you know?" }, { 5, "XiangYuan", "123456", 93283,
	 "you know?" }, { 6, "Alger", "123456", 93283, "you know?" }, { 7,
	 "Li", "123456", 93283, "you know?" }, { 8, "Jack", "123456",
	 93283, "you know?" }, { 9, "XiangYuan", "123456", 93283,
	 "you know?" } };

	 boolean isOk = db_use_transaction(db,
	 "insert into userinfo(id,uname,pwd,uno,rdate) values (?,?,?,?,?);",
	 datas, 8, 5);
	 if (isOk) {
	 printf("the transaction is perform ok\n");
	 } else {
	 printf("the transaction is failure \n");
	 }
	 */
	//得到数据库数据
	//	db_select_data(db, "select id,uname,pwd,uno,rdate,mblog from userinfo",
	//			NULL, query);
	/*//插入blob对象
	 FILE *file = NULL;
	 file = fopen("test.jpg", "r");
	 if (file == NULL) {
	 printf("file open failure\n");
	 }
	 boolean isOk = db_insert_blob(db,"insert into userinfo(id,uname,pwd,mblog) values(?,?,?,?)",file,7);
	 if (isOk) {
	 printf("insert success !\n");
	 } else {
	 printf("insert blog failure \n");
	 }
	 */

//	db_get_blob(db, "userinfo", "mblog", 7);
//	db_close(db);
//	printf("the db address is %p\n", db);
	return 0;
}
