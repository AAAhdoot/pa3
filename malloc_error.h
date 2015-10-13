#ifndef MALLOC_ERROR_H
#define MALLOC_ERROR_H

#define BLOCKSIZE 5000


#include <stdlib.h>
#include <stdio.h>

typedef struct MemEntry{
	struct MemEntry *prev, *succ;
	int isfree;
	unsigned int size;
}MemEntry;

typedef struct MemEntry* MemPtr;

void *mymalloc(unsigned int size);

void myfree(void *p1);



#endif