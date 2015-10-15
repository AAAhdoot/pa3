#include "malloc_error.h"

void *my_malloc(unsigned int size, char* file, int line){
  static char bigblock[BLOCKSIZE];
  static int initialized=0;
  static MemPtr root;
  MemPtr p, post; 
  
  if(!initialized){
    root= (MemPtr)bigblock;
    root->prev = root->succ = 0;
    root->size = BLOCKSIZE - sizeof(MemEntry);
    root->isfree = 1;
    initialized = 1;
    //recognition pattern??
  }
  if(size>BLOCKSIZE){
    printf("<ERROR>%s:%d: Request larger than blocksize\n",file,line);
    return NULL;
  }
  if(size<=0){
    printf("<ERROR>%s:%d: Request too small (0 or negative number)\n",file,line);
    return NULL;
  }

  p=root;

  do{
    if(p->size<size) p=p->succ;
    else if(!p->isfree) p=p->succ;
    else if(p->size<=(size+sizeof(MemEntry))){
      p->isfree=0;
      return (char*)p + sizeof(MemEntry);
    }
    else{
      post = (MemPtr)((char*)p + sizeof(MemEntry))+size;
      post->prev = p;
      post->succ=p->succ;
      if(p->succ!=0) p->succ->prev = post;
      p->succ= post;
      post->size= p->size-sizeof(MemEntry)-size;
      post->isfree=1;
      p->size = size;
      p->isfree=0;
      /*not post, is beginning of memory*/
      return (char*)p+sizeof(MemEntry);
    }
  }while(p!=0);
  return 0;
}


void my_free(void *p1, char* file, int line){
  printf("4\n");
  if(p1==NULL){
    printf("<ERROR>%s:%d: Attempting to free a null pointer\n", file,line);
    return;
  }
  MemPtr ptr, pred, after;
  ptr = (MemPtr)p1-1;
  printf("5\n");
  printf("is it free? %d\n",ptr->isfree);
  if(ptr->isfree == 1){ //if it's already free
    printf("<ERROR>%s:%d: Already freed\n", file,line);
    return;
  }
  //2 cases for actually changing isfree of block: when pred and after are not free & when pred not free and after is free
  if((pred=ptr->prev)!=0 && pred->isfree){
    printf("1\n");
    pred->size+=sizeof(MemEntry)+pred->size;
    pred->succ= ptr->succ;
    if(ptr->succ!=0) ptr->succ->prev = pred;
  }
  else{
    printf("2\n");
    ptr->isfree=1;
    pred=ptr;
  }
  if((after=ptr->succ)!=0 && after->isfree){
    printf("3\n");
    pred->size+=sizeof(MemEntry)+after->size;
    pred->succ= after->succ;
    if(after->succ!=0) after->succ->prev=pred;		
  }
  return;
}


