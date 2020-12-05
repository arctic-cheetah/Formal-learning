# COMP2521, Question: containsSequence .. 

CC=gcc
CFLAGS=-Wall -Werror

all: testContainsSequence

testContainsSequence : list.o  containsSequence.o  testContainsSequence.o 
	$(CC) -o testContainsSequence  testContainsSequence.c list.o  containsSequence.o 


testContainsSequence.o : testContainsSequence.c  list.h 
containsSequence.o : containsSequence.c  list.h 
list.o : list.c  list.h 

clean:
	rm -f testContainsSequence list.o containsSequence.o testContainsSequence.o core



