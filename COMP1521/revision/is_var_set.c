#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char **argv) {
	
	char *c = getenv(argv[1]);
	//Check if env variable exists
	if (c == NULL) {
		printf("0\n");
		return 0;
	}
	//Check the for empty string
	if (strlen(c)) {
		printf("1\n");
	}
	else {
		printf("0\n");
	}
	return 0;
}	
