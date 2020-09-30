// Binary Search Tree ADT interface ... 

#include <stdbool.h>

typedef int Item;      // item is just a key

typedef struct Node *Tree;
struct Node {
	int data;
	Tree left;
	Tree right;
};

Tree newTree();        // create an empty Tree
void freeTree(Tree);   // free memory associated with Tree
void showTree(Tree);   // display a Tree (sideways)

bool TreeSearch(Tree, Item);   // check whether an item is in a Tree
int  TreeHeight(Tree);         // compute height of Tree
int TreeNumNodes(Tree t);     // count #nodes in Tree
Tree TreeInsert(Tree, Item);   // insert a new item into a Tree
Tree TreeDelete(Tree, Item);   // delete an item from a Tree
int TreeNumLeaves(Tree t);  //Counts the number of leaves
int TreeCountInternal(Tree t); //Counts the internal number of leaves
int TreeNodeDepth (Tree t, int key); //Gets the depth of a node
int BSTreeCountOdds(Tree t); //Returns the number of nodes which are odd
//int BSTreeCountGreater(BSTree t, int val);//Returns the number of nodes greater than the key


// internal functions made visible for testing
Tree rotateRight(Tree);
Tree rotateLeft(Tree);
Tree insertAtRoot(Tree, Item);
Tree partition(Tree, int);
Tree rebalance(Tree);
