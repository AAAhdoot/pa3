#include "malloc_error.h"

int main(){
  char* first;
  char* second;
  char *third;
  first = (char*)malloc(2000*sizeof(char));
  second = (char*)malloc(100*sizeof(char));
  third = (char*)malloc(50*sizeof(char));
  free(first);
  free(second);
  free(third);
  return 0;
}
