all: prog

grafos.o: grafos.h grafos.c
	gcc -c grafos.c

ecra.o: ecra.h ecra.c
	gcc -c ecra.c

prog: grafos.o ecra.o
	gcc main.c grafos.o ecra.o -o prog
run: 
	./prog
	
clean: 
	rm *.o prog