#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <string.h>

#define MAX_LENGTH 1023

void print_lower (char word[]);

int main (int argc, char *argv[] ) {
	
	int i = 1;
	while (i < argc) {
		print_lower(argv[i]);
		fputs(argv[i], stdout);
		printf(" ");
		i++;
	}
	printf("\n");
	return 0;
}

void print_lower (char word[]) {
	int stringLength = strlen(word);
	int i = 0;
	while (*word != '\0' && i < stringLength ) {
		word[i] = tolower(word[i]);
		i++;
	}
	
}














































