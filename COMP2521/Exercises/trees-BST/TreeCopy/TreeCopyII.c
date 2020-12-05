#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

//A helper function to make to copy a treeNode

Tree copyNode(Tree t) {
	Tree new = malloc(sizeof(struct node));
	new->value = t->value;
	new->left = NULL;
	new->right = NULL;
	return new;
}

Tree TreeCopy(Tree t, int depth) {
	Tree n = NULL;
	if (t == NULL) {
		return NULL;
	}
	//Check that the depth is not zero
	if (depth >= 0) {
		n = copyNode(t);
		n->left = TreeCopy(t->left, depth - 1);
		n->right = TreeCopy(t->right, depth - 1);
	}
	
	return n;
}


