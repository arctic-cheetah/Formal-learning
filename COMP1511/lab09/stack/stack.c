//Implementation of a stack
//Lecture demo by Marc Chee
//April 2020
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK 100


struct stackInternals {
	//Implementation of a stack via doubly linked lists
	struct stackNode *tail;
	struct stackNode *head;
	int size;
	//Implementation of a stack via an array
	int stack[MAX_STACK];
	int top;
};

//Linked lists
struct stackNode {
	int data;
	struct stackNode *next;
	struct stackNode *prev;
};

//Create a new stack and return it
Stack stackCreate () {
	struct stackInternals *newStack = malloc (sizeof (struct stackInternals));
	newStack->size = 0;
	newStack->tail = NULL;
	return newStack;	
}


//Adds an element to the stack
void stackPush(Stack s, int item) {
	struct stackNode *newNode = malloc ( sizeof (struct stackNode) );
	newNode->data = item;
	//If the stack was empty
	//Make the first element
	if (s->tail == NULL) {
		s->tail = newNode;
		newNode->prev = NULL;
	}
	//If not empty, simply add a stack element
	else { 
		newNode->prev = s->tail;
		s->tail->next = newNode
	}
	s->tail = newNode;
	newNode->next = NULL;
	s->size++;
}

//Removes an node from the stack
int stackPop(Stack s) {

	if (s->tail == NULL) {
		printf("The stack is empty!\n");
		exit(1);
	}
	//Account for removal of the last stack element
	int returnData = s->tail->data;
	if (s->tail->prev == NULL) {
		free (s->tail);
		s->tail = NULL;
	}
	else {
		s->tail = s->tail->prev;
		free (s->tail->next);
		s->tail->next = NULL;
	}
	s->size--;
	return returnData;
}

int stackSize(Stack s) {
	return s->size;
}

//Implementation of a stack via an array
/*
//Create a new stack and return it
Stack stackCreate() {
	struct stackInternals *newStack = malloc (sizeof (struct stackInternals));
	newStack->top = 0;
	return newStack;
}

//Add a new item to the top of the stack
void stackPush(Stack s, int item) {
	if (s->top >= MAX_STACK) {
		//array holding the stack items is full
		printf("Maximum stack size reached\n");
		exit(1);
	}
	s->stack[s->top] = item;
	s->top++;
}

//Remove the item at the top of the stack
//Then return the current top element
int stackPop(Stack s) {
	if (s->top <= 0) {
		//no elements in the stack
		printf("There are no elements to pop from the stack\n");
		exit(1);
	}
	s->top--;
	return s->stack[s->top];
}

int stackSize(Stack s) {
	return s->top;
}
*/



















