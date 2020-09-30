#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 1023

int main () {
	char word[MAX_LENGTH];
	char wordStore[MAX_LENGTH][MAX_LENGTH];
	int lines = 0;
	while (fgets (word, MAX_LENGTH, stdin) != NULL) {
		int sameCount = 0;
		
		for (int i = lines; i >= 0; i--) {
			if (strcmp(wordStore[i], word) == 0) {
				sameCount = 1;
			}
		}
		if (sameCount != 1) {
			fputs(word, stdout);
			strcpy(wordStore[lines], word);
			lines++;
		}
	}		
}




































