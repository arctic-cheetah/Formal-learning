//A program which prints all the bytes of a file 
//in decimal and hexadecimal
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int main (int argc, char **argv) {
	if (argc < 1) {
		perror("Not enough arguments!\n");
		return 0;
	}
	FILE *input = fopen(argv[1], "r");
	if (input == NULL) {
		perror("No file!\n");
		return 0;
	}
	int c = 0;
	int i = 0;
	while ((c = fgetc(input)) != EOF) {
		printf("byte %4d: %3d 0x%02x ", i, c, c);
		if (isprint(c)) {
			printf("'%c'", c);
		}
		printf("\n");
		i +=1;
	}
	fclose(input);
}


