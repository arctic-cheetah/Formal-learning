#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "invertedIndex.h"

#define MAX_LENGTH 100

int main () {
	tree t = generateInvertedIndex("collection.txt");
	printInvertedIndex(t);
}
///////////////////////////////////////////////////////////////////
//Part 1:
//Helper functions for normaliseWord
char *toLower (char *str);
char *removeSpace (char *str);
char *removeEndPunct (char *str);

//Normalise word is a destructive function...
char *normaliseWord(char *str) {
	return removeSpace( removeEndPunct(toLower(str) ) );
}


//A function that makes a string to a lower case.
//O(n)
char *toLower (char *str) {
	int length = strlen(str);
	for (int i = 0; i < length; i +=1) {
		if ('A' <= str[i] && str[i] <= 'Z') {
			str[i] = str[i] + 32;
		}	
	}
	return str;
}

//This function removes any whitespace
//O(n)
char *removeSpace (char *str) {

	int count = 0;
	for (int i = 0; str[i]; i +=1) {
		if (str[i] != ' ') {
			str[count] = str[i];
			count +=1;
		}
	}
	//Null terminate the string
	str[count] = '\0';
	return str;
}

//A function that only removes a punctuation at the end of the word
//O(1)
char *removeEndPunct (char *str) {

	int i = strlen(str) - 1; //O(n)
	
	if (str[i] == '?' || str[i] == '.' 
		|| str[i] == ',' || str[i] == ';') {	
		str[i] = '\0';	
	}
	return str;
}
////////////////////////////////////////////////////////////////////////////
//Helper functions for InvertedIndexBST
int file_term_count (char *fileName); //O(n)
int specific_word_count (char *fileName, char *word); //O(n * k)

InvertedIndexBST generateInvertedIndex(char *collectionFilename) {
	FILE *file = fopen(collectionFilename, "r");
	char fileName[MAX_LENGTH];
	InvertedIndexBST root = NULL;
	char word[MAX_LENGTH];
	char NormWord[MAX_LENGTH];
	//FILE *fileRead;
	int termCount = 0;
	int numWordFile = 0;
	while (fscanf(file, "%s", fileName) == 1) {
		//printf("The words in %s are: \n", fileName);
		FILE *fileRead = fopen(fileName, "r");

		//ISSUE---------------------------------------------
		if (fileRead == NULL) {
			printf("File read pointer was null by %s\n", fileName);
			return NULL;
		}
		//---------------------------------------------------

		//Obtain the number of words in a file
		termCount = file_term_count(fileName);

		//Input words into a tree
		while (fscanf(fileRead, "%s", word) == 1) {
			strcpy(NormWord, normaliseWord(word));
			//Count the number of words in the file
			numWordFile = specific_word_count(fileName,
			 NormWord);
			root = insert_treeNode(NormWord, fileName, 
									numWordFile, termCount, root);
		}
		fclose(fileRead);
	}
	return root;
}

//A function that reads the number of words in a file
int file_term_count (char *fileName) {
	FILE *fileRead = fopen(fileName, "r");
	int termCount = 0;
	char word[MAX_LENGTH];
		//Need to count the number of terms in a document
		while (fileRead != NULL && fscanf(fileRead, "%s", word) == 1) {
			termCount +=1;
		}
	fclose(fileRead);
	return termCount;
}
//A function that returns the quantity of occurences of a word in a file
int specific_word_count (char *fileName, char *word) {
	int numWordFile = 0;
	FILE *fileRead = fopen(fileName, "r");
	char currWord[MAX_LENGTH];
		//Need to count the number of terms in a document
		while (fileRead != NULL && fscanf(fileRead, "%s", currWord) == 1) {
			//only add if normalised currWord is equal to the word
			if (strcmp(word, normaliseWord(currWord) ) == 0) {//O(k)
				numWordFile +=1;
			}
		}
	fclose(fileRead);
	return numWordFile;
}


//Print the inverted index using inorder traversal
void printInvertedIndex(tree t) {
	if (t != NULL) {
	//Print the tree using infix
	printInvertedIndex(t->left);
	//Print the word
	printf("%s ", t->word);
	print_list(t->fileList);
	printInvertedIndex(t->right);
	}

}
/*
//////////////////////////////////////////////////////////////// //////
//Functions for Part-2
TfIdfList calculateTfIdf(InvertedIndexBST tree, char *searchWord, int D);
TfIdfList retrieve(InvertedIndexBST tree, char *searchWords[], int D);

*/











































