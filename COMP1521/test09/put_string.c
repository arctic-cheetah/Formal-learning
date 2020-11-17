#include <stdio.h>

#include "put_string.h"

// print s to stdout with a new line appended using fputc (only)

void put_string(char *s) {
	
	//Get the length of the string
	int i = 0;
	while (s[i] != '\0') {
		fputc(s[i], stdout);
		i +=1;
	}
	fputc('\n', stdout);
}
