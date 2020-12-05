#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
	if (argc != 2) {
		printf("Incorrect number of arguments");
	}
	
	FILE *f1 = fopen(argv[1], "w");
	if (!f1) {
		perror("");
		exit(1);
	}
	
	int c = 0;
	while ( (c = fgetc(stdin)) != EOF) {
		if (c == '\n') {
			break;
		}
		fputc(c, f1);
	}
	
	fclose(f1);
	return 0;
}
