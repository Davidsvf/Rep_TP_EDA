
all: prog

funcoes.o: funcoes.h funcoes.c
	gcc -c funcoes.c

prog: funcoes.o funcoes.c
	gcc main.c funcoes.o -o prog

run: 
	./prog
	
clean: 
	rm *.o prog