#include "malloc_error.h"

int main(){
	char* first;
	char* second;
	char *third;
	first = (char*)malloc(1000*sizeof(char));
	second = (char*)malloc(10*sizeof(char));
	third = (char*)malloc(5*sizeof(char));
	return 0;
}
