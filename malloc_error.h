#ifndef MALLOC_ERROR_H
#define MALLOC_ERROR_H
#define BLOCKSIZE 10000
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
  size_t size;
  const char* file;
  unsigned int line;
}MemEntry;

typedef struct MemEntry* MemPtr;

void memleak_check();
void* my_malloc(size_t size, const char* file, unsigned int line);
void my_free(void *q, const char* file, unsigned int line);
void* my_calloc(size_t size, const char* file, unsigned int line);

#endif
