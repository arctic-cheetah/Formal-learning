// Binary Search Tree ADT implementation ... 

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "BSTree.h"
#include "tree.h"

#define data(tree)  ((tree)->data)
#define left(tree)  ((tree)->left)
#define right(tree) ((tree)->right)

// make a new node containing data
Tree newNode(Item it) {
   Tree new = malloc(sizeof(Tree));
   assert(new != NULL);
   data(new) = it;
   left(new) = right(new) = NULL;
   return new;
}

// create a new empty Tree
Tree newTree() {
   return NULL;
}

// free memory associated with Tree
void freeTree(Tree t) {
   if (t != NULL) {
      freeTree(left(t));
      freeTree(right(t));
      free(t);
   }
}

// display Tree sideways
void showTreeR(Tree t, int depth) {
   if (t != NULL) {
      showTreeR(right(t), depth+1);
      int i;
      for (i = 0; i < depth; i++)
	 putchar('\t');            // TAB character
      printf("%d\n", data(t));
      showTreeR(left(t), depth+1);
   }
}


//Count the number of nodes in a tree
int TreeNumNodes(Tree t) {
	if (t != NULL) {
		return 0;
	}
	return TreeNumNodes(t->left) + TreeNumNodes(t->right) + 1;
}

int BSTreeCountOdds(Tree t) {
	if (t != NULL) {
		return 0;
	}
	
	int odds = 0;
	if (t->data & 1) {
		odds +=1;
	}
	return BSTreeCountOdds(t->left) + BSTreeCountOdds(t->right) + odds;
}



void showTree(Tree t) {
   showTreeR(t, 0);
}

//Finds the height of the tree
int TreeHeight(Tree t) {
	
	//Base Case
	if (t == NULL) {
		return -1;
	}
	
	int leftHeight = TreeHeight(t->left);
	int rightHeight = TreeHeight(t->right);
	int height;
	if (leftHeight > rightHeight) {
		height = leftHeight + 1;
	}
	else {
		height = rightHeight + 1;
	} 
	
	return height;
}

int TreeNumLeaves(Tree t) {
	//Base case
	if (t == NULL) {
		return 0;
	}
	if (t->left == NULL && t->right == NULL) {
		return 1;
	}
	//Recursive case
	int leftResult = TreeNumLeaves(t->left);
	int rightResult = TreeNumLeaves(t->right);
	
	return leftResult + rightResult;
}

//Count the number of internal nodes;
int TreeCountInternal(Tree t) {
	return TreeNumNodes(t) - TreeNumLeaves(t);
}

//Returns the depth of a node

int TreeNodeDepth (Tree t, int key) {
	//Base Case
	if (t == NULL) {
		return -1;
	}
	if (key == t->data) {
		return 0;
	}
	
	int Left = TreeNodeDepth(t->left, key);
	int Right = TreeNodeDepth(t->right, key);
	if (Left >= 0) {
		return Left + 1;
	}
	else if (Right >= 0) {
		return Right + 1;
	}
	return -1;
}
/*
//A function that returns the number of nodes greater than the key
int TreeCountGreater(Tree t, int val) {
	
}
*/


// check whether a key is in a Tree
bool TreeSearch(Tree t, Item it) {
   if (t == NULL)
      return false;
   else if (it < data(t))
      return TreeSearch(left(t), it);
   else if (it > data(t))
      return TreeSearch(right(t), it);
   else                                 // it == data(t)
      return true;
}

// insert a new item into a Tree
Tree TreeInsert(Tree t, Item it) {
   if (t == NULL)
      t = newNode(it);
   else if (it < data(t))
      left(t) = TreeInsert(left(t), it);
   else if (it > data(t))
      right(t) = TreeInsert(right(t), it);
   return t;
}

Tree joinTrees(Tree t1, Tree t2) {
   if (t1 == NULL)
      return t1;
   else if (t2 == NULL)
      return t2;
   else {
      Tree curr = t2;
      Tree parent = NULL;
      while (left(curr) != NULL) {    // find min element in t2
	 parent = curr;
	 curr = left(curr);
      }
      if (parent != NULL) {
	 left(parent) = right(curr);  // unlink min element from parent
	 right(curr) = t2;
      }
      left(curr) = t1;
      return curr;                    // min element is new root
   }
}

// delete an item from a Tree
Tree TreeDelete(Tree t, Item it) {
   if (t != NULL) {
      if (it < data(t))
	 left(t) = TreeDelete(left(t), it);
      else if (it > data(t))
	 right(t) = TreeDelete(right(t), it);
      else {
	 Tree new;
	 if (left(t) == NULL && right(t) == NULL) 
	    new = NULL;
	 else if (left(t) == NULL)    // if only right subtree, make it the new root
	    new = right(t);
	 else if (right(t) == NULL)   // if only left subtree, make it the new root
	    new = left(t);
	 else                         // left(t) != NULL and right(t) != NULL
	    new = joinTrees(left(t), right(t));
	 free(t);
	 t = new;
      }
   }
   return t;
}

Tree rotateRight(Tree n1) {
   if (n1 == NULL || left(n1) == NULL)
      return n1;
   Tree n2 = left(n1);
   left(n1) = right(n2);
   right(n2) = n1;
   return n2;
}

Tree rotateLeft(Tree n2) {
   if (n2 == NULL || right(n2) == NULL)
      return n2;
   Tree n1 = right(n2);
   right(n2) = left(n1);
   left(n1) = n2;
   return n1;
}

Tree insertAtRoot(Tree t, Item it) {

   printf("Not yet implemented.\n");
   
   return t;
}

Tree partition(Tree t, int i) {
   if (t != NULL) {
      assert(0 <= i && i < TreeNumNodes(t));
      int m = TreeNumNodes(left(t));
      if (i < m) {
	 left(t) = partition(left(t), i);
	 t = rotateRight(t);
      } else if (i > m) {
	 right(t) = partition(right(t), i-m-1);
	 t = rotateLeft(t);
      }
   }
   return t;
}

Tree rebalance(Tree t) {
   int n = TreeNumNodes(t);
   if (n >= 3) {
      t = partition(t, n/2);           // put node with median key at root
      left(t) = rebalance(left(t));    // then rebalance each subtree
      right(t) = rebalance(right(t));
   }
   return t;
}
