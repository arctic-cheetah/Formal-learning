#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main (int argc, char **argv) {
	
	if (argc < 2) {
		printf("Incorrect number of arguments\n");
		exit(1);
	}
	
	FILE *f1 = fopen(argv[1], "w");
	int i = 2;
	int c = 0;
	while (i < argc) {
		c = atoi(argv[i]);
		fputc(c, f1);
		i +=1;
	}
	
	fclose(f1);
	return 0;
}
