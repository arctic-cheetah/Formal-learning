# COMP2521, Question: nodesNotBalanced
# Written by Ashesh Mahidadia, May 2019

CC=gcc
CFLAGS=-Wall -Werror  

all: testNodesNotBalanced

testNodesNotBalanced : BSTree.o nodesNotBalanced.o testNodesNotBalanced.o
	$(CC) -o testNodesNotBalanced  BSTree.o  nodesNotBalanced.o testNodesNotBalanced.o

nodesNotBalanced.o : nodesNotBalanced.c  BSTree.h 
BSTree.o : BSTree.c  BSTree.h 
testNodesNotBalanced.o : testNodesNotBalanced.c  BSTree.h 

clean:
	rm -f testNodesNotBalanced nodesNotBalanced.o testNodesNotBalanced.o BSTree.o core
