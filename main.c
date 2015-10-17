#include "malloc_error.c"

int main(int argc, char** argv){
  char *emily, *sweta;
  int* ptr1;
  int charlie;
  char* p;
  char* s;
  s = (char*)malloc(12*sizeof(char));
  emily = (char*)malloc(167*sizeof(char));
  sweta = (char*)malloc(10*sizeof(char));
  p = (char*)malloc(20*sizeof(char));
  free(emily);
  free(sweta);
  free(p);
  free(s);
  /*if(emily==0){
    printf("camille\n");
  }

   for(charlie =0;charlie<5;charlie++){
    (char*)malloc(18*sizeof(char));
  }

  sweta = (char*)malloc(19*sizeof(char));


  free(emily);
  free(sweta);


  (char*)malloc(217*sizeof(char));

  

  ptr1=NULL;
  free(ptr1);

  malloc(0);
  printf("bruh\n");
  malloc(8000);
  */
  return 0;
}
