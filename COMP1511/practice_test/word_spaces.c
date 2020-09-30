#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1023

int main () {
	
	char word[MAX_LENGTH];
	printf("Enter a string: ");
	fgets(word, MAX_LENGTH, stdin);
	int wordLength = strlen(word) - 1;
	for (int i = 0; i < wordLength; i++) {
		printf("%c", word[i]);
		printf(" ");
	}
	printf("\n");
	
	return 0;
}


































