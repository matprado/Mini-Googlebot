all: avl.o site.o list.o cliente.o
	gcc -g avl.o site.o list.o cliente.o -o cliente -Wall -ansi -lm

avl.o:
	gcc -g -c avl.c -Wall -ansi -lm

site.o:
	gcc -g -c site.c -Wall -ansi -lm

list.o:
	gcc -g -c list.c -Wall -ansi -lm

cliente.o:
	gcc -g -c cliente.c -Wall -ansi -lm

clean:
	rm *.o cliente

run:
	./cliente	