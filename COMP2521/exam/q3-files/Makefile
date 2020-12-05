# COMP2521 Question: rankPopularity

CC = gcc
CFLAGS = -Wall -Werror

all: testRankPopularity

testRankPopularity: Graph.o rankPopularity.o testRankPopularity.c
	$(CC) $(CFLAGS) -o testRankPopularity testRankPopularity.c Graph.o rankPopularity.o 

rankPopularity.o: Graph.h rankPopularity.c
	$(CC) $(CFLAGS) -c rankPopularity.c

Graph.o: Graph.h Graph.c
	$(CC) $(CFLAGS) -c Graph.c
	
clean:
	rm -f testRankPopularity rankPopularity.o Graph.o testRankPopularity.o core

