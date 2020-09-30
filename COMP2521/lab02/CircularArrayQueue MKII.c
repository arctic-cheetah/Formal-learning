// Implementation of the Queue ADT using a circular array

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"

#define DEFAULT_SIZE 16 // DO NOT change this line

// DO NOT modify this struct
struct queue {
	Item *items;
	int size;
	int capacity;
	int frontIndex;
};


/**
 * Creates a new empty queue
 */
Queue QueueNew(void) {
	Queue q = malloc(sizeof(*q));
	if (q == NULL) {
		fprintf(stderr, "couldn't allocate Queue");
		exit(EXIT_FAILURE);
	}
	
	q->items = malloc(DEFAULT_SIZE * sizeof(Item));
	if (q->items == NULL) {
		fprintf(stderr, "couldn't allocate Queue");
		exit(EXIT_FAILURE);
	}
	
	q->size = 0;
	q->capacity = DEFAULT_SIZE;
	q->frontIndex = 0;
	return q;
}
//A helper function that returns the length needed to get to the rear of the array
int ArrayRear (Queue q) {
	for (int i = 0; i < DEFAULT_SIZE; i++) {
	}
	return i;
}
//A utility function that returns the index of the end of the queue
int traverse (Queue q) {
	
	int i = 0;
	while (i < q->size) {
		i++;
	}
	return i % (q->capacity);
}


/**
 * Frees all resources associated with the given queue
 */
void QueueFree(Queue q) {
	free(q->items);
	free(q);
}

/**
 * Adds an item to the end of the queue
 */
void QueueEnqueue(Queue q, Item it) {
	//Cases:
	int LengthToLastElement = ArrayRear(q);
	int Alength = LengthToLastElement - q->frontIndex + 1; //A variable that stories the distance from the front to the end of the array 
// Remember arrays begin from 0 to n - 1
	//Consider if the array is full Y
	int endQueue = traverse(q);
	if (q->size == q->capacity) {
		//Double the size of the array
		q->items = realloc(q->items, DEFAULT_SIZE * sizeof(Item) );
		q->capacity *=2;
		q->items[size + 1] = it;
		q->size +=1;
	}
	
	//Consider if the array needs to be wrapped around use:
	//Need to somehow track the end of the queue
	//Check if size of queue needs to be wrapped around
	
	else if (Alength <= q->size) {
		q->items[endQueue] = it;
		q->size +=1;
		
	}
	else {
		
	}
	
	//
	// TODO
}

/**
 * Removes an item from the front of the queue and returns it
 * Assumes that the queue is not empty
 */
Item QueueDequeue(Queue q) {
	// TODO
	return 0;
}

/**
 * Gets the item at the front of the queue without removing it
 * Assumes that the queue is not empty
 */
Item QueueFront(Queue q) {
	assert(q->size > 0);
	
	return q->items[q->frontIndex];
}

/**
 * Gets the size of the given queue
 */
int QueueSize(Queue q) {
	return q->size;
}

/**
 * Returns true if the queue is empty, and false otherwise
 */
bool QueueIsEmpty(Queue q) {
	return q->size == 0;
}

/**
 * Prints the queue to the given file with items space-separated
 */
void QueueDump(Queue q, FILE *fp) {
	for (int i = q->frontIndex, j = 0; j < q->size; i = (i + 1) % q->capacity, j++) {
		fprintf(fp, "%d ", q->items[i]);
	}
	fprintf(fp, "\n");
}

