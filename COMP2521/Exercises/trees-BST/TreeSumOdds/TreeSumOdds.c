//A program that returns the sum of all the nodes with odd value
#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

//
int TreeSumOdds(Tree t) {
	if (t == NULL) {
		return 0;
	}
	int oddSum = 0;
	int leftSum = TreeSumOdds(t->left);
	int rightSum = TreeSumOdds(t->right);
	
	//Use bitwise operation to check for odd number
	if (t->value & 1) {
		oddSum += t->value;
	}
	
	oddSum = oddSum + leftSum + rightSum;
	return oddSum;
}

