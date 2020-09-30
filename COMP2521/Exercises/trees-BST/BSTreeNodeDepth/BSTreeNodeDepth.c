//Returns the depth of a node given a key in the tree

#include <stdlib.h>
#include <stdio.h>
#include "BSTree.h"



/*
//////////////////////////////////////////////////////////////////
//Helper function that finds the depth of a BST
int getLevel (BSTree t, int key, int depth) {
	if (t == NULL) {
		return -1;
	}
	
	if (t->value == key) {
		return depth;
	}
	
	if (t->value < key) {
		return getLevel(t->right, key, depth + 1);
	}
	else {
		return getLevel(t->left, key, depth + 1);
	}
}

//Improved implementation here
int BSTreeNodeDepth(BSTree t, int key) {
	int depth = 0;
	return getLevel(t, key, depth);
}
*/

//Returns the depth of a node
int BSTreeNodeDepth (BSTree t, int key) {
	//Base Case
	if (t == NULL) {
		return -1;
	}
	if (key == t->value) {
		return 0;
	}
	
	int Left = BSTreeNodeDepth(t->left, key);
	int Right = BSTreeNodeDepth(t->right, key);
	if (Left >= 0) {
		return Left + 1;
	}
	else if (Right >= 0) {
		return Right + 1;
	}
	
	return -1;
}















///////////////////////////////////////////////////////////////////////////
// Original Implementation
/*
//need to handle keys which are not in the BST


BSTree check_node (BSTree t, int key) {
	if (t == NULL) {
		return t;
	}
	if (t->value == key) {
		return t;
	}
	if (t->value < key) {
		t = check_node(t->right, key);
	}
	else {
		t = check_node(t->left, key);
	}
	return t;
}


int BSTreeNodeDepth(BSTree t, int key) {
	int nodeDepth = 0;
	//Check if the key is present in the tree
	BSTree check = check_node(t, key);
	
	if (check == NULL) {
		return -1;
	}
	if (t->value == key) {
		return nodeDepth;
	}
	
	//Traverse through the tree and find the node
	if (t->value > key) {
		nodeDepth = BSTreeNodeDepth(t->left, key) + 1;
	}
	else {
		nodeDepth = BSTreeNodeDepth(t->right, key) + 1;
	}
	
	return nodeDepth;
}

*/
