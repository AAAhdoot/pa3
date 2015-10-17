#include "malloc_error.h"

 static char bigblock[BLOCKSIZE];

void  memleak_check(){
  MemPtr p, root, mid;
  int sm_leaks =0;
  int lg_leaks=0;
  
  root = (MemPtr)bigblock;
  mid = (MemPtr)(bigblock+(BLOCKSIZE/2));
 
  p = root;  
  printf("\e[1mMemory Leak Summary For Small Blocks:\n\e[0m");
  while(p!=0){
    if(p->isfree==0){
      sm_leaks++;
      printf("Memory Leak at: %s: %d\n", p->file, p->line );
    }
    p=p->succ;
  }
  if(sm_leaks==0)printf( "No leaks for Small Blocks\n");
  p = mid;
  printf("\e[1mMemory Leak Summary For Large  Blocks:\n\e[0m");
  while(p!=0){
    if(p->isfree==0){
      lg_leaks++;
      printf("Memory Leak at: %s: %d\n", p->file, p->line );
    }
    p=p->succ;
  }
  if(lg_leaks==0)printf("No leaks for Large Blocks\n");
  
  return;
}


void *my_malloc(unsigned int size, const char* file, unsigned int line){
  static int initialized=0;
  static MemPtr root,mid;
  MemPtr p, post; 

  if(size+sizeof(MemEntry)>BLOCKSIZE/2){
    printf("<ERROR>%s:%d: Request larger than blocksize\n",file,line);
    return NULL;
  }
  if(size<=0){
    printf("<ERROR>%s:%d: Request too small (0 or negative number)\n",file,line);
    return NULL;
  }
  
  if(!initialized){
    root= (MemPtr)bigblock;
    root->prev = root->succ = 0;
    root->size = BLOCKSIZE/2 - sizeof(MemEntry);
    root->isfree = 1;
    initialized = 1;
    root->pattern = PATTERNUM;
    root->file = file;
    root->line = line;
    mid = (MemPtr)(bigblock+(BLOCKSIZE/2));
    mid->prev =  mid->succ = 0;
    mid->isfree = 1;
    mid->pattern = PATTERNUM;
    mid->size = BLOCKSIZE/2 - sizeof(MemEntry);
    mid->file = file;
    mid->line = line;

    atexit(memleak_check);
  }

  if(size>(BLOCKSIZE/50)-sizeof(MemEntry)){
    p=mid;
  }
  else{
    p=root;
  }
  do{
    if(p->size<size){ 
      p=p->succ;
    }
    else if(!p->isfree) p=p->succ;
    else if(p->size<=(size+sizeof(MemEntry))){
      p->isfree=0;
      p->pattern = PATTERNUM;
      p->file = file;
      p->line = line;
      return (char*)p + sizeof(MemEntry);
    }
    else{
      post = (MemPtr)((char*)p + sizeof(MemEntry)+size);
      post->prev = p;
      post->succ=p->succ;
      if(p->succ!=0) p->succ->prev = post;
      p->succ= post;
      post->size= p->size-sizeof(MemEntry)-size;
      post->isfree=1;
      p->size = size;
      p->isfree=0;
      p->pattern = PATTERNUM;
      p->file = file;
      p->line = line;
      /*not post, is beginning of memory*/
      return (char*)p+sizeof(MemEntry);
    }
  }while(p!=0 && p!=mid);
  printf("<ERROR>%s:%d: No room\n", file,line);
  return 0;
}


void my_free(void *q, const char* file, unsigned int line){
  if(!q){
    printf("<ERROR>%s:%d: Attempting to free a null pointer\n", file,line);
    return;
  }

  MemPtr ptr, pred, after;
  ptr = (MemPtr)q-1;
  if(ptr->pattern!=PATTERNUM){
    printf("<ERROR>%s:%d: Invalid free\n", file,line);
    return;
  }
  if(ptr->isfree == 1){ //if it's already free
    printf("<ERROR>%s:%d: Already freed\n", file,line);
    return;
  }
  //2 cases for actually changing isfree of block: when pred and after are not free & when pred not free and after is free
  if((pred=ptr->prev)!=0 && pred->isfree){
    pred->size+=sizeof(MemEntry)+ptr->size;
    pred->succ= ptr->succ;
    if(ptr->succ!=0) ptr->succ->prev = pred;
  }
  else{
    ptr->isfree=1;
    pred=ptr;
  }
  if((after=ptr->succ)!=0 && after->isfree){
    pred->size+=sizeof(MemEntry)+after->size;
    pred->succ= after->succ;
    if(after->succ!=0) after->succ->prev=pred;		
  }
  return;
}

void * my_calloc(unsigned int size, const char* file, unsigned int line){
  void * result = my_malloc(size,file,line);
  if(!result){
    return 0;
  }
  memset(result,0,size);
  return result;
}


