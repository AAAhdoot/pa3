#include "malloc_error.h"

int main(){
  char* first;
  char* second;
  char* third;
  char* fourth;
  first = (char*)malloc(250*sizeof(char));
  second = (char*)malloc(100*sizeof(char));
  third = (char*)malloc(10*sizeof(char));
  fourth = (char*)malloc(1000*sizeof(char));
  free(first);
  free(second);
  free(third);
  return 0;
}
