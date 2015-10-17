CC = gcc
CFLAGS  = -Wall -g
COMPILE = $(CC) $(CFLAGS)

main: main.o malloc_error.o
	$(COMPILE) -o main main.o malloc_error.o

main.o: main.c malloc_error.c malloc_error.h
	$(COMPILE) -c main.c malloc_error.c

malloc_error.o: malloc_error.c malloc_error.h
	$(COMPILE) -c malloc_error.c

clean:
	rm -rf *.o sl main.o malloc_error.o

