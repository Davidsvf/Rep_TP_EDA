
all: prog

funcoes.o: funcoes.h funcoes.c
	gcc -c funcoes.c

matriz.o: matriz.h matriz.c
	gcc -c matriz.c

prog: funcoes.o matriz.o
	gcc main.c funcoes.o matriz.o -o prog

run: 
	./prog
	
clean: 
	rm *.o prog