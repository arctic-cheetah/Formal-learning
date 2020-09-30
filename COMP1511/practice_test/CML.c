#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 1023

int main (int argc, char *argv[] ) {
	char myString[MAX_LENGTH][MAX_LENGTH];
	for (int i = 1; i < argc; i++) {
		strcpy(myString[i], argv[i]);
		//printf("The length of sentence number %d is %lu\n", i, strlen(myString[i]) );
	}
	for (int i = 1; i < argc; i++) {
		printf ("%s\n", myString[i]);
		//fputs(myString[i], stdout);
		//printf("\n");
	}
	printf ("%d\n", argc);
	
	return 0;
}














































