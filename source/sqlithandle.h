/*
 * sqlithandle.h
 * handle the sqlite3 database
 *  Created on: 2011-10-10
 *      Author: liyajie
 */
#include <sqlite3.h>
#include "defdatatypes.h"

#ifndef SQLITHANDLE_H_
#define SQLITHANDLE_H_

/**
 * open the database
 * @param db
 * @param db_name the name of the dabase
 */
void db_open(sqlite3 *db,char * db_name,db_open_callback);
/**
 * create database
 * @param sql
 */
boolean db_create(sqlite3 *db,const char* sql);

/**
 * @param db the database
 * @param sql the sql to use
 * @return Table 列表结构
 */
Table *db_meta_names(sqlite3 *db,const char *sql);

/**
 * insert data to the database
 * @param db
 * @param sql the insert sql
 * @param id the insert id value
 * @param char*[] the columns values to insert
 * @param char*[] length
 * @return is success or failure
 */
boolean db_insert_data(sqlite3 *db,const char *sql,int id,char *data[],int len);


/**
 * close the database
 * @param db the database to close
 */
void db_close(sqlite3 *db);

#endif /* SQLITHANDLE_H_ */
