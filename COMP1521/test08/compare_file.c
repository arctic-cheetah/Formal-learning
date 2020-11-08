

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int main (int argc, char **argv) {
	
	if (argc < 3) {
		perror("Not enough arguments!\n");
		exit(1);
	}
	
	FILE *text1 = fopen(argv[1], "r");
	if (text1 == NULL) {
		perror("FILE WAS NULL!\n");
		exit(1);
	}
	FILE *text2 = fopen(argv[2], "r");
	if (text2 == NULL) {
		perror("FILE WAS NULL!\n");
		exit(1);
	}
	
	
	int i = 0;
	int c1 = 0;
	int c2 = 0;
	int isSame = 1;
	while ((c1 = fgetc(text1)) != EOF && (c2 = fgetc(text2)) != EOF) {
		if (c1 != c2) {
			isSame = 0;
			break;
		}
		i +=1;
	}
	c2 = fgetc(text2);
	
	if (isSame && c1 == EOF && c2 == EOF) {
		printf("Files are identical\n");
	} 
	else if (!isSame) {
		printf("Files differ at byte %d\n", i);
	}
	else if (c1 == EOF) {
		printf("EOF on %s\n", argv[1]);
	}
	else if (c2 == EOF) {
		printf("EOF on %s\n", argv[2]);
	} 
	
	
	
	fclose(text1);
	fclose(text2);
}






