CC = gcc
CFLAGS = -Wall -O3 -Wno-unused-result -c
LNFLAGS = -O3 -Ofast -Wall
LN = gcc

all: lab5a/aula5a aula5b

aula5b: aula5b.o LinkedList.o
	$(LN) $(LNFLAGS) -o aula5b aula5b.c LinkedList.o

lab5a/aula5a: lab5a/main.c
	$(CC) $(LNFLAGS) -o lab5a/aula5a lab5a/main.c

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@
