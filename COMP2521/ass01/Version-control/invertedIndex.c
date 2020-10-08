#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "invertedIndex.h"

#define MAX_LENGTH 100

///////////////////////////////////////////////////////////////////
//Part 1:
//Helper functions for normaliseWord

int main () {
	generateInvertedIndex("collection.txt");
}

char *toLower (char *str);
char *removeSpace (char *str);
char *removeEndPunct (char *str);
char *normaliseWord(char *str) {
	return removeSpace( removeEndPunct(toLower(str) ) );
}


//A function that makes a string to a lower case.
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
int file_term_count (FILE *fileRead, char *fileName); //O(n)

InvertedIndexBST generateInvertedIndex(char *collectionFilename) {
	FILE *file = fopen(collectionFilename, "r");
	char fileName[MAX_LENGTH];
	InvertedIndexBST root;

	//char word[MAX_LENGTH];
	//FILE *fileRead;
	int termCount = 0;
	while (fscanf(file, "%s", fileName) == 1) {
		printf("The words in %s are: \n", fileName);

		FILE *fileRead = fopen(fileName, "r");
		//Obtain the number of words in a file
		termCount = file_term_count(fileRead, fileName);
		/*
		while (fscanf(fileRead, "%s", word) == 1) {
			printf("%s\n", normaliseWord(word));
		}
		*/
	}

	return NULL;
}

//A function that reads the number of words in a file
int file_term_count (FILE *fileRead, char *fileName) {
	int termCount = 0;
	char word[MAX_LENGTH];
		//Need to count the number of terms in a document
		while (fscanf(fileRead, "%s", word) == 1) {
			printf("%s\n", normaliseWord(word));
			termCount +=1;
		}
		//Remove the scaffolding after prototyping!!!
		printf("----------------------------------\n");
		printf("The number of words file %s is: %d", fileName, termCount);
		printf("\n\n");
	return termCount;
}
/*
void printInvertedIndex(InvertedIndexBST tree); 

//////////////////////////////////////////////////////////////// //////
//Functions for Part-2
TfIdfList calculateTfIdf(InvertedIndexBST tree, char *searchWord, int D);
TfIdfList retrieve(InvertedIndexBST tree, char *searchWords[], int D);

*/













































































































































