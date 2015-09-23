CC=gcc
CFLAGS=-g -c -Wall -ansi -pedantic
LFLAGS= -lm -o hashPalavra

pal: pal.o hash.o
	$(CC) $(LFLAGS) pal.o hash.o

pal.o: pal.c pal.h
	$(CC) $(CFLAGS) pal.c


hash.o: hash.c pal.h
	$(CC) $(CFLAGS) hash.c

clean::
	rm -f *.o core a.out hashPalavra *~
