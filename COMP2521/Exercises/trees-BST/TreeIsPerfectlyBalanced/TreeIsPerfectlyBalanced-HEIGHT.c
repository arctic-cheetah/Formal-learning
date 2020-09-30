//A program that 

#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

#define NOT_BALANCED 0
#define BALANCED 1

//Need to traverse the tree and count the number of nodes in the subtrees
int treeBalanceCheck(Tree t, int *height) {
	
	int leftHeight = 0;
	int rightHeight = 0;
	
	if (t == NULL) {
		*height = 0;
		return 1;
	}
	//Obtain the left and right heights
	int leftCount = treeBalanceCheck(t->left, &leftHeight); 
	int rightCount = treeBalanceCheck(t->right, &rightHeight); 
	
	//And obtain the highest
	if (leftHeight > rightHeight) {
		*height = leftHeight + 1;
	}
	else {
		*height = rightHeight + 1;
	}
	
	printf("%d\n\n", leftHeight - rightHeight);
	
	//Check if left and right subtree are balanced
	//Find the difference in the height
	if ( -1 <= (leftHeight - rightHeight) && (leftHeight - rightHeight) <= 1) {
		return leftCount && rightCount;
	}
	else {
		return NOT_BALANCED;
	}
}

bool TreeIsPerfectlyBalanced(Tree t) {
	if (t == NULL) {
		return true;
	}
	int height = 0;
	return treeBalanceCheck(t, &height);
	
}

