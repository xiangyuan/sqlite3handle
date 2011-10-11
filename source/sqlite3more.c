/*
 * sqlite3more.c
 *
 *  Created on: 2011-10-11
 *      Author: liyajie
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3more.h"

/**
 *
 */
void* db_select_data(sqlite3 *db, const char* sql, void* args,
		data_handle callback) {
	char * errMsg;
	int re = sqlite3_exec(db, sql, callback, args, &errMsg);
	if (re != SQLITE_OK) {
		perror(errMsg);
		sqlite3_free(errMsg);
		return NULL;
	}
	return NULL;
}
/**
 *
 */
boolean db_use_transaction(sqlite3 *db, const char *sql, void **datas, int len,
		int cols) {
	boolean isOk = 0;
	boolean isCommit = 0;
	char *errMsg;
	sqlite3_stmt *ptmt;
	sqlite3_prepare(db, sql, strlen(sql), &ptmt, NULL);
	int re = sqlite3_exec(db, "begin;", NULL, NULL, &errMsg);
	if (re != SQLITE_OK) {
		perror(errMsg);
		sqlite3_free(errMsg);
	}
	int i;
	//绊定数据
	for (i = 0; i < 5; i++) {
		sqlite3_bind_int(ptmt, 1, i + 2);
		sqlite3_bind_text(ptmt, 2, "Alger", -1, SQLITE_TRANSIENT);
		sqlite3_bind_text(ptmt, 3, "Alger", -1, SQLITE_TRANSIENT);
		sqlite3_bind_int(ptmt, 4, rand());
		sqlite3_bind_text(ptmt, 5, "Alger", -1, SQLITE_TRANSIENT);
		//		for (j = 0; j < cols; j++) {
		//			if (j == 0 || j== 3) {
		//				sqlite3_bind_int(ptmt, j + 1, *(((int *) datas + i) + j));
		//			} else {
		//				re = sqlite3_bind_text(ptmt, j + 1,
		//						*(((const char*) datas + i) + j), -1, SQLITE_TRANSIENT);
		//				if (re != SQLITE_OK) {
		//					perror(sqlite3_errmsg(db));
		//					exit(0);
		//				}
		//			}
		//		}
		re = sqlite3_step(ptmt);
		if (re != SQLITE_OK && re != SQLITE_DONE) {
			printf("the step code is %d\n", re);
			perror(sqlite3_errmsg(db));
			isCommit = 0;
		} else {
			isCommit = 1;//success
			re = sqlite3_reset(ptmt);
			if (re != SQLITE_OK) {
				perror(sqlite3_errmsg(db));
				exit(0);
			}
		}
	}
	if (isCommit) {
		re = sqlite3_exec(db, "commit;", NULL, NULL, &errMsg);
		if (re != SQLITE_OK) {
			perror(errMsg);
			sqlite3_free(errMsg);
		}
		isOk = 1;
	} else {
		sqlite3_exec(db, "rollback;", NULL, NULL, &errMsg);
		if (re != SQLITE_OK) {
			perror(errMsg);
			sqlite3_free(errMsg);
		}
	}
	sqlite3_finalize(ptmt);
	return (isOk);
}
/**
 *最好是加入事务的，在此不进行操作
 */
boolean db_insert_blob(sqlite3 *db, const char *sql, FILE * file, int id) {
	boolean isOk = 0;
	sqlite3_stmt *ptmt;
	sqlite3_prepare(db, sql, strlen(sql), &ptmt, NULL);

	fseek(file, 0, SEEK_END);//移到文件结束
	long int fsize = ftell(file);
	printf("file length is %ld\n", fsize);
	fseek(file, 0, SEEK_SET);
	sqlite3_bind_int(ptmt, 1, id);
	sqlite3_bind_text(ptmt, 2, "work", -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(ptmt, 3, "13213123", -1, SQLITE_TRANSIENT);
	int len;
	char buff[fsize + 1];
	len = fread(buff, sizeof(char), fsize + 1, file);
	printf("the len is %d\n", len);
	//	re = sqlite3_blob_write(mblog, buff, fsize + 1, 0);
	//	if (re != SQLITE_OK) {
	//		exit(0);
	//	}
	//	int re = sqlite3_bind_zeroblob(ptmt, 4, fsize);
	int re = sqlite3_bind_blob(ptmt, 4, buff, fsize, NULL);
	if (re != SQLITE_OK) {
		sqlite3_finalize(ptmt);
		perror(sqlite3_errmsg(db));
		fclose(file);
		return (isOk);
	}
	re = sqlite3_step(ptmt);
	if (re != SQLITE_OK && re != SQLITE_DONE) {
		sqlite3_finalize(ptmt);
		perror(sqlite3_errmsg(db));
		fclose(file);
		return (isOk);
	}
	//	//然后打开部分进行写入数据
	//	sqlite3_blob * mblog;
	//	re = sqlite3_blob_open(db, NULL, "userinfo", "mblog", id, 2, &mblog);
	//	if (re != SQLITE_OK) {//encounter some error
	//		printf("the re = %d\n", re);
	//		sqlite3_finalize(ptmt);
	//		perror(sqlite3_errmsg(db));
	//		fclose(file);
	//		return (isOk);
	//	}

	//	char buff[1024 * 4];
	//	int len = 0;
	//	int i;
	//	i = 1;
	//	while ((len = fread(buff,sizeof(buff),1,file)) > 0 ) {
	//		printf("the read length len =%d\n",len);
	//		re = sqlite3_blob_write(mblog,buff,len,0);
	//		fseek(file,sizeof(buff)*i,SEEK_SET);
	//		i ++;
	//		if (re != SQLITE_OK) {
	//			exit(0);
	//		}
	//	}
	//	fseek(file,0,SEEK_SET);
	isOk = 1;
	fclose(file);
	sqlite3_finalize(ptmt);
	return (isOk);
}
