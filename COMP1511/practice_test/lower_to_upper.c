#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 1023

void print_upper (char word[]);

int main (int argc, char *argv[] ) {
	
	int wordCount = argc;
	for (int i = 1; i < wordCount; i++) {
		print_upper(argv[i]);
	}
	for (int i = 1; i < wordCount; i++) {
		fputs(argv[i], stdout);
		printf(" ");
	}
	printf("\n");

	return 0;
}

void print_upper (char word[]) {
	
	int i = 0;
	while (word[i] != '\0') {
		word[i] = toupper(word[i]);
		i++;
	}
	
}











































