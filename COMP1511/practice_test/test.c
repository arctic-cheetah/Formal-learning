#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 1023


int main () {
   int len;
   char str1[] = "ABCDEFG019874";
   char str2[] = "ABCDEF";

   len = strspn(str1, str2);

   printf("Length of initial segment matching %d\n", len );
   
   return(0);
}













/*
int main (int argc, char *argv[] ) {
	char myString[MAX_LENGTH][MAX_LENGTH];
	for (int i = 1; i < argc; i++) {
		strcpy(myString[i], argv[i]);
	}
	//fputs(myString, stdout);
	for (int i = 1; i < argc; i++) {
		printf ("%s\n", myString[i]);
	}
	printf ("%d\n", argc);
	
	return 0;
}
*/













































