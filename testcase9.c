#include "malloc_error.h"

int main(){
  char* first;
  char* second;
  char *third;
  int x;
  first = (char*)malloc(2452*sizeof(char));
  for(x=0;x<24;x++){
    (char*)malloc(152*sizeof(char));
  }
  second = (char*)malloc(2452*sizeof(char));
  free(first);
  free(second);
  third = (char*)malloc(3000*sizeof(char));
  free(third);
  return 0;
}
