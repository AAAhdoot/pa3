#include "malloc_error.h"

int main(){
	char* first;
	first = (char*)malloc(2000*sizeof(char));
	free(first);
	free(first);
	return 0;
}
