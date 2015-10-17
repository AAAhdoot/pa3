#include "malloc_error.c"

int main(int argc, char** argv){
  char *emily, *sweta;
  int* ptr1;


  emily = (char*)malloc(6368*sizeof(char));

  if(emily==0){
    printf("camille\n");
  }

  sweta = (char*)malloc(12*sizeof(char));
  if(sweta==0){
    printf("kirstin\n");
  }
 /* free(emily);

  ptr1=NULL;
  free(ptr1);

  malloc(0);

  malloc(8000);
*/
  return 0;
}
