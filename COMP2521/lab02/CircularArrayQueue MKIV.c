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
//Via brute force... Possibly O(n)
int rearQueue (Queue q) {
	int i = 0;
	int Konstant = mod - (q->frontIndex);
	while ( !(q->size == (i + Konstant) % q->capacity) ) {
		i++;
	}
	return i;
}
//A utility function that shifts the all the elements that have passed the front of the array to the end of the extended array.
void shift_to_right(Queue q, int end_of_array) {
	int end_of_extendedArray = ArrayRear(q);
	while (end_of_array != (q->frontIndex - 1)) {
		q->items[end_of_extendedArray] = q->items[end_of_array];
		end_of_array -=1;
	}
}

//A utility function that returns the length needed to get to the rear of the array
int ArrayRear (Queue q) {
	for (int i = 0; i < q->capacity; i++) {
	}
	return i;
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
	//Consider if queue is empty. --Guaranteed not to be empty

	//Consider if the queue is full.
	int rearIndex = rearQueue(q);
	int end_of_array = ArrayRear(q);
	
	if (q->size == q->capacity) {
		//Double the size of the array
		q->items = realloc(q->items, 2 * q->capacity * sizeof(Item) );
		q->capacity *=2;
		/*
		//Consider if queue is full but frontIndex is in the end and rear
		if (frontIndex == q->capacity - 1) {
			q->items[q->size] = it;
			q->size +=1;
		}
		//Consider if queue is full but frontIndex is in the beginning
		else if (frontIndex == ) {
			
		}
		//Consider if queue is full but frontIndex is somewhere in the middle.
		//But not the end nor the beginning
		else {
			
		}
		*/
			//Consider if (rear is or difference is one index away)...
		//frontIndex is in the front and rearIndex is in the back
		if (rearIndex + 1 == q->frontIndex) && frontIndex == 0) {
			q->items[rearIndex + 1] = it;
		}
		//frontIndex is somewhere in the middle or end
		else if (rearIndex + 1 == q->frontIndex) && frontIndex != 0) {
			//Shift all values from frontIndex onwards to the right 
			//until the end of the list is reached
			shift_to_right(q, end_of_array);
			q->items[rearIndex + 1] = it;
		}
	}
	
		//Consider if the array needs to be wrapped around use:
	//Need to somehow track the end of the queue
	//Check if size of queue needs to be wrapped around
	
	else {	
		q->items[rearIndex + 1] = it;
	}
	q->size +=1;
}

/**
 * Removes an item from the front of the queue and returns it
 * Assumes that the queue is not empty
 */
Item QueueDequeue(Queue q) {
	//Cases
	Item returnVal;
	int rearIndex = rearQueue(q);
	//Removing the head from the rear
	if (q->size == 1 && rearIndex == 0) {
		returnVal = q->items[q->frontIndex];
		q->size -=1;
		q->frontIndex = 0;
	}
	//Removing the head, but it not in the rear
	else {
		returnVal = q->items[q->frontIndex];
		q->size -=1;
		q->frontIndex +=1;
	}
	
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

