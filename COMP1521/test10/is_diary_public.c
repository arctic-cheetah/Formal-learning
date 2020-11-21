#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_LENGTH 0xFFFFF

int main (int argc, char **argv) {
	char *pathName = calloc(MAX_LENGTH, sizeof(char));
	strcpy(pathName, getenv("HOME"));
	strcat(pathName, "/.diary");
	
	FILE *f = fopen(pathName, "r");
	//Check if the file exists
	if (f == NULL) {
		printf("0\n");
		return 0;
	}
	fclose(f);
	
	struct stat value;
	stat(pathName, &value);
	if ((value.st_mode & (S_IROTH)) &&
		(value.st_mode & (S_IRGRP)) ) {
		printf("1\n");
	}
	else {
		printf("0\n");
	}
	
	free(pathName);
}	
