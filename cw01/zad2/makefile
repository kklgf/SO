cc = gcc -Wall -std=c11 -g

all: main_static

static_lib: libdiff.c libdiff.h
	$(cc) -c libdiff.c -o libdiff.o
	ar rcs libdiff.a libdiff.o

shared_lib: libdiff.c libdiff.h
	$(cc) -c -fPIC libdiff.c -o libdiff.o
	$(cc) -shared -fPIC -o libdiff.so libdiff.o

main_static: main.c static_lib
	$(cc) -c main.c -o main.o
	$(cc) main.o libdiff.a -o main.out

main_shared: main.c shared_lib
	$(cc) -c main.c -o main.o
	$(cc) main.c -L. -o main.out -ldiff -Wl,-rpath=.

clean:
	rm *.out *.so *.o *.a

test:
	echo > raport.txt
	echo "Few pairs (5)" >> raport.txt
	./main.out create_table 5 compare_pairs \
 		a.txt:b.txt b.txt:a.txt a.txt:a.txt b.txt:b.txt a.txt:b.txt remove_block 0 >> raport.txt

	echo >> raport.txt
	echo >> raport.txt
	echo "More pairs (10)" >> raport.txt
	./main.out create_table 10 compare_pairs \
		a.txt:b.txt b.txt:a.txt a.txt:a.txt b.txt:b.txt a.txt:b.txt\
		a.txt:b.txt b.txt:a.txt a.txt:a.txt b.txt:b.txt a.txt:b.txt\
		remove_block 0 >> raport.txt

	echo >> raport.txt
	echo >> raport.txt
	echo "Many pairs (100)" >> raport.txt
	./main.out create_table 100 compare_pairs \
		a.txt:b.txt b.txt:a.txt a.txt:a.txt b.txt:b.txt a.txt:b.txt\
		a.txt:b.txt b.txt:a.txt a.txt:a.txt b.txt:b.txt a.txt:b.txt\
		a.txt:b.txt b.txt:a.txt a.txt:a.txt b.txt:b.txt a.txt:b.txt\
		a.txt:b.txt b.txt:a.txt a.txt:a.txt b.txt:b.txt a.txt:b.txt\
		a.txt:b.txt b.txt:a.txt a.txt:a.txt b.txt:b.txt a.txt:b.txt\
		a.txt:b.txt b.txt:a.txt a.txt:a.txt b.txt:b.txt a.txt:b.txt\
		a.txt:b.txt b.txt:a.txt a.txt:a.txt b.txt:b.txt a.txt:b.txt\
		a.txt:b.txt b.txt:a.txt a.txt:a.txt b.txt:b.txt a.txt:b.txt\
		a.txt:b.txt b.txt:a.txt a.txt:a.txt b.txt:b.txt a.txt:b.txt\
		a.txt:b.txt b.txt:a.txt a.txt:a.txt b.txt:b.txt a.txt:b.txt\
		a.txt:b.txt b.txt:a.txt a.txt:a.txt b.txt:b.txt a.txt:b.txt\
		a.txt:b.txt b.txt:a.txt a.txt:a.txt b.txt:b.txt a.txt:b.txt\
		a.txt:b.txt b.txt:a.txt a.txt:a.txt b.txt:b.txt a.txt:b.txt\
		a.txt:b.txt b.txt:a.txt a.txt:a.txt b.txt:b.txt a.txt:b.txt\
		a.txt:b.txt b.txt:a.txt a.txt:a.txt b.txt:b.txt a.txt:b.txt\
		a.txt:b.txt b.txt:a.txt a.txt:a.txt b.txt:b.txt a.txt:b.txt\
		a.txt:b.txt b.txt:a.txt a.txt:a.txt b.txt:b.txt a.txt:b.txt\
		a.txt:b.txt b.txt:a.txt a.txt:a.txt b.txt:b.txt a.txt:b.txt\
		a.txt:b.txt b.txt:a.txt a.txt:a.txt b.txt:b.txt a.txt:b.txt\
		a.txt:b.txt b.txt:a.txt a.txt:a.txt b.txt:b.txt a.txt:b.txt\
		remove_block 0 >> raport.txt

	echo >> raport.txt
	echo >> raport.txt
	echo "Identical" >> raport.txt
	./main.out create_table 10 compare_pairs \
		a.txt:a.txt a.txt:a.txt a.txt:a.txt a.txt:a.txt a.txt:a.txt\
		a.txt:a.txt a.txt:a.txt a.txt:a.txt a.txt:a.txt a.txt:a.txt\
		remove_block 0 >> raport.txt

	echo >> raport.txt
	echo >> raport.txt
	echo "Similar" >> raport.txt
	./main.out create_table 10 compare_pairs \
		a.txt:b.txt a.txt:b.txt a.txt:b.txt a.txt:b.txt a.txt:b.txt\
		a.txt:b.txt a.txt:b.txt a.txt:b.txt a.txt:b.txt a.txt:b.txt\
		remove_block 0 >> raport.txt

	echo >> raport.txt
	echo >> raport.txt
	echo "Different" >> raport.txt
	./main.out create_table 10 compare_pairs \
		libdiff.c:main.c libdiff.c:main.c libdiff.c:main.c libdiff.c:main.c libdiff.c:main.c\
		libdiff.c:main.c libdiff.c:main.c libdiff.c:main.c libdiff.c:main.c libdiff.c:main.c\
		remove_block 0 >> raport.txt
