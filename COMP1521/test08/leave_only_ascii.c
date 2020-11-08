

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int main (int argc, char **argv) {
	
	if (argc < 2) {
		perror("Not enough arguments!\n");
		exit(1);
	}
	
	FILE *text1 = fopen(argv[1], "r+");
	if (text1 == NULL) {
		perror("FILE WAS NULL!\n");
		exit(1);
	}
	long int i = 0;
	int c1 = 0;
	while ((c1 = fgetc(text1)) != EOF) {
		if (isascii(c1)) {
			i +=1;
		}
	}
	//Store the text in an array
	int *temp = malloc(i * sizeof(int));
	fseek(text1, 0, SEEK_SET);
	
	//Copy the contents of the file into an array
	int j = 0;
	c1 = 0;
	while ((c1 = fgetc(text1)) != EOF) {
		if (isascii(c1)) {
			temp[j] = c1;
			j +=1;
		}
	}
	
	fclose(text1);
	
	
	FILE *text2 = fopen(argv[1], "w+");
	if (text2 == NULL) {
		perror("FILE WAS NULL!\n");
		exit(1);
	}
	
	//Overwrite all the characters to be ascii characters
	j = 0;
	c1 = 0;
	while (j < i) {
		fputc(temp[j], text2);
		j +=1;
	}
	free(temp);
	fclose(text2);
}






