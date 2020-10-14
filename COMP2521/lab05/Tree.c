// Implementation of the BST ADT using an AVL tree

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Time.h"
#include "Tree.h"

typedef struct node *Node;
struct node {
    Time time;
    int  height;
    Node left;
    Node right;
};

struct tree {
    Node root;
};

////////////////////////////////////////////////////////////////////////
// Function Prototypes

static void doFree(Node n);
static Node doInsert(Node n, Time time);
static Node rotateLeft(Node n);
static Node rotateRight(Node n);
static int  height(Node n);
static int  max(int a, int b);
static Node newNode(Time time);

////////////////////////////////////////////////////////////////////////
// Constructor and Destructor

// Creates a new empty tree
Tree TreeNew(void) {
    Tree t = malloc(sizeof(*t));
    if (t == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }
    t->root = NULL;
    return t;
}

// Frees all memory associated with the given tree
void TreeFree(Tree t) {
    doFree(t->root);
    free(t);
}

static void doFree(Node n) {
    if (n != NULL) {
        doFree(n->left);
        doFree(n->right);
        TimeFree(n->time);
        free(n);
    }
}

////////////////////////////////////////////////////////////////////////
// Insertion

// Inserts  a  copy of the given time into the tree if it is not already
// in the tree
void TreeInsert(Tree t, Time time) {
    t->root = doInsert(t->root, time);
}


//A helper function that calculates the balance factor of a tree
int balance (Node n) {
	if (n == NULL) {
		return 0;
	}
	return height(n->left) - height(n->right);
}

static Node doInsert(Node n, Time time) {
    if (n == NULL) {
        return newNode(time);
    }

    // insert recursively
    int cmp = TimeCmp(time, n->time);
    if (cmp < 0) {
        n->left = doInsert(n->left, time);
    } else if (cmp > 0) {
        n->right = doInsert(n->right, time);
    } else { // (cmp == 0)
        // if time is already in the tree,
        // we can return straight away
        return n;
    }
	//My original implementation:
	
	//IN FUTURE:
	//TRY UNSW'S IMPLEMENTATION
	
    // insertion done
    // fix the height of the current subtree
    n->height = 1 + max(height(n->left), height(n->right));
    
    //Balance may have a bug... if any of the nodes are NULL
    int balanceNum = balance(n);
    
    //Check the type of rotation needed from the child nodes
    //By considering 4 cases
    //LL
    if (balanceNum > 1 && balance(n->left) >= 0) {
    	return rotateRight(n);
    }
    //LR
    if (balanceNum > 1 && balance(n->left) < 0) {
    	n->left = rotateLeft(n->left);
    	return rotateRight(n);
    }
    //RR
    if (balanceNum < -1 && balance(n->right) <= 0) {
    	return rotateLeft(n);
    }
    //RL
    if (balanceNum < -1 && balance(n->right) > 0) {
    	n->right = rotateRight(n->right);
    	return rotateLeft(n);
    }
    
    return n;
}

static Node newNode(Time time) {
    Node n = malloc(sizeof(*n));
    if (n == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }

    n->time = TimeCopy(time);
    n->height = 0;
    n->left = NULL;
    n->right = NULL;
    return n;
}

//A helper function that returns the height of the tree

int tree_height(Node n) {
	if (n == NULL) {
		return -1;
	}
	int left = tree_height(n->left);
	int right = tree_height(n->right);
	if (left > right) {
		return left + 1;
	}
	else {
		return right + 1;
	}
}

static Node rotateLeft(Node n) {
	//Check for empty node
	if (n == NULL) {
		return n;
	}
	Node a = n->right;
	if (a != NULL) {
		Node b = a->left;
		//rotate left
		a->left = n;
		n->right = b;
		//Update the height
		n->height = 1 + max(height(n->left), height(n->right));
		a->height = 1 + max(height(a->left), height(a->right));
		return a;
	}
	return n;
}

// Rotates the given subtree right and returns the root of  the  updated
// subtree.
static Node rotateRight(Node n) {
	if (n == NULL) {
		return n;
	}
	Node a = n->left;
	if (a != NULL) {
		Node b = a->right;
		//rotate right
		a->right = n;
		n->left = b;
		//Update the height
		n->height = 1 + max(height(n->left), height(n->right));
		a->height = 1 + max(height(a->left), height(a->right));
		return a;
	}
	return n;
}


// Returns  the height of a subtree while assuming that the height field
// of the root node of the subtree is correct
static int height(Node n) {
    if (n == NULL) {
        return -1;
    } else {
        return n->height;
    }
}

static int max(int a, int b) {
    return a > b ? a : b;
}

////////////////////////////////////////////////////////////////////////
// Specialised Operations


Time tFloor(Node n, Time time) {
	//Base case
	if (n == NULL) {
		return NULL;
	}
	Time check;
	if (TimeCmp(n->time, time) > 0) {
		check = tFloor(n->left, time);
	}
	else if (TimeCmp(n->time, time) < 0) {
		check = tFloor(n->right, time);
	}
	else if (TimeCmp(n->time, time) == 0) {
		return n->time;
	}
	
	//if NULL is returned for check
	//Then check the first instance of the latest time of that node;
	if (check == NULL && TimeCmp(n->time, time) < 0) {
		return n->time;
	}
	return check;
}

Time tCeiling(Node n, Time time) {
	//Base case
	if (n == NULL) {
		return NULL;
	}
	Time check;
	if (TimeCmp(n->time, time) > 0) {
		check = tCeiling(n->left, time);
	}
	else if (TimeCmp(n->time, time) < 0) {
		check = tCeiling(n->right, time);
	}
	else if (TimeCmp(n->time, time) == 0) {
		return n->time;
	}
	
	//if NULL is returned for check
	//Then check the first instance of the earliest time of that node
	if (check == NULL && TimeCmp(n->time, time) > 0) {
		return n->time;
	}
	//Now we need to check if there exists a node earlier than the checked time
	if (check != NULL && TimeCmp(n->time, check) < 0
			 && TimeCmp(n->time, time) > 0) {
		return n->time;
	}
	return check;
}
// Returns the latest time in the tree that is earlier than or equal  to
// the  given  time,  or  NULL if no such time exists. The returned time
// should not be modified or freed.
Time TreeFloor(Tree t, Time time) {
    // TODO: Add your code here and change
    //       the return statement if needed
    //       You can create helper functions
    //       if needed
    return tFloor(t->root, time);
}

// Returns the earliest time in the tree that is later than or equal  to
// the  given  time,  or  NULL if no such time exists. The returned time
// should not be modified or freed.
Time TreeCeiling(Tree t, Time time) {
    // TODO: Add your code here and change
    //       the return statement if needed
    //       You can create helper functions
    //       if needed

    return tCeiling(t->root, time);
}

////////////////////////////////////////////////////////////////////////
// Printing

//////////////////
// List the items

static void doList(Node n);

void TreeList(Tree t) {
    doList(t->root);
}

static void doList(Node n) {
    if (n != NULL) {
        doList(n->left);
        TimeShow(n->time);
        printf("\n");
        doList(n->right);
    }
}

///////////////////////////
// Show the tree structure

typedef unsigned long long uint64;
static void doShow(Node n, int level, uint64 arms);

void TreeShow(Tree t) {
    if (t->root != NULL && t->root->height >= 64) {
        printf("Tree is too tall!\n");
    } else {
        doShow(t->root, 0, 0);
    }
}

// This  function  uses a hack to determine when to draw the arms of the
// tree and relies on the tree being reasonably balanced. Don't  try  to
// use this function if the tree is not an AVL tree!
static void doShow(Node n, int level, uint64 arms) {
    if (n == NULL) return;

    TimeShow(n->time);
    printf(" (height: %d)\n", n->height);

    if (n->left != NULL) {
        for (int i = 0; i < level; i++) {
            if ((1LLU << i) & arms) {
                printf("│     ");
            } else {
                printf("      ");
            }
        }
        printf("%s", n->right != NULL ? "┝━╸L: " : "┕━╸L: ");
        if (n->right != NULL) {
            arms |= (1LLU << level);
        } else {
            arms &= ~(1LLU << level);
        }
        doShow(n->left, level + 1, arms);
    }

    if (n->right != NULL) {
        // if (n->left != NULL) {
        //     for (int i = 0; i <= level; i++) {
        //         if ((1LLU << i) & arms) {
        //             printf("│     ");
        //         } else {
        //             printf("      ");
        //         }
        //     }
        //     printf("\n");
        // }
        for (int i = 0; i < level; i++) {
            if ((1LLU << i) & arms) {
                printf("│     ");
            } else {
                printf("      ");
            }
        }
        printf("┕━╸R: ");
        arms &= ~(1LLU << level);
        doShow(n->right, level + 1, arms);
    }
}

////////////////////////////////////////////////////////////////////////
// Testing
// All  functions below exist for testing purposes ONLY. Do NOT use them
// in your code.

static Node doInsertLeaf(Node n, Time time);

void TreeRotateLeftAtRoot(Tree t) {
    t->root = rotateLeft(t->root);
}

void TreeRotateRightAtRoot(Tree t) {
    t->root = rotateRight(t->root);
}

void TreeInsertLeaf(Tree t, Time time) {
    t->root = doInsertLeaf(t->root, time);
}

static Node doInsertLeaf(Node n, Time time) {
    if (n == NULL) {
        return newNode(time);
    }

    int cmp = TimeCmp(time, n->time);
    if (cmp < 0) {
        n->left = doInsertLeaf(n->left, time);
    } else if (cmp > 0) {
        n->right = doInsertLeaf(n->right, time);
    }

    n->height = 1 + max(height(n->left), height(n->right));
    return n;
}
