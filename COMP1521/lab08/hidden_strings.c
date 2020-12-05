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



/*

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
*/
