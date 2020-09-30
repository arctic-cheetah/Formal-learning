//A program that determines if a BST is balanced by checking the number of nodes
//NOT HEIGHT!

#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

#define NOT_BALANCED 0
#define BALANCED 1

//Need to traverse the tree and count the number of nodes in the subtrees
int treeBalanceCheck(Tree t, int *isBalanced) {
	
	if (t == NULL) {
		return 0;
	}
	int leftCount = treeBalanceCheck(t->left, isBalanced); 
	int rightCount = treeBalanceCheck(t->right, isBalanced); 
	

	//Check if left and right subtree are balanced
	//Find the difference in the number of the nodes
	if ( *isBalanced != 0 
		&& -1 <= (leftCount - rightCount) 
		&& (leftCount - rightCount) <= 1
	) {
		*isBalanced = 1;
	}
	else {
		*isBalanced = 0;
	}
	return leftCount + rightCount + 1;
}

bool TreeIsPerfectlyBalanced(Tree t) {
	if (t == NULL) {
		return true;
	}
	int isBalanced = 1;
	treeBalanceCheck(t, &isBalanced);
	
	return isBalanced;
}

