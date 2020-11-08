//A program which creates a file and outputs a range of numbers
#include <stdio.h>
#include <stdlib.h>


int main (int argc, char **argv) {
	if (argc < 3) {
		printf("Less than 3 arguments entered!\n");
		return 0;
	}
	FILE *output = fopen(argv[1], "w+");
	
	if (output == NULL) {
		perror(argv[1]);
		return 1;
	}
	
	int begin = atoi(argv[2]);
	int end = atoi(argv[3]);
	
	while (begin <= end) {
		fprintf(output, "%d\n", begin);
		begin +=1;
	}
	
	
	fclose(output);
} 



