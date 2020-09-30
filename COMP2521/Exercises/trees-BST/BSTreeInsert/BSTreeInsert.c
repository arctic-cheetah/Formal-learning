//A program that demonstrates the insertion of a new node in a binary tree


#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

BSTree new_node (int val);

BSTree BSTreeInsert(BSTree t, int val) {
	if (t != NULL) {
		if (t->value <= val) {
			t->right = BSTreeInsert(t->right, val);
		}
		else if (t->value >= val) {
			t->left = BSTreeInsert(t->left, val);
		}
	}
	else {
		t = new_node(val);
	}
	
	return t;
}

//A helper function to create a new node

BSTree new_node (int val) {
	
	struct BSTNode *newNode = malloc(sizeof(struct BSTNode));
	newNode->value = val;
	newNode->right = NULL;
	newNode->left = NULL;
	
	return newNode;
}


