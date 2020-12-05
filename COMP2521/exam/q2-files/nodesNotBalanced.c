// nodesNotBalanced.c ... implementation of nodesNotBalanced function

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

/* 
    You will submit only this one file.

    Implement the function "nodesNotBalanced" below. Read the exam paper for a
    detailed specification and description of your task.  

    - DO NOT modify the code in any other files. 
    - If you wish, you can add static variable and/or 
      helper functions to this file.  
    - DO NOT add a "main" function to this file. 
*/

//A helper function that returns the height of a node
int nodeHeight (BSTree t) {
	if (t == NULL) {
		return -1;
	}
	
	int lh = nodeHeight(t->left) + 1;
	int rh = nodeHeight(t->right) + 1;
	
	if (lh > rh) {
		return lh;
	}
	
	return rh;	
}
//O(1)
int nodesNotBalanced(BSTree t) {
	int numNodes = 0;
	//Base case
	if (t == NULL) {
		numNodes = 0;
		return numNodes;
	}
	//Fetch the number of balanced nodes
	numNodes = nodesNotBalanced(t->left) + nodesNotBalanced(t->right);//O(n)
	
	//Fetch the height
	int lh = nodeHeight(t->left) + 1;//O(n)
	int rh = nodeHeight(t->right) + 1;//O(n)
	int balance = lh - rh;
	
	//Balanced
	if (-1 <= balance && balance <= 1) {
		return numNodes;
	}
	//Imbalanced
	return numNodes + 1;
}




