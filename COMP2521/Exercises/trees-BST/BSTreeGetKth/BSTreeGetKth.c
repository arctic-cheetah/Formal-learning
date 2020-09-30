
#include <stdlib.h>
#include <stdio.h>

#include "BSTree.h"

BSTree inOrderTrav(BSTree t, int *k) {
	if (t == NULL) {
		return NULL;
	}
	
	BSTree left = inOrderTrav(t->left, k);
	
	if (left != NULL) {
		return left;
	}
	
	*k -=1;
	if (*k == -1) {
		return t;
	}
	
	return inOrderTrav(t->right, k);
}


int BSTreeGetKth(BSTree t, int k) {
	BSTree value = inOrderTrav(t, &k);
	return value->value;
}

