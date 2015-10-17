#ifndef MALLOC_ERROR_H
#define MALLOC_ERROR_H
#define BLOCKSIZE 500
#define PATTERNUM 78245

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define malloc(x) my_malloc( x, __FILE__, __LINE__)
#define free(x) my_free( x, __FILE__, __LINE__)
#define calloc(x) my_calloc( x, __FILE__, __LINE__)

typedef struct MemEntry{
  struct MemEntry *prev, *succ;
  int isfree, pattern;
  unsigned int size;
}MemEntry;

typedef struct MemEntry* MemPtr;


void* my_malloc(unsigned int size, const char* file, unsigned int line);
void my_free(void *q, const char* file, unsigned int line);
void* my_calloc(unsigned int size, const char* file, unsigned int line);

#endif
