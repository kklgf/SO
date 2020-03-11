cc = gcc -Wall -std=c11 -g

all: static_lib

static_lib: 
	$(cc) -c libdiff.c -o libdiff.o
	ar rcs libdiff.a libdiff.o

shared_lib:
	$(cc) -c -fPIC libdiff.c -o libdiff.o
	$(cc) -shared -fPIC -o libdiff.so libdiff.o

clean:
	rm *.so *.o *.a
