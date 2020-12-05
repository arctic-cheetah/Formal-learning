#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main (int argc, char **argv) {
	if (argc != 2) {
		printf("Incorrect arguments");
		exit(1);
	}
	
	FILE *f1 = fopen(argv[1], "r");
	if (!f1) {
		perror("");
		exit(1);
	}
	
	//exclude EOF
	fseek(f1, -1, SEEK_END);
	long curr = ftell(f1);
	long size = ftell(f1) + 1;
	int c = fgetc(f1);
	//Empty file
	if ( fseek(f1, -1, SEEK_END) == -1) {
		exit(1);
	}
	
	//Check if the last character is '\n'
	//Begin at n-2
	if (c == '\n') {
		curr -=1;
		fseek(f1, curr, SEEK_SET);
		c = fgetc(f1);
	}
	
	
	//Loop until '\n' or curr <= 0
	while (c != '\n' && curr > 0 && c != EOF) {
		curr -=1;
		fseek(f1, curr, SEEK_SET);
		c = fgetc(f1);
	}
	//begin beyond the '\n'
	if (c == '\n') {
		curr +=1;
		fseek(f1, curr, SEEK_SET);
		c = fgetc(f1);
	}
	
	while (curr < size) {
		fputc(c, stdout);
		c = fgetc(f1);
		curr +=1;
	}
	

}

























