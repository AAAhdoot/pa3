#include "malloc_error.h"

void *my_malloc(unsigned int size, const char* file, unsigned int line){
  static char bigblock[BLOCKSIZE];
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
    mid = (MemPtr)(bigblock+(BLOCKSIZE/2));
    mid->prev =  mid->succ = 0;
    mid->isfree = 1;
    mid->pattern = PATTERNUM;
    mid->size = BLOCKSIZE/2 - sizeof(MemEntry);
  }

  if(size>(BLOCKSIZE/10)-sizeof(MemEntry)){
    printf("BIG\n");
    p=mid;
  }
  else{
    printf("SMALL\n");
    p=root;
  }
  do{
    //    printf("p->size is %d\n",p->size);
    // printf("size is %d\n",size);
    if(p->size<size){ 
      p=p->succ;
    }
    else if(!p->isfree) p=p->succ;
    else if(p->size<=(size+sizeof(MemEntry))){
      p->isfree=0;
      p->pattern = PATTERNUM;
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
      /*not post, is beginning of memory*/
      printf("we made it! meha\n");
      return (char*)p+sizeof(MemEntry);
    }
  }while(p!=0 && p!=mid);
  printf("<ERROR>%s:%d: No room\n", file,line);
  return 0;
}


void my_free(void *q, const char* file, unsigned int line){
  printf("4\n");
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
  printf("5\n");
  printf("is it free? %d\n",ptr->isfree);
  if(ptr->isfree == 1){ //if it's already free
    printf("<ERROR>%s:%d: Already freed\n", file,line);
    return;
  }
  //2 cases for actually changing isfree of block: when pred and after are not free & when pred not free and after is free
  if((pred=ptr->prev)!=0 && pred->isfree){
    printf("1\n");
    pred->size+=sizeof(MemEntry)+ptr->size;
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

void * my_calloc(unsigned int size, const char* file, unsigned int line){
  void * result = my_malloc(size,file,line);
  if(!result){
    return 0;
  }
  memset(result,0,size);
  return result;
}


