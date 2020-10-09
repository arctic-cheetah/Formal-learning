//Implementation functions for invertedIndexF.c and treeF.c
#ifndef _MYHEADER_GUARD
#define _MYHEADER_GUARD

#include "invertedIndex.h"
//Jeremy shortened the pointer to invertedIndexNode
typedef struct InvertedIndexNode *tree;

//Helper functions for normaliseWord
char *toLower (char *str);
char *removeSpace (char *str);
char *removeEndPunct (char *str);

//Tree functions exist here
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
TfIdfList rm_tilNode(TfIdfList ListNode);
TfIdfList copy_tilNode(TfIdfList ListNode);
void print_tilList(TfIdfList ListNode);
int tilNode_count(TfIdfList ListNode);

#endif
