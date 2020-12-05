#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
	
	if (argc != 4) {
		printf("Incorrect arguments entered\n");
		exit(1);
	}
	FILE *f1 = fopen(argv[1], "w");
	int begin = atoi(argv[2]);
	int end = atoi(argv[3]);
	
	while (begin <= end) {
		fprintf(f1, "%d\n", begin);
		begin +=1;
	}
	
	fclose(f1);
	return 0;
}
