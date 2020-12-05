//A program that removes write permissions from the group and others
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main (int argc, char **argv) {
	
	if (argc < 2) {
		printf("Insufficient arguments!\n");
		exit(1);
	}
	
	for (int i = 1; i < argc; i +=1) {
		//Fetch the metadata of the file
		struct stat file;
		if (stat(argv[i], &file) == -1) {
			perror("");
			exit(1);
		}
		
		//Copy the permissions
		mode_t perm = file.st_mode;
		
		//Remove write permissions for group and others
		if (perm & (S_IWGRP | S_IWOTH)) {
			perm = perm ^ (S_IWGRP | S_IWOTH);
		}
		
		//Change the permissions of the file
		if (chmod(argv[i], perm) != 0) {
			perror("");
			exit(1);
		}
		
	}

}
