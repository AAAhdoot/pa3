#include "malloc_error.h"

int main(){
	char x;
	free(&x);
	return 0;
}
