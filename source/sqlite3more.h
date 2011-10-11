/*
 * sqlite3more.h
 *
 *  Created on: 2011-10-11
 *      Author: liyajie
 */
#include <sqlite3.h>
#include "defdatatypes.h"


#ifndef SQLITE3MORE_H_
#define SQLITE3MORE_H_
/**
 * 处理查询数据
 */
typedef int (*data_handle)(void*,int,char**,char**);
/**
 * select data from the database
 * @param db the database
 * @param sql select sql
 * @param args callback arguments
 * @param callback
 * @return datas return values
 */
void* db_select_data(sqlite3 *db,const char* sql,void* args,data_handle callback);
/**
 * 事务处理
 * @param db
 * @param sql
 * @param datas values to insert into tables
 * @param len the datas length
 * @param cols
 * @return is ok
 */
boolean db_use_transaction(sqlite3 *db,const char *sql,void **datas,int len,int cols);
/**
 * insert blob into the database
 * @param db
 * @param sql
 * @param buff data to insert
 * @param offset
 * @param id
 * @return is ok or not
 */
boolean db_insert_blob(sqlite3 *db,const char *sql,FILE * file,int id);
/**
 * get the blob
 * @param db
 * @param sql
 */
void db_get_blob(sqlite3 *db,const char sql);

#endif /* SQLITE3MORE_H_ */
