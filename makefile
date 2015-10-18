objects = testcase1.o testcase2.o testcase3.o testcase5.o testcase6.o testcase7.o  testcase8.o  testcase9.o testcase10.o
executables =  testcase1 testcase2 testcase3 testcase4 testcase5 testcase6 testcase7 testcase8 testcase9

all: testcase1 testcase2 testcase3 testcase4 testcase5 testcase6 testcase7 testcase8 testcase9

testcase1: malloc_error testcase1.c
	gcc -g -o testcase1 malloc_error.o testcase1.c
testcase2: malloc_error testcase2.c
	gcc -g -o testcase2 malloc_error.o testcase2.c
testcase3: malloc_error testcase3.c
	gcc -g -o testcase3 malloc_error.o testcase3.c
testcase4: malloc_error testcase4.c
	gcc -g -o testcase4 malloc_error.o testcase4.c
testcase5: malloc_error testcase5.c
	gcc -g -o testcase5 malloc_error.o testcase5.c
testcase6: malloc_error testcase6.c
	gcc -g -o testcase6 malloc_error.o testcase6.c
testcase7: malloc_error testcase7.c
	gcc -g -o testcase7 malloc_error.o testcase7.c
testcase8: malloc_error testcase8.c
	gcc -g -o testcase8 malloc_error.o testcase8.c
testcase9: malloc_error testcase9.c
	gcc -g -o testcase9 malloc_error.o testcase9.c
malloc_error:
	gcc -g -c malloc_error.c malloc_error.h

clean:
	rm -rf *.o $(objects) *.a $(executables)

