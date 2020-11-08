#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int main (int argc, char **argv) {
	
	if (argc < 2) {
		perror("Not enough arguments!\n");
		exit(1);
	}
	
	FILE *text = fopen(argv[1], "r");
	
	if (text == NULL) {
		perror("FILE WAS NULL!\n");
		exit(1);
	}
	int i = 0;
	int c = 0;
	int isAscii = 1;
	while ((c = fgetc(text)) != EOF) {
		if (!isascii(c)) {
			isAscii = 0;
			break;
		}
		i +=1;
	}
	
	if (isAscii) {
		printf("%s is all ASCII\n", argv[1]);
	}
	else {
		printf("%s: byte %d is non-ASCII\n", argv[1], i);
	} 
	
	
	
	fclose(text);
}

























