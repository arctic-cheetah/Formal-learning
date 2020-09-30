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

//////////////////////////////////////////////////////////////////////
//// Helper functions:
void shift_to_right(Queue q, int end_of_array);
int rearQueue (Queue q);
//A function that prints the queue
void printQueue (Queue q) {
	int i = q->frontIndex;
	int rearQ = rearQueue(q);
	while (i != rearQ) {
		printf("%d, ", q->items[i]);
		i = (i + 1) % q->capacity;
	}
	printf("\n");
}

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

//////////////////////////////////////////////////////////////////////////
//A utility function that returns the index of the end of the queue
//
int rearQueue (Queue q) {
	return (q->size + q->frontIndex) % q->capacity;
}
//A utility function that shifts the all the elements that have passed the front of the array to the end of the extended array.
// O(n)
void shift_to_right(Queue q, int end_of_array) {
	int end_of_extendedArray = 2*q->capacity - 1;
	while (end_of_array != (q->frontIndex - 1)) {
		q->items[end_of_extendedArray] = q->items[end_of_array];
		end_of_array -=1;
	}
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
	//printQueue(q);
	//Cases:
	//Consider if queue is empty. Add a new element
	if (q->size == 0) {//O(1)
		q->size +=1;
		q->items[q->frontIndex] = it;
		return;
	}
	//Consider if the queue is full.
	int rearIndex = rearQueue(q);//O(1)
	if (q->size == q->capacity - 1) {
		//Double the size of the array
		q->items = realloc(q->items, 2 * q->capacity * sizeof(Item) ); //O(n);
		//Consider Cases for wrapping
		//frontIndex is somewhere in the middle or end
		if ( (rearIndex + 1 == q->frontIndex) && (q->frontIndex != 0) ) {
			int end_of_array = (q->capacity - 1);
			//Shift all values from frontIndex onwards to the right 
			//until the end of the list is reached
			shift_to_right(q, end_of_array); //O(n)
		}
		q->capacity *=2;
		q->items[rearIndex] = it;
	}
	else {	
		q->items[rearIndex] = it;
	}
	q->size +=1;
	//printQueue(q);
}

/**
 * Removes an item from the front of the queue and returns it
 * Assumes that the queue is not empty
 */
Item QueueDequeue(Queue q) {
	//Cases
	
	Item returnVal;
	
	//Removing the head from the rear
	if (q->frontIndex == q->capacity - 1) {
		returnVal = q->items[q->frontIndex];
		q->size -=1;
		q->frontIndex = 0;
	}
	//Removing the head, but it not in the rear
	else {
		returnVal = q->items[q->frontIndex];
		q->frontIndex +=1;
		q->size -=1;
	}
	//printQueue(q);
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

