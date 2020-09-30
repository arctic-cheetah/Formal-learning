//An in order traversal of a binary tree
#include <stdio.h>
#include <stdlib.h>


#include "BSTree.h"

void BSTreePostfix(BSTree t) {
	if (t != NULL) {
		BSTreePostfix(t->left);
		BSTreePostfix(t->right);
		printf("%d ", t->value);
	}
	
}

