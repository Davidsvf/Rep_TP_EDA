all: prog

grafos.o: grafos.h grafos.c
	gcc -c grafos.c

ecra.o: ecra.h ecra.c
	gcc -c ecra.c

libgrafos.a: grafos.o
	ar rcs libgrafos.a grafos.o

libecra.a: ecra.o
	ar rcs libecra.a ecra.o

prog: main.c libgrafos.a libecra.a
	gcc main.c -L. -lgrafos -lecra -o prog

run: 
	./prog
	
clean: 
	rm -f *.o *.a prog