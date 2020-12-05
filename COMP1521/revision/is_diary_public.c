#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main () {
	//Get a copy of the HOME var string
	//Including '\0'
	
	//Fetch sufficient memory for the pathname
	int len = strlen(getenv("HOME")) + strlen("/.diary") + 1;
	char *c = calloc(len, sizeof(char));
	strcpy(c, getenv("HOME"));
	
	//Append /.diary to the pathname
	char *pathName = strcat(c, "/.diary");
	
	struct stat path;
	if( stat(pathName, &path) != 0) {
		printf("0\n");
		return 0;
	}
	
	if ((path.st_mode & S_IRGRP) && (path.st_mode & S_IROTH)) {
		printf("1\n");
	}
	else {
		printf("0\n");
	}
	return 0;
}
