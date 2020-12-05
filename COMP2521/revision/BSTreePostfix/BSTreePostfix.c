
#include <stdio.h>

#include "BSTree.h"

void BSTreePostfix(BSTree t) {
	//base case
	if (t == NULL) {
		return;
	}
	
	BSTreePostfix(t->left);
	BSTreePostfix(t->right);
	printf("%d ", t->value);
	
}

