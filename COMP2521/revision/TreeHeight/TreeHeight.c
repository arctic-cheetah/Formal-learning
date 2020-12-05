
#include <stdlib.h>

#include "tree.h"

int TreeHeight(Tree t) {
	if (t == NULL) {
		return -1;
	}
	
	int l = TreeHeight(t->left) + 1;
	int r = TreeHeight(t->right) + 1;
	
	if (l > r) {
		return l;
	}
	return r;
	
}

