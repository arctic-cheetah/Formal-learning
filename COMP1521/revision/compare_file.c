#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
	FILE *f1 = fopen(argv[1], "r");
	FILE *f2 = fopen(argv[2], "r");
	
	int c1 = 0;
	int c2 = 0;
	int curr = 0;
	int isDiff = 0;
	while ((c1 = fgetc(f1)) != EOF && (c2 = fgetc(f2)) != EOF) {
		if (c1 != c2) {
			isDiff = 1;
			break;
		}
		curr +=1;
	}
	//Check if c2 is EOF
	if (c1 == EOF) {
		c2 = fgetc(f2);
	}
	
	
	if (isDiff) {
		printf("Files differ at byte %d\n", curr);
	}
	else if (c1 == EOF && c2 != EOF) {
		printf("EOF on %s\n", argv[1]);
	}
	else if (c2 == EOF && c1 != EOF) {
		printf("EOF on %s\n", argv[2]);
	}
	else {
		printf("Files are identical\n");
	}
	
	
	fclose(f1);
	fclose(f2);
	return 0;
}
