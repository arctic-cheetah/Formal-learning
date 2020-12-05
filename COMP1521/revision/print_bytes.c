#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main (int argc, char **argv) {
	
	if (argc != 2) {
		printf("Incorrect number of arguments\n");
		exit(1);
	}
	
	FILE *f1 = fopen(argv[1], "r");
	long counter = 0;
	int c = 0;
	while (( c = fgetc(f1) ) != EOF) {
		fprintf(stdout, "byte %4ld: %3d 0x%02x ", counter, c, c);
		if (isprint(c)) {
			fprintf(stdout, "'%c'\n", c);
		}
		else {
			printf("\n");
		}
		counter +=1;
	}
	
	fclose(f1);
	return 0;
}
