/*
 * xmemory.c
 *
 *  Created on: 2011-10-10
 *      Author: liyajie
 */
#include <stdlib.h>
#include "xmemory.h"
/**
 *
 */
void * xmalloc(size_t size) {
	void * ptr = NULL;
	ptr = malloc(size);
	return (ptr);
}

/**
 * @param ptr the pointer memoery to free
 */
void xfree(void *ptr) {
	if (ptr == NULL) {
		perror("there is no memoery to free\n");
		return;
	}
	free(ptr);
}
