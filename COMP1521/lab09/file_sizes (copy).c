#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>


int main (int argc, char **argv) {
	if (argc < 2) {
		fprintf(stderr, "Not enough arguments\n");
		exit(1);
	}
	struct stat s;
	int i = 1;
	uint64_t sum = 0;
	while (i < argc) {
		if (stat(argv[i], &s) ) {
			perror("Error: ");
			exit(1);
		} 
		sum +=s.st_size;
		printf("%s: %ld bytes\n",argv[i], s.st_size);
		
		i +=1;
	}
	printf("Total: %lu bytes\n", sum);

}
