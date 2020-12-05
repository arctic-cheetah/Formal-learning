
#include "BSTree.h"

#include <stdlib.h>

BSTree BSTreeGetSmallest(BSTree t) {
	if (t == NULL) {
		return t;
	}
	//Go to the left
	else if (t->left != NULL) {
		t = BSTreeGetSmallest(t->left);
	}
	
	return t;
	
}

