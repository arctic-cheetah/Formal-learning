
#include <stdlib.h>

#include "BSTree.h"

//Check if the node-key pair exists

int findNode(BSTree t, int key) {
	if (t == NULL) {
		return 0;
	}
	
	if (key < t->value) {
		return findNode(t->left, key);
	} 
	else if (key > t->value) {
		return findNode(t->right, key);
	}
	
	else {
		return 1;
	}
}

int nodeDepth(BSTree t, int key) {
	if (t == NULL) {
		return -1;
	}
	
	if (key < t->value) {
		return nodeDepth(t->left, key) + 1;
	} 
	else if (key > t->value) {
		return nodeDepth(t->right, key) + 1;
	}
	
	else {
		return 0;
	}
}

int BSTreeNodeDepth(BSTree t, int key) {
	if(findNode(t, key) == 1) {
		return nodeDepth(t, key);
	}
	else {
		return -1;
	}
}


