/*
 * defdatatypes.h
 *
 *  Created on: 2011-10-11
 *      Author: liyajie
 */

#ifndef DEFDATATYPES_H_
#define DEFDATATYPES_H_

typedef int boolean;

/**
 * 查找出的所有数据表列名信息
 */
typedef struct Table Table;

struct Table {
	char *name;
	char *type;
	Table * next;
};

typedef void (*db_open_callback)(sqlite3*);

#endif /* DEFDATATYPES_H_ */
