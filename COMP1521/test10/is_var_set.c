#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char **argv) {
	//Get the environment variable
	char *env = getenv(argv[1]);
	if(env && strlen(env)) {
		printf("1\n");
	}
	else {
		printf("0\n");
	}
}	
