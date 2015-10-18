#include "malloc_error.h"

int main(){
	char* first;
	char* second;
	first = (char*)malloc(2000*sizeof(char));
	second = (char*)malloc(100*sizeof(char));
	free(first+10);
	free(second);
	return 0;
}
