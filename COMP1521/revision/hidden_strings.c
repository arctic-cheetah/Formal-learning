//A program which creates a file and outputs a range of numbers
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int main (int argc, char **argv) {
	if (argc != 2) {
		printf("Incorrect arguments\n");
		return 0;
	}
	FILE *f1 = fopen(argv[1], "r");
	
	if (f1 == NULL) {
		perror(argv[1]);
		return 1;
	}
	char buffer[5] = {0};
	int c = 0;
	int bufferCount = 0;
	while ((c = fgetc(f1)) != EOF) {
		
		//Add consecutive characters to the buff
		if (isprint(c)) {
			buffer[bufferCount] = c;
			bufferCount +=1;
		}
		//Otherise, reset the buffer
		else {
			bufferCount = 0;
		}
		//print the buffer
		if (bufferCount == 4) {
			fprintf(stdout, "%s", buffer);
			
			//Check if there are consecutive printable characters remaining
			while ((c = fgetc(f1)) != EOF) {
				if (isprint(c)) {
					fputc(c, stdout);
				}
				else {
					break;
				}
			}
			
			printf("\n");
			bufferCount = 0;
		}
			
		
	}
	
	fclose(f1);
	return 0;
} 



