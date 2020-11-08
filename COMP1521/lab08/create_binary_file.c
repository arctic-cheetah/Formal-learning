#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
	
	if (argc < 2) {
		printf("Less than 2 arguments!\n");
		return 0;
	}
	
	FILE *output = fopen(argv[1], "w+");
	
	if (output == NULL) {
		perror("Empty argument!\n");
		return 0;
	}
	
	int i = 2;
	while (i < argc) {
		fputc(atoi(argv[i]), output);
		i +=1;
	}
	
	
	fclose(output);
}
