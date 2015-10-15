#ifndef MALLOC_ERROR_H
#define MALLOC_ERROR_H
#define BLOCKSIZE 6400


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define malloc(x) my_malloc( x, __FILE__, __LINE__)
#define free(x) my_free( x, __FILE__, __LINE__)


typedef struct MemEntry{
	struct MemEntry *prev, *succ;
	int isfree;
	unsigned int size;
}MemEntry;

typedef struct MemEntry* MemPtr;

void *my_malloc(unsigned int size, char* file, int line);

void my_free(void *p1, char* file, int line);



#endif