//A program that excludes odd lines from an input

#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 1023

int main(void) {
	
	char array[MAX_LENGTH][MAX_LENGTH];
	int i = 0;
	while (fgets(array[i], MAX_LENGTH, stdin) != NULL) {
		if (!(strlen(array[i]) & 1) ) {
			fputs(array[i], stdout);
		}
		i++;
	}
	
}
