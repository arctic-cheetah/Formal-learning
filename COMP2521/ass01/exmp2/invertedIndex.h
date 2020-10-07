// COMP2521 Assignment 1
// DO NOT MODIFY THIS FILE

#ifndef _INVERTEDINDEX_GUARD
#define _INVERTEDINDEX_GUARD

struct FileListNode {
	char *filename;
	double tf; // relative tf
	struct FileListNode *next;
};
typedef struct FileListNode *FileList;

struct InvertedIndexNode {
	char *word; // key
	struct FileListNode *fileList;
	struct InvertedIndexNode *left;
	struct InvertedIndexNode *right;

};
typedef struct InvertedIndexNode *InvertedIndexBST;
typedef struct InvertedIndexNode *tree;

struct TfIdfNode {
	char *filename;
	double tfIdfSum; // tfidf sum value
	struct TfIdfNode *next;
};
typedef struct TfIdfNode *TfIdfList;

// Functions for Part 1

/**
 * Normalises a given string. See the spec for details. Note: you should
 * modify the given string - do not create a copy of it.
 */
char *normaliseWord(char *str);

/**
 * This function opens the collection file with the given name, and then
 * generates an inverted index from those files listed in the collection
 * file,  as  discussed  in  the spec. It returns the generated inverted
 * index.
 */
InvertedIndexBST generateInvertedIndex(char *collectionFilename);

/**
 * Outputs  the  given inverted index to a file named invertedIndex.txt.
 * The output should contain one line per word, with the  words  ordered
 * alphabetically  in ascending order. Each list of filenames for a word
 * should be ordered alphabetically in ascending order.
*/
void printInvertedIndex(InvertedIndexBST tree); 

// Functions for Part-2

/**
 * Returns  an  ordered list where each node contains a filename and the 
 * corresponding tf-idf value for a given searchWord. You only  need  to
 * include documents (files) that contain the given searchWord. The list
 * must  be  in  descending order of tf-idf value. If there are multiple
 * files with same  tf-idf  value,  order  them  by  their  filename  in
 * ascending order.
*/
TfIdfList calculateTfIdf(InvertedIndexBST tree, char *searchWord, int D);

/**
 * Returns  an  ordered list where each node contains a filename and the
 * summation of tf-idf values of all the matching search words for  that
 * file.  You only need to include documents (files) that contain one or
 * more of the given search words. The list must be in descending  order
 * of summation of tf-idf values (tfIdfSum). If there are multiple files
 * with  the  same tf-idf sum, order them by their filename in ascending
 * order.
 */
TfIdfList retrieve(InvertedIndexBST tree, char *searchWords[], int D);


//Helper functions for normaliseWord
char *toLower (char *str);
char *removeSpace (char *str);
char *removeEndPunct (char *str);

//Tree functions exists here
tree create_treeNode(char *str);
tree insert_treeNode(char *str, char *fileName,
					 int numWordFile, int termCount , tree t);
tree search_tree(tree t, char *word);
//Tree balancing functions here
tree tree_balance(tree t);
tree right_rotation(tree t);
tree left_rotation(tree t);
int tree_height(tree t);
int height_diff(tree t);

//FileListNode functions
FileList create_listNode(char *fileName, int numWordFile, 
						 int termCount);
FileList insert_listNode(FileList ListNode, char *fileName, 
						 int numWordFile, int termCount);
void print_list(FileList ListNode);
int ListNode_count(FileList ListNode);
void sortArray(FileList *myArray, int length);

//TfIdfNode functions
TfIdfList create_tilNode(FileList ListNode, double tfidf);
TfIdfList insert_tilNode(FileList ListNode, double tfidf);
TfIdfList copy_tilNode(TfIdfList ListNode);
void print_tilList(TfIdfList ListNode);
TfIdfList rm_tilNode(TfIdfList ListNode);
int tilNode_count(TfIdfList ListNode);






#endif
