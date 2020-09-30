#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 1023

int main () {

	char word[MAX_LENGTH];
	printf("Enter a string: ");
	fgets(word, MAX_LENGTH, stdin);
	int wordLength = strlen(word);
	int wordCount = 0;
	for (int i = 0; i < wordLength; i++) {
		if (word[i] == 32 || word[i] == 10) {
			wordCount++;
		}
	}
	printf("The number of words in the sentence: %d\n", wordCount);

	return 0;
}








































