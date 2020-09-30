//A program that finds the smallest value in a BST

#include "BSTree.h"
#include <stdio.h>
#include <stdlib.h>


BSTree BSTreeGetSmallest(BSTree t) {
	if (t == NULL) {
		return NULL;
	}	
	
	if (t->left != NULL) {
		t = BSTreeGetSmallest(t->left);
	}
	return t;
}

