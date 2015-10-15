#include "malloc_error.c"

int main(){
  char *emily;
  int* ptr1;
  
  emily = (char*)malloc(5*sizeof(char));
  free(emily);
  free(emily);

  ptr1=NULL;
  free(ptr1);

  malloc(0);

  malloc(8000);

  return 0;
}
