all: site.o list.o cliente.o
	gcc -g site.o list.o cliente.o -o cliente -Wall -ansi

site.o:
	gcc -g -c site.c -Wall -ansi

list.o:
	gcc -g -c list.c -Wall -ansi

cliente.o:
	gcc -g -c cliente.c -Wall -ansi

clean:
	rm *.o cliente

run:
	./cliente	