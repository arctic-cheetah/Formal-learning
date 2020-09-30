

#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

//A helper function that creates new node and returns it
Tree new_node (int value) {
	Tree newNode = malloc(sizeof(struct node));
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


//A pair of functions that finds the level of a node
int nodeHeightUtil(Tree t, int value, int level) {
	if (t == NULL) {
		return 0;
	}
	
	if (t->value == value) {
		return level;
	}
	//Using a preorder traversal, find the level of a node
	int downLevel = nodeHeightUtil(t->left, value, level + 1);
	if (downLevel != 0) {
		return downLevel;
	}
	
	downLevel = nodeHeightUtil(t->right, value, level + 1);
	return downLevel;
	
}

int nodeHeight (Tree root, int value) {
	return nodeHeightUtil(root, value, 0);
}


Tree insert_node (Tree t, int val) {
	if (t != NULL) {
		if (t->value <= val) {
			t->right = insert_node(t->right, val);
		}
		else if (t->value >= val) {
			t->left = insert_node(t->left, val);
		}
	}
	else {
		t = new_node(val);
	}
	return t;
}
//Need to start from root node, and copy until the desired depth

//My implementation of copying a tree

Tree cp_tree(Tree root, Tree t, Tree newNode, int depth) {
	if (t == NULL) {
		return NULL;
	}
	newNode = new_node(t->value);
	//Check!!!
	//Add the nodes if they are at the desired depth
	if (t->left != NULL && nodeHeight(root, t->left->value) <= depth) {
		newNode->left = cp_tree(root, t->left, newNode, depth);
	}
	if (t->right != NULL && nodeHeight(root, t->right->value) <= depth) {
		newNode->right = cp_tree(root, t->right, newNode, depth);
	}
	return newNode;
}

//Copies a tree to a desired depth
Tree TreeCopy(Tree t, int depth) {
	if (t == NULL) {
		return NULL;
	}
	
	if (depth < 0) {
		return NULL;
	}
	
	Tree newTree = NULL;
	int h = treeHeight(t);
	if (depth > h) {
		newTree = cp_tree(t, t, newTree, h);
	}
	else {
		newTree = cp_tree(t, t, newTree, depth);
	}
	return newTree;
}





























































