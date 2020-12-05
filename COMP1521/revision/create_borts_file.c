#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define UPPERBYTE 0xFF00

int main (int argc, char **argv) {
	
	if (argc != 4) {
		printf("Incorrect arguments entered\n");
		exit(1);
	}
	FILE *f1 = fopen(argv[1], "w");
	uint32_t begin = atoi(argv[2]);
	uint32_t end = atoi(argv[3]);
	
	while (begin <= end) {
		//Put the upper bytes first
		uint32_t upperByte = begin >> 8;
		fprintf(f1, "%c", upperByte);
		uint32_t lowerByte = begin & 0xFF;
		fprintf(f1, "%c", lowerByte);
		
		begin +=1;
	}
	
	fclose(f1);
	return 0;
}
