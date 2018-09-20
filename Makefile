all: site.o list.o cliente.o
	gcc -g site.o list.o cliente.o -o cliente -Wall -ansi

site.o:
	gcc -g -c site.c

list.o:
	gcc -g -c list.c

cliente.o:
	gcc -g -c cliente.c

clean:
	rm *.o cliente