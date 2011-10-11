/*
 * sqlite3handle.c
 *
 *  Created on: 2011-10-10
 *      Author: liyajie
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xmemory.h"
/**
 * 释放数据
 * @table 表各列名
 */
extern void free_table(Table *table) {
	if (table != NULL) {
		Table * p = NULL;
		while (table) {
			xfree(table->name);
			xfree(table->type);
			p = table->next;
			xfree(table);
			table = p;
		}
		printf("the table pointer %p\n", table);
	}
}

void db_open(sqlite3 *db, char * db_name, db_open_callback callback) {
	int re = sqlite3_open(db_name, &db);
	printf("the open db %p\n", db);
	if (re != SQLITE_OK) {
		printf("open database error! %s\n", sqlite3_errmsg(db));
		exit(1);
	}
	callback(db);
}
/**
 *
 */
boolean db_create(sqlite3 *db, const char* sql) {
	boolean isSuccess = 0;
	sqlite3_stmt *pstmt;
	int re = sqlite3_prepare(db, sql, strlen(sql), &pstmt, NULL);
	if (re != SQLITE_OK) {//处理不成功
		printf("prepare prepare sql encounter error! %s\n", sqlite3_errmsg(db));
		sqlite3_finalize(pstmt);
		return isSuccess;
	}
	re = sqlite3_step(pstmt);
	if (re != SQLITE_OK && re != SQLITE_DONE && re != SQLITE_ROW) {
		printf("prepare step sql encounter error! %s\n", sqlite3_errmsg(db));
		sqlite3_finalize(pstmt);
		return isSuccess;
	}
	if (re == SQLITE_DONE) {//sql执行完成
		isSuccess = 1;
		printf("the table is create success \n");
	}
	if (re == SQLITE_ROW) {//表示select请句返回一行

	}
	sqlite3_finalize(pstmt);
	return (isSuccess);
}
/**
 * get the column message
 */
Table* db_meta_names(sqlite3 *db, const char *sql) {
	Table *table = NULL;
	sqlite3_stmt *ptmt;
	int i;
	int re = sqlite3_prepare(db, sql, strlen(sql), &ptmt, NULL);
	if (re != SQLITE_OK) {
		printf("meta_names prepare error %s\n", sqlite3_errmsg(db));
		return NULL;
	}
	re = sqlite3_step(ptmt);
	if (re != SQLITE_OK && re != SQLITE_ROW && re != SQLITE_DONE) {
		printf("meta_names sqlite3_step error %s\n", sqlite3_errmsg(db));
		return NULL;
	}
	int cols = sqlite3_column_count(ptmt);
	for (i = 0; i < cols; i++) {//使用头插法进行链表插值
		Table *temp = xmalloc(sizeof(Table));
		temp->name = strdup(sqlite3_column_name(ptmt, i));
		temp->type = strdup(sqlite3_column_decltype(ptmt, i));
		temp->next = table;
		table = temp;
	}
	sqlite3_finalize(ptmt);
	return table;
}

/**
 * insert data to the database
 * @param db
 * @param sql the insert sql
 * @param id the insert id value
 * @param char*[] the columns values to insert
 * @return is success or failure
 * insert into userinfo(id,uname,pwd,uno,rdate) values(?,?,?,?,?);
 */
boolean db_insert_data(sqlite3 *db, const char *sql, int id, char * data[],
		int len) {
	boolean isOk = 0;
	int i;
	sqlite3_stmt *ptmt;
	int re = sqlite3_prepare(db, sql, strlen(sql), &ptmt, NULL);
	if (re != SQLITE_OK) {
		printf("db_insert_data prepare error %s\n", sqlite3_errmsg(db));
		return (isOk);
	}
	sqlite3_bind_int(ptmt, 1, id);
	for (i = 0; i < len; i++) {
		sqlite3_bind_text(ptmt, i + 2, data[i],-1,SQLITE_TRANSIENT);
	}
	re = sqlite3_step(ptmt);
	printf("insert data of the retype = %d\n",re);
	if (re == SQLITE_ROW) {

	}
	sqlite3_finalize(ptmt);
	isOk = 1;
	return (isOk);
}
/**
 * close the database
 */
void db_close(sqlite3 *db) {
	if (db != NULL) {
		int re = sqlite3_close(db);
		if (re != SQLITE_OK) {
			printf("close database error! %s\n", sqlite3_errmsg(db));
			exit(1);
		}
		db = NULL;
	}
}
