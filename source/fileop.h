/*
 * fileop.h
 * 记录我在读取图片文件时碰到的问题
 * <p>
 *  1. 第一次读取流到buffer中时，会出现文件读取不全的错误
 *  2.使用第二种笨方法，一个字一个字的读取
 * </p>
 * 最后第一个写到新的图片错误
 * 第二个写入到一个新的图成功
 *  Created on: 2011-10-12
 *      Author: liyajie
 */
#include <stdio.h>


#ifndef FILEOP_H_
#define FILEOP_H_
/**
 *@param file
 *        if the file is NULL then use the linux operator fstat calculator the file length
 *@param fb
 *	      calculator the file length by the file descriptor
 *@return
 *		the file length
 */
long int picture_length(FILE * file,int fb);
/**
 *@param filename the origin picture name
 *@param destfilename the write to file name
 *@return the newfile path
 */
char * picture_in_buffer(const char *filename,const char *destfilename);

/**
 *@param filename the origin picture name
 *@param destfilename the write to file name
 *@return the newfile path
 */
char * picture_in_byte(const char *filename,const char *destfilename);

#endif /* FILEOP_H_ */
