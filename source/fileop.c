/*
 * fileop.c
 *
 *  Created on: 2011-10-12
 *      Author: liyajie
 */
#include <unistd.h>
#include <sys/stat.h>
#include "fileop.h"

long int picture_length(FILE * file, int fb) {
	long int len;
	if (file == NULL) {//使用fstat计算文件长度
		struct stat info;
		fstat(fb, &info);
		len = info.st_size;
	}
	if (fb < 0) {
		fseek(file, 0, SEEK_END);
		len = ftell(file);
		fseek(file, 0, SEEK_SET);
	}
	return (len);
}
/**
 *@param filename the origin picture name
 *@param destfilename the write to file name
 *@return the newfile path
 */
char * picture_in_buffer(const char *filename, const char *destfilename) {
	FILE * file = fopen(filename, "r");
	FILE * newFile = fopen(destfilename, "w");
	int len = picture_length(file, -1);

	char buffer[len];
	/*这里读取的数据不全*/
	int re = fread(buffer, sizeof(buffer), 1, file);
	printf("the re %d\n", re);
	if (!re) {
		printf("read failure \n");
	}
	fwrite(buffer, sizeof(buffer), 1, newFile);
	//得到文件路径的两种方式
	//	char path[80];
	//	getcwd(path, sizeof(path));
	char *path = get_current_dir_name();
	return (path);
}

/**
 *@param filename the origin picture name
 *@param destfilename the write to file name
 *@return the newfile path
 */
char * picture_in_byte(const char *filename, const char *destfilename) {
	FILE * file = fopen(filename, "r");
	FILE * newFile = fopen(destfilename, "w");
	int ch;
	while ((ch = getc(file)) != EOF) {
		putc(ch,newFile);
	}
	char *path = get_current_dir_name();
	return (path);
}
