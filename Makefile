all: site.o list.o avl.o cliente.o
	gcc -g site.o list.o avl.o cliente.o -o cliente -Wall -ansi -lm

site.o:
	gcc -g -c site.c -Wall -ansi -lm

list.o:
	gcc -g -c list.c -Wall -ansi -lm

avl.o:
	gcc -g -c avl.c -Wall -ansi -lm

cliente.o:
	gcc -g -c cliente.c -Wall -ansi -lm

clean:
	rm *.o cliente

run:
	./cliente	