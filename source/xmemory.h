/*
 * xmemory.h
 *
 *  Created on: 2011-10-10
 *      Author: liyajie
 */
#include <stdio.h>
#include "sqlithandle.h"

#ifndef XMEMORY_H_
#define XMEMORY_H_

/**
 * @param size size to malloc
 * @return ptr
 */
void * xmalloc(size_t size);

/**
 * @param ptr the pointer memoery to free
 */
void xfree(void *ptr);
/**
 * release the table datas
 * @param table
 */
extern void free_table(Table *table);

#endif /* XMEMORY_H_ */
