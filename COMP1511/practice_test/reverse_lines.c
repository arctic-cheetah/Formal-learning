//This is an improved version of reverse lines.c
//In preparation for the COMP1511 exam
//z5312813 Jeremy Mang
//27/04/2020

#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 1023

int main () {
	char word[MAX_LENGTH];
	while (fgets(word, MAX_LENGTH, stdin) != NULL){	
		int wordLen = strlen(word);
		for (int i = wordLen - 2; i >= 0; i--) {
			printf("%c", word[i]);
		}
		printf("\n");
	}
}








































