#include "malloc_error.h"

int main(){
  char* first;
  char* second;
  char* third;
  char* fourth;
  first = (char*)malloc(10000*sizeof(char));
  second = (char*)malloc(4952*sizeof(char));
  third = (char*)malloc(20*sizeof(char));
  printf("%ld\n",sizeof(MemEntry));
  fourth = (char*)malloc(4952*sizeof(char));
  free(first);
  free(second);
  free(third);
  return 0;
}
