

#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

#define MAX_LENGTH 10

////////////////////////////////////////////////////////////////////////////////
///Queue implementation
typedef struct queueInternals {
	// This implements a queue using an array
	
	Tree head;
	Tree tail;
	Tree array[MAX_LENGTH];
	int size;
	
}*Queue;

//Change to linked list by uncommenting this! 
/*
struct queueNode{
	struct queueNode *next;
	int data;
};
*/

//Implementation of a queue via an array
//Create a new queue
Queue queueCreate(void) {
	struct queueInternals *newQueue = malloc (sizeof( struct queueInternals));
	newQueue->head = NULL;
	newQueue->tail = NULL;
	newQueue->size = 0;
	return newQueue;
}

//Add an element to the queue
void queueAdd(Queue q, Tree item) {
	if (q->size != MAX_LENGTH) {
		q->array[q->size] = item;
		//Make the head point to the front of the queue
		if (q->head == NULL) {
			q->head = q->array[q->size];
		}
		//Make the tail point to the end of the queue
		q->tail = q->array[q->size];
		q->size++;
	}
	else {
		printf("Maximum queue size reached!\n");
	}
}

//Remove a person from the queue and return the element
Tree queueRemove(Queue q) {
	Tree frontQueue = q->head;
	if (q->size != 0) {
		//Shift everything to the left
		for (int length = 0; length < q->size; length++ ) {
			q->array[length] = q->array[length + 1];
		}
		q->size--;
		q->tail = q->array[q->size];
		q->head = q->array[0];
		return frontQueue;
	}
	else {
		printf("There are no elements to remove from the queue!\n");
		exit(1);
	}
}
///////////////////////////////////////////////////////////////////////



//A helper function that creates new node and returns it
Tree new_node (int value) {
	Tree newNode = malloc(sizeof(Tree));
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->value = value;
	return newNode;
}
//Need to find the depth of the tree, eg; height

int treeHeight(Tree t) {
	if (t == NULL) {
		return -1;
	}
	
	int leftHeight = treeHeight(t->left);
	int rightHeight = treeHeight(t->right);
	
	if (leftHeight > rightHeight) {
		return leftHeight + 1;
	}
	else {
		return rightHeight + 1;
	}
}

Tree insert_node (Tree t, int val) {
	if (t != NULL) {
		if (t->value <= val) {
			t->right = insert_node(t->right, val);
		}
		else if (t->value >= val) {
			t->left = insert_node(t->left, val);
		}
	}
	else {
		t = new_node(val);
	}
	return t;
}

int numberOfNodes (int depth) {
	int Count = 1;
	for (int i = 0; i <= depth; i++) {
		Count *= 2;
	}
	return Count - 1;
}

//Need to start from root node, and copy until the desired depth

//Copies a tree to a desired depth
Tree TreeCopy(Tree t, int depth) {
	if (depth < 0) {
		return NULL;
	}
	//int h = treeHeight(t);
	int maxNumberNode = numberOfNodes(depth);
	Queue q = queueCreate();
	Tree newTree = NULL;
	queueAdd(q, t);
	int i = 0;
	while (q->head != NULL && i < maxNumberNode) {
		Tree temp = queueRemove(q);
		newTree = insert_node(newTree, temp->value); 
		if (temp->left != NULL) {
			queueAdd(q, temp->left);
		}
		if (temp->right != NULL) {
			queueAdd(q, temp->right);
		}
		
		i++;
	}
	return newTree;
}





























































