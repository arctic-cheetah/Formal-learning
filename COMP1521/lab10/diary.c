#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 0xFFFFF


int main (int argc, char **argv) {
	if (argc < 2) {
		perror("Not enough arguments");
		exit(1);
	}
	char *value = calloc(MAX_LEN, sizeof(char));
	strcpy(value, getenv("HOME"));
	char *path = strcat(value, "/.diary");
	FILE *f = fopen(path, "a");
	
	for (int k = 1; k < argc; k +=1) {
		fprintf(f,"%s ", argv[k]);
	}
	fprintf(f, "%s" ,"\n");
	free(value);
	
	return 0;
}
