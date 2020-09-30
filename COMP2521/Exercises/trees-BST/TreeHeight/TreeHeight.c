//A program that obtains the height of a tree, starting from a height of 0

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"



int TreeHeight(Tree t) {
	
	if (t == NULL) {
		return -1;
	}
	
	int CompareLeft = TreeHeight(t->left);
	int CompareRight = TreeHeight(t->right);
		
	if (CompareLeft > CompareRight) {
		return CompareLeft + 1;
	}
	else {
		return CompareRight + 1;
	}
}

