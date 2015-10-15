#ifndef MALLOC_ERROR_H
#define MALLOC_ERROR_H

#define BLOCKSIZE 5000


#include <stdlib.h>
#include <stdio.h>

#define malloc(x) mymalloc(x,__FILE__,__LINE__);
#define free(x) myfree(x,__FILE__,__LINE__);

typedef struct MemEntry{
	struct MemEntry *prev, *succ;
	int isfree;
	unsigned int size;
}MemEntry;

typedef struct MemEntry* MemPtr;

void *mymalloc(unsigned int size, char* filename, int line);

void myfree(void *p1, char* filename, int line);



#endif
