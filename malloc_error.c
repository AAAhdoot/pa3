#define BLOCKSIZE 1<<20
#define malloc(x) mymalloc(x,__FILE__,__LINE__)
#define free(x) myfree(x,__FILE__,__LINE__)
static char big-block[BLOCKSIZE];
static int initialized;
static MemPtr root;
initialized=0;



typedef struct MemEntry{
	struct MemEntry *prev, *succ;
	int isfree;
	unsigned int size;
}MemEntry;

typedef struct MemEntry* MemPtr;

void *mymalloc(unsigned int size){
	MemPtr *p, *post; 

	if(!initialized){
		root= (MemPtr)big-block;
		root->prev = root->succ =0;
		root->size = BLOCKSIZE - sizeof(mementry);
		root->isfree = 1;
		initialized = 1;
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
		return (char*)p+size(MemEntry);
		}while(p!=0);
		return 0;
	}
}

void myfree(void *p1){
	MemPtr ptr, pred,succ;
	ptr = (MemPtr)p1-1;
	if((pred=ptr->prev)!=0 && pred->isfree){
		pred->size+=sizeof(MemEntry)+pred->size;
		pred->succ= ptr->succ;
		if(ptr->succ!=0) ptr->succ->prev = pred;
		else{
			ptr->isfree=1;
			pred=ptr;
		}
		if((succ->ptr->succ)!=0 && succ->isfree){
			pred->size+=sizeof(MemEntry)+succ->size;
			pred->succ= succ->succ;
			if(succ->succ!=0) succ->succ=pred;
		}
	}
}




}