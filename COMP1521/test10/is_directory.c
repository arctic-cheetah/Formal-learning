#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


int main (int argc, char **argv) {
	
	struct stat pathName;
	if (stat(argv[1], &pathName) == -1) {
		printf("0\n");
		return 0;
	}
	
	if(pathName.st_mode & S_IFDIR) {
		printf("1\n");
	}
	else {
		printf("0\n");
	}
}	
