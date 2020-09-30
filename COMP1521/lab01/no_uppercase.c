//A program that converts uppercase letters to lowercase

#include <stdio.h>
#include <ctype.h>

#define MAX_LENGTH 1023

int main(void) {
	int array[MAX_LENGTH];
	int c;
	int i = 0;
	while ( ( c = getchar() ) != EOF ) {
		if ('A' <= c && c <= 'Z') {
			c = c + 32;
		}
		array[i] = c;
		i++;
	}
	
	array[i] = '\0';
	
	for (int k = 0; k < i; k += 1) {
		putchar(array[k]);
	}
	
}






