#
#  File name: makefile
#
#  Author: 2013 Fall Semester AED Team
#
#  Release date: 2013/10/04
#
#  Description: Makefile for the program lab03b
#
#  Usage:
#     1) To generate the executable file for the program lab03,
#       run
#         $ make
#
#     2) To clean all object files and the executable file of
#        lab03b, run
#         $ make clean
#

#  Compiler
CC = gcc

#  Compiler Flags
CFLAGS = -g -Wall -ansi -pedantic

#  Sources
SOURCES = LinkedList.c Entry.c lab03b.c

#  Objects
OBJECTS = LinkedList.o Entry.o lab03b.o

lab03b: $(OBJECTS)
	gcc -o $@ $(OBJECTS)

Entry.o: Entry.h

LinkedList.o: LinkedList.h defs.h


clean::
	rm -f *.o core a.out lab03b *~

depend::
	makedepend $(SOURCES)
# DO NOT DELETE
