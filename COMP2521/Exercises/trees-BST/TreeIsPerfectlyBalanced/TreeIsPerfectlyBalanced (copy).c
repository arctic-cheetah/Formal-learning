
#include <stdlib.h>

#include "tree.h"

//Get the number of nodes of the left and right subtree

int nodeNum (Tree t) {
	if (t == NULL) {
		return -1;
	}
	
	int l = nodeNum(t->left) + 1;
	int r = nodeNum(t->right) + 1;
	return r + l;
	
}
//Use in order traversal
bool TreeIsPerfectlyBalanced(Tree t) {
	//base case
	if (t == NULL) {
		return true;
	}
	
	//Check that each node is balanced
	int l = nodeNum(t->left);
	int r = nodeNum(t->right);
	int diff = l - r;
	bool check;
	if (-1 <= diff && diff <= 1) {
		check = true;
	}
	else{
		check = false;
	}
	//Check for the left and right
	bool lc = TreeIsPerfectlyBalanced(t->left);
	bool rc = TreeIsPerfectlyBalanced(t->right);
	
	return lc && rc && check;
}






















