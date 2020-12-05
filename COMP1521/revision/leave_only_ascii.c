#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main (int argc, char **argv) {
	
	FILE *f1 = fopen(argv[1], "r+");
	
	//Get the size of the file
	fseek(f1, 0, SEEK_END);
	long size = ftell(f1);
	int *buff = calloc(size, sizeof(int));
	
	//restore the pointer to the original position
	fseek(f1, 0, SEEK_SET);
	
	//Copy all ascii chars into an array
	int c = 0;
	int i = 0;
	while ((c = fgetc(f1)) != EOF) {
		if (isascii(c)) {
			buff[i] = c;
			i +=1;
		}
	}
	fclose(f1);
	
	//Replace the file with ascii bytes
	FILE *f2 = fopen(argv[1], "w");
	
	for (int j = 0; j < i; j +=1) {
		fputc(buff[j], f2);
	}

	fclose(f2);
	
	return 0;
}
