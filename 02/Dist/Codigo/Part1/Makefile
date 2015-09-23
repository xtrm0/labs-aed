CFLAGS= -g -Wall -pedantic

words: main3a.o word.o
	gcc $(CFLAGS) -o words word.o main3a.o

main3a.o: main3a.c word.h
	gcc $(CFLAGS) -c main3a.c

word.o: word.c word.h
	gcc $(CFLAGS) -c word.c

clean:
	rm -f *.o *.~ words *.gch
