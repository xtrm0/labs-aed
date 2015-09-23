CC=gcc
CFLAGS=-g -c -Wall -ansi -pedantic

pal: pal.o hash.o
	$(CC) -o hashPalavra -lm pal.o hash.o

pal.o: pal.c pal.h
	$(CC) $(CFLAGS) pal.c


hash.o: hash.c pal.h
	$(CC) $(CFLAGS) hash.c

clean::
	rm -f *.o core a.out hashPalavra *~
