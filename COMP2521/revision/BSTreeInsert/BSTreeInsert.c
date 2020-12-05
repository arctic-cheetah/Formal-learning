
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

BSTree BSTreeInsert(BSTree t, int val) {
	//Make a new node
	if (t == NULL) {
		BSTree n = malloc(sizeof(struct BSTNode));
		n->value = val;
		n->left = NULL;
		n->right = NULL;
		return n;
	}
	
	//Recursive case;
	if (val < t->value) {
		t->left = BSTreeInsert(t->left, val);
	}
	else {
		t->right = BSTreeInsert(t->right, val);
	}
	
	return t;
}

