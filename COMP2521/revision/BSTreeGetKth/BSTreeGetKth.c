
#include <stdlib.h>
#include <stdio.h>
#include "BSTree.h"


//Convert the BST to an array using inorder traversal
void getKth(BSTree t, int *k, int *n) {
	//base case
	if (t == NULL) {
		return;
	}
	
	
	getKth(t->left, k, n);
	//Stopping case;
	if (*k == 0) {
		*n = t->value;
	}
	*k -=1;
	getKth(t->right, k, n);
	
	return;
}


int BSTreeGetKth(BSTree t, int k) {
	int num = -1;
	getKth(t, &k, &num);
	return num;
}

