//Implementation of a Queue
//Demonstration from COMP1511 Marc Chee
//15/04/2020

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

#define MAX_LENGTH 1023


struct queueInternals{
	//This implements a queue using linked lists
	//struct queueNode *head;
	//struct queueNode *tail;
	
	// This implements a queue using an array
	int *head;
	int *tail;
	int People[MAX_LENGTH];
	int size;
};

//Change to either linked list or array

struct queueNode{
	//struct queueNode *next;
	//int data;
};


//Implementation of a queue via an array
//Create a new queue
Queue queueCreate() {
	struct queueInternals *newQueue = malloc (sizeof( struct queueInternals));
	newQueue->head = NULL;
	newQueue->tail = NULL;
	newQueue->size = 0;
	return newQueue;
}

//Add an element to the queue
void queueAdd(Queue q, int item) {
	if (q->size != MAX_LENGTH) {
		q->People[q->size] = item;
		//Make the head point to the front of the queue
		if (q->head == NULL) {
			q->head = &q->People[q->size];
		}
		//Make the tail point to the end of the queue
		q->tail = &q->People[q->size];
		q->size++;
	}
	else {
		printf("Maximum queue size reached!\n");
	}
}

//Remove a person from the queue and return the element
int queueRemove(Queue q) {
	int frontQueue = *q->head;
	if (q->size != 0) {
		for (int length = 0; length < q->size; length++ ) {
			q->People[length] = q->People[length + 1];
		}
		q->size--;
		q->tail = &q->People[q->size];
		return frontQueue;
	}
	else {
		printf("There are no elements to remove from the queue!\n");
		exit(1);
	}
}

//Return the size of the queue
int queueSize(Queue q) {
	return q->size;
}

/*
//--------------------------------------------Below uses a linked list
//Create a new empty queue
//and return a queue pointer
Queue queueCreate(){
	struct queueInternals *newQueue = malloc (sizeof (struct queueInternals) );
	newQueue->head = NULL;
	newQueue->tail = NULL;
	newQueue->size = 0;
	return newQueue;
}

//Loop through the queue and free all the nodes
void queueFree(Queue q) {
	struct queueNode *curr = q->head;
	while (curr != NULL) {
		struct queueNode *remNode = curr;
		curr = curr->next;
		free (remNode);
	}
	free (q);
}


//Create and add an element to the queue
void queueAdd (Queue q, int data) {
	struct queueNode *newNode = malloc ( sizeof (struct queueNode) );
	newNode->next = NULL;
	newNode->data = data;	
	
	if (q->tail == NULL) {
		//There are no nodes in the queue
		q->head = newNode;
	}
	else {
		//there are nodes in the queue
		q->tail->next = newNode;
	}
	q->tail = newNode;
	q->size++;
}

//Remove the oldest node in the queue (the head);
//Return the stored value;
int queueRemove (Queue q) {
	if (q->head == NULL) {
		//empty list
		printf("Attempted to remove from an empty queue\n");
		exit(1);
	}
	//keep track of the node for removal
	int returnData = q->head->data;
	struct queueNode *remNode = q->head;
	//Move the head pointer to the second node or NULL
	q->head = q->head->next;
	
	//If there is only one element in the queue and is removed,
	//tail must be assigned a value.
	if (q->head == NULL) {
		q->tail = NULL;
	}
	
	free(remNode);
	q->size--;
	
	return returnData;
}

//Loop through the list until the end
//Count the number of elements inside
int queueSize(Queue q) {
	return q->size;
}

*/
































