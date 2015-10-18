#include "malloc_error.h"

int main(){
  char* first;
  char* second;
  first = (char*)malloc(0*sizeof(char));
  second = (char*)malloc(-24*sizeof(char));
  free(first);
  free(second);
  return 0;
}
