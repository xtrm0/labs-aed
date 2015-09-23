CFLAGS= -g -Wall -pedantic

lab06: lab06.o tree.o queue.o
	gcc $(CFLAGS) -o lab06 tree.o lab06.o queue.o

lab06.o: lab06.c tree.h queue.h
	gcc $(CFLAGS) -c lab06.c

tree.o: tree.c tree.h queue.h
	gcc $(CFLAGS) -c tree.c
	
queue.o: queue.c queue.h
	gcc $(CFLAGS) -c queue.c

clean:
	rm -f *.o *.~ lab06 *.gch
