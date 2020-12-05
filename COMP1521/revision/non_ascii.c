#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main (int argc, char **argv) {
	
	FILE *f1 = fopen(argv[1], "r");
	
	int c = 0;
	int curr = 0;
	int isAscii = 1;
	while ((c = fgetc(f1)) != EOF) {
		if (!isascii(c)) {
			isAscii = 0;
			break;
		}
		curr +=1;
	}
	
	if (isAscii) {
		printf("%s is all ASCII\n", argv[1]);
	}
	else {
		printf("%s: byte %d is non-ASCII\n", argv[1], curr);
	}
	fclose(f1);
	
	return 0;
}
