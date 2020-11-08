#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define LOW8BIT 0xFF
#define UPP8BIT 0xFF00

int main (int argc, char **argv) {
	if (argc < 2) {
		printf("Less than 2 arguments!\n");
		return 0;
	}
	
	FILE *output = fopen(argv[1], "w+");
	
	int begin = atoi(argv[2]);
	int end = atoi(argv[3]);
	
	
	while (begin <= end) {
		//extract lower 8 bits
		uint32_t j = begin & LOW8BIT;
		//extract upper 8 bits
		uint32_t i = (begin & UPP8BIT) >> 8;
		//printf("%d %d\n", i, j);
		fprintf(output, "%c", i);
		fprintf(output, "%c", j);
		begin +=1;
	}
	
	
	fclose(output);
}
