#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "invertedIndex.h"

#define MAX_LENGTH 100

//Time complexity;
//n is the number of nodes
//Create a treeNode from a word
tree create_treeNode(char *str) {
    tree t = malloc( sizeof(struct InvertedIndexNode) );
    //allocate memory for the size of the word
    t->word = malloc( sizeof(char) * MAX_LENGTH );
    //copy the string
    t->word = strcpy(t->word, str);
    
    t->left = NULL;
    t->right = NULL;
    t->fileList = NULL;
    return t;
}

//Insert a listNode from a tree, but requires rotations to
//to maintain ordering
tree insert_treeNode(char *str, char *fileName,
int numWordFile, int termCount, tree t) {
    
    if (t == NULL) {
        t = create_treeNode(str);
        t->fileList = create_listNode(fileName, numWordFile,
                                             termCount);   
        return t;                             
    }
    //Insert desired node with linked list if the word does not exist.
    //If word exists, only insert the file name as a linked list
    if (strcmp(str, t->word) < 0) {
        t->left = insert_treeNode(str, fileName, numWordFile, termCount,
                                  t->left);
    }
    else if (strcmp(str, t->word) > 0) {
        t->right = insert_treeNode(str, fileName, numWordFile, termCount,
                                  t->right);
    }
    else if (strcmp(str, t->word) == 0) {
        //Insert the linked list in ascending order
        t->fileList = insert_listNode(t->fileList, fileName, 
                                      numWordFile, termCount);
    }
    //Balance the tree using tree_balance
    return tree_balance(t);
}
//Search for a node with the matching word
//We can assume the word exists
tree search_tree(tree t, char *word) {
    
    //If word doesn't exist, then give a warning
    if (t == NULL) {
        printf("Entered invalid word\n");
        exit(0);
        return t;
    }

    if (strcmp(word, t->word) < 0) {
        return search_tree(t->left, word);
    }
    else if (strcmp(word, t->word) > 0) {
        return search_tree(t->right, word);
    }
    //found key word!
    return t;
}


//returns the height of the tree O(n), T(1)
int tree_height(tree t) {
    //Base Case
	if (t == NULL) {
		return -1;
	}
	
	int leftHeight = tree_height(t->left);
	int rightHeight = tree_height(t->right);
	int height;
	if (leftHeight > rightHeight) {
		height = leftHeight + 1;
	}
	else {
		height = rightHeight + 1;
	} 
	return height;
}
//This function balances the tree based on its height
tree tree_balance(tree t) {

    //1)Obtain height difference
    int balance = height_diff(t);
    //2)Consider cases for balancing
    //LL
    if (balance > 1 && height_diff(t->left) >= 0) {
        return right_rotation(t);
    }
    //LR
    if (balance > 1 && height_diff(t->left) < 0) {
        t->left = left_rotation(t->left);
        return right_rotation(t);
    }
    //RR
    if (balance < -1 && height_diff(t->right) <= 0) {
        return left_rotation(t);
    }
    //RL
    if (balance < -1 && height_diff(t->right) > 0) {
        t->right = right_rotation(t->right);
        return left_rotation(t);
    }
    return t;
} 

//Calculate the difference in tree heights
int height_diff(tree t) {
    if (t == NULL) { 
        return 0;
    }
    return ( tree_height(t->left) - tree_height(t->right) );
}

//Tree rotations down here O(1)
tree right_rotation(tree t) {
    tree a = t->left;
    tree subTree = a->right;
    a->right = t;
    t->left = subTree;
    return a;
}
tree left_rotation(tree t) {
    tree a = t->right;
    tree subTree = a->left;
    a->left = t;
    t->right = subTree;
    return a;
}


//Create a linked list node;
FileList create_listNode(char *fileName, int numWordFile, int termCount) {
    FileList newNode = malloc( sizeof(struct FileListNode) );
    //Allocate memory for the file name
    newNode->filename = malloc(sizeof(char) * MAX_LENGTH);
    newNode->filename = strcpy(newNode->filename, fileName);

    //Perform a type cast
    newNode->tf = (double)numWordFile / termCount;
    newNode->next = NULL;

    return newNode;
}

//Insert a linked list node in lexical order
//O(n)
FileList insert_listNode(FileList ListNode, char *fileName, 
                         int numWordFile, int termCount) 
{
    FileList newNode = create_listNode(fileName, numWordFile, termCount);
    //Consider if List is empty
    if (ListNode == NULL) {
        return newNode;
    }
    //Consider if inserting before the head
    if (strcmp(fileName, ListNode->filename) < 0) {
        newNode->next = ListNode;
        return newNode;
    }
    FileList curr = ListNode->next;
    FileList prev = ListNode;

    while (curr != NULL && strcmp(fileName, curr->filename) >= 0) {
        //Don't add identical filenames
        if (strcmp(fileName, curr->filename) == 0) {
            free(newNode);
            return ListNode;
        }

        prev = curr;
        curr = curr->next;
    }
    //Do not add identical filenames
    if (strcmp(fileName, prev->filename) == 0) {
        free(newNode);
        return ListNode;
    }
    prev->next = newNode;
    newNode->next = curr;
    
    //Return the head
    return ListNode;
}

//Print out the index, when tree is complete. Index cannot be NULL. 
//This was covered by the cases above
void print_list(FileList ListNode) {

    FileList curr = ListNode;
    //Loop through each linked list
    while (curr != NULL) {
        //Print the tf (....) filename
        printf("%s (%lf) ", curr->filename, curr->tf);
        curr = curr->next;
    }
    printf("\n");
}

//Return the number of ListNodes
int ListNode_count(FileList ListNode) {
    if (ListNode == NULL) {
        return 0;
    }
    return ListNode_count(ListNode->next) + 1;
}


///////////////////////////////////////
//TfIdfNode functions

//A function that returns a new TfIdfList node
TfIdfList create_tilNode(FileList ListNode, double tfidf) {
    TfIdfList newNode = malloc(sizeof(struct TfIdfNode));
    newNode->tfIdfSum = tfidf;
    //Allocate memory for the string
    newNode->filename = malloc(sizeof(char) * MAX_LENGTH);
    //Copy string
    strcpy(newNode->filename, ListNode->filename);
    //Make TfIdfList->null
    newNode->next = NULL;
    return newNode;
}

//A function that inserts a TfIdfList node
TfIdfList insert_tilNode(FileList ListNode, double tfidf) {
    TfIdfList newNode = create_tilNode(ListNode, tfidf);
    return newNode;
}

//Debugging function to print out the TfIdfList
void print_tilList(TfIdfList ListNode) {
    TfIdfList curr = ListNode;

    while (curr != NULL) {
        printf("%lf  %s", curr->tfIdfSum, curr->filename);
        printf("\n");
        curr = curr->next;
    }
}

//Copy a TfIdfList node
TfIdfList copy_tilNode(TfIdfList ListNode) {
    //Allocate memory for a node
    TfIdfList newNode = malloc(sizeof (struct TfIdfNode) );
    //copy the tfidfsum
    newNode->tfIdfSum = ListNode->tfIdfSum;
    //allocate memory for the string
    newNode->filename = malloc(sizeof(char) * MAX_LENGTH);
    //copy the string to the new node
    strcpy(newNode->filename, ListNode->filename);
    newNode->next = NULL;

    return newNode;
}

//A function that returns the number of nodes in tfIdf
//O(n)
int tilNode_count(TfIdfList ListNode) {
    if (ListNode == NULL) {
        return 0;
    }
    return tilNode_count(ListNode->next) + 1;
}

//TODO
//Create a function that frees memory for the tilNode
TfIdfList rm_tilNode(TfIdfList ListNode) {
    //Base case
    if (ListNode->next == NULL) {
        free(ListNode->filename);
        free(ListNode);
        return NULL;
    }
    
    if (ListNode->next != NULL) {
        ListNode->next = rm_tilNode(ListNode->next);
    }
    free(ListNode->filename);
    free(ListNode);

    return NULL;
}