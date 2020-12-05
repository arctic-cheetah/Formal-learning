
#include <stdlib.h>

#include "tree.h"

int TreeSumOdds(Tree t) {
	//Base case;
	if (t == NULL) {
		return 0;
	}
	
	int l = TreeSumOdds(t->left);
	int r = TreeSumOdds(t->right);
	int sum = l + r;
	//check if the current node's key is odd
	if (t->value & 1) {
		sum += t->value;
	}
	
	return sum;
}

