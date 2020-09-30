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
int ArrayRear (Queue q);
void printQueue (Queue q) {
	int i = q->frontIndex;
	int rearQ = rearQueue(q);
	while (i != rearQ + 1) {
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
//A utility function that returns the index of the end of the queue
//Via brute force... Possibly O(n)
int rearQueue (Queue q) {
	int i = 0;
	//Case where the queue is full
	if (q->size == q->capacity) {
		return q->size - 1;
	}
	int Konstant = q->capacity - (q->frontIndex);
	while ( !(q->size == (i + Konstant) % q->capacity) ) {
		i++;
	}
	//printf("Konstant: %d\n", i - 1);
	return i - 1;
}
//A utility function that shifts the all the elements that have passed the front of the array to the end of the extended array.
//O(n)
void shift_to_right(Queue q, int end_of_array) {
	int end_of_extendedArray = ArrayRear(q);
	while (end_of_array != (q->frontIndex - 1)) {
		q->items[end_of_extendedArray] = q->items[end_of_array];
		end_of_array -=1;
	}
}

//A utility function that returns the length needed to get to the rear of the array
//O(n)
int ArrayRear (Queue q) {
	int i = 0;
	while (i < q->capacity) {
		i++;
	}
	return i - 1;
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
	//printQueue(q);
	//Consider if the queue is full.
	int rearIndex = rearQueue(q);//O(n)
	if (q->size == q->capacity) {
		int end_of_array = ArrayRear(q);//O(n)
		//Double the size of the array
		q->items = realloc(q->items, 2 * q->capacity * sizeof(Item) ); //O(n);
		q->capacity *=2;
		
		//Consider Cases for wrapping
		//frontIndex is somewhere in the middle or end
		if ( (rearIndex + 1 == q->frontIndex) && (q->frontIndex != 0) ) {
			//Shift all values from frontIndex onwards to the right 
			//until the end of the list is reached
			shift_to_right(q, end_of_array); //O(n)
			q->items[rearIndex + 1] = it;
		}
		q->items[rearIndex + 1] = it;
	}
	else {	
		q->items[rearIndex + 1] = it;
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
	
	Item returnVal;//O(1)
	int end_of_array = ArrayRear(q);//O(n)
	
	//Removing the head from the rear
	//O(1)
	if (q->frontIndex == end_of_array) {
		returnVal = q->items[q->frontIndex];
		q->size -=1;
		q->frontIndex = 0;
	}
	//Removing the head, but it not in the rear
	//O(1)
	else {
		returnVal = q->items[q->frontIndex];
		q->size -=1;
		q->frontIndex +=1;
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
