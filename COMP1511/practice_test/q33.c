#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 1023
int main () {
	char word[MAX_LENGTH];
	
	printf("Enter a string: ");
	scanf("%s", word);
	int wordLen = strlen(word);
	char wordCheck[wordLen];
	int Duplicate = 0;
	printf("The count of each letter is: \n");
	for (int i = 0; i < wordLen; i++) {
		Duplicate = 0;
		int letter = word[i];
		wordCheck[i] = word[i];
		int letterCount = 0;
		for (int j = 0; j < wordLen; j++) {
			if (letter == word[j]) {
				letterCount++;
			}	
		}
		for (int k = 0; k < i; k++) {
			if (wordCheck[k] == word[i]) {
				Duplicate = 1;
			}
		}
		if (Duplicate != 1) {
			printf("%c       %d\n", letter, letterCount);
		}
	}


	return 0;
}




































