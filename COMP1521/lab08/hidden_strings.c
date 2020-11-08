#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>

int main (int argc, char **argv) {
	if (argc < 2) {
		perror("Not enough parameters!\n");
		return 0;
	} 
	
	FILE *input = fopen(argv[1], "r");
	if (input == NULL) {
		perror("File is NULL!\n");
		return 0;
	}
	 
	uint32_t c = 0;
	int buffer[3] = {0};
	int size = 0;
	while ((c = fgetc(input)) != EOF) {
	
		if (isprint(c) && size < 3) {
			buffer[size] = c;
			size +=1; 
		}
		//3 characters in a row
		else if (size == 3 && isprint(c)) {
			//print the contents of the buffer
			for (int i = 0; i < 3; i +=1) {
				putchar(buffer[i]);
			}
			putchar(c);
			
			while (isprint(c) && ((c = fgetc(input)) != EOF)) {
				if (isprint(c)) {
					putchar(c);
				}
			}
			
			if (!isprint(c)) {
				putchar('\n');
			}
			
			//Empty the buffer
			size = 0;
			for (int i = 0; i < 3; i +=1) {
				buffer[i] = 0;
			}
		}
		else {
			//Empty the buffer
			size = 0;
			for (int i = 0; i < 3; i +=1) {
				buffer[i] = 0;
			}
		} 
		
		
	}
	fclose(input);	
}
