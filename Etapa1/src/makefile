
all: prog

funcoes.o: funcoes.h funcoes.c
	gcc -c funcoes.c

matriz.o: matriz.h matriz.c
	gcc -c matriz.c

libfuncoes.a: funcoes.o
	ar rcs libfuncoes.a funcoes.o

libmatriz.a: matriz.o
	ar rcs libmatriz.a matriz.o

prog: main.c libfuncoes.a libmatriz.a
	gcc main.c -L. -lfuncoes -lmatriz -o prog

run: 
	./prog
	
clean: 
	rm -f *.o *.a prog