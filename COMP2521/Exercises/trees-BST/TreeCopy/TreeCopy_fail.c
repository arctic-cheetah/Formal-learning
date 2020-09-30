
#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

//A helper function that creates new node and returns it
Tree new_node (int value) {
	Tree newNode = malloc(sizeof(Tree));
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->value = value;
	return newNode;
}
//Need to find the depth of the tree, eg; height

int treeHeight(Tree t) {
	if (t == NULL) {
		return -1;
	}
	
	int leftHeight = treeHeight(t->left);
	int rightHeight = treeHeight(t->right);
	
	if (leftHeight > rightHeight) {
		return leftHeight + 1;
	}
	else {
		return rightHeight + 1;
	}
}

//My implementation of copying a tree
Tree tree_copy (Tree t, int *depth) {
	if (t == NULL) {
		return t;
	}
	*depth -=1;
	Tree newNode = new_node(t->value);
	printf("Depth is : %d\n", *depth);
	
	Tree currOT = t;
	
	Tree currNew = newNode;
	
	int i = 1;
	//We are guaranteed to not begin from the root node
	while (i < *depth) {
		
		//copy nodes from the left tree
		if (currOT->left != NULL) {
			currNew->left = new_node(currOT->left->value);		
		}
		else {
			currNew->left = NULL;
		}
		
		//Copy nodes from the right tree
		if (currOT->right != NULL) {
			currNew->right = new_node(currOT->right->value);	
		}
		else {
			currNew->right = NULL;
		}
		
		//Traverse to the node on the same level
		curr = prev;
		if (prev = curr) {
		
		}
		//Traverse both trees to the next level
		else {
			currOT = currOT->left;
			currNew = currNew->left;
		}
		
		i++;
	}
		/*
		newNode->left = tree_copy(t->left, depth);
		newNode->right = tree_copy(t->right, depth);
		return newNode;
		*/
	return newNode;
}

//A function that counts the number of nodes up to a given depth of a BS-TREE;

int treenode_count (Tree t, int *depth) {
	return NULL;	
}

//Need to start from root node, and copy until the desired depth

//Copies a tree to a desired depth
Tree TreeCopy(Tree t, int depth) {
	if (depth < 0) {
		return NULL;
	}
	
	int t_height = treeHeight(t);
	printf("%d\n", t_height);
	Tree newTree = NULL;
	if (depth <= t_height) {
		newTree = tree_copy(t, &depth + 1);
	}
	else {
		newTree = tree_copy(t, &t_height);
	}
	
	return newTree;
}





























































