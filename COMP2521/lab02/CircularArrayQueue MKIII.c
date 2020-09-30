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
	//Consider if queue is empty.
	if (q == NULL) {
		printf("The queue was NULL")
		return;
	}

	//Consider if the array is full Y
	int Qrear = traverse(q);
	if (q->size == q->capacity) {
		//Double the size of the array
		q->items = realloc(q->items, DEFAULT_SIZE * sizeof(Item) );
		q->capacity *=2;
		q->size +=1;
		q->items[q->size] = it;
	}
		//Consider if the array needs to be wrapped around use:
	//Need to somehow track the end of the queue
	//Check if size of queue needs to be wrapped around
	
	else {	
		q->items[Qrear] = it;
		q->size +=1;
	}
}

/**
 * Removes an item from the front of the queue and returns it
 * Assumes that the queue is not empty
 */
Item QueueDequeue(Queue q) {
	//Cases
	Item returnVal;
	int Qrear = traverse(q);
	//Removing the head from the rear but it is the only element
	if (q->size == 1 && Qrear == 0) {
		returnVal = q->item[q->frontIndex];
		q->size -=1;
		q->frontIndex = 0;
	}
	//Removing from head from the rear but it is NOT the only element
	else if (q->size == 1 && Qrear != 0) {} {
		returnVal = q->item[q->frontIndex];
		q->size -=1;
		q->frontIndex = 0;
	}
	//Removing the head, but it not in the rear
	
	
	return returnVal;
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

