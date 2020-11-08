#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>

int main (int argc, char **argv) {
	if (argc < 2) {
		printf("Insufficient arguments!\n");
		exit(1);
	}
	
	FILE *text = fopen(argv[1], "r");
	if (text == NULL) {
		printf("The text was null!\n");
		exit(1);
	}
	fseek(text, 0, SEEK_END);
	long size = ftell(text) - 1;  // Exclude EOF
	long backup = size;
	//printf("The size of the file is: %ld\n", size);
	
	//Return the file pointer to the beginning
	fseek(text, 0, SEEK_SET);
	
	//Check if the last character is a newline
	fseek(text, size, SEEK_SET);
	int c = fgetc(text);
	int c1 = 0;

	if (c == '\n') {
		size -=1;
		c = 0;
	}
	
	//Warning, at bytes may not begin from 0
	
	while (size >= 0 && c != '\n') {
		fseek(text, size, SEEK_SET);
		c = fgetc(text);
		
		size -=1;
	}
	size +=1;
	//Don't include the second "\n"
	if (c == '\n') {
		size +=1;
	}
	
	fseek(text, size, SEEK_SET);
	while (size <= backup && (c1 = fgetc(text)) != EOF) {
		putchar(c1);
		size +=1;
	}
	fclose(text);
}




