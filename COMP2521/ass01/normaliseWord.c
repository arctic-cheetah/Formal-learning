#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>


///////A prototype research program that implements normaliseWord
char *normaliseWord (char *str);
char *toLower (char *str);
char *removeSpace (char *str);
char *removeEndPunct (char *str);

int main () {
	//char original[1000];
	char *original;
	//FILE *pFile = fopen("COMP1010.txt", "r");
	/*
	while (fscanf(pFile, "%s", original) == 1) {
		printf("%s \n", original);
	}
	*/
	original = strdup("HTTPs.com.au.");
	original = removeSpace( removeEndPunct(toLower(original) ) );
	
	printf("%s\n", original);
	
}

char *normaliseWord(char *str) {
	return removeSpace( removeEndPunct(toLower(str) ) );
}


//A function that makes a string to a lower case.
char *toLower (char *str) {
	if (str == NULL) {
		return '\0';
	}
	int length = strlen(str);
	for (int i = 0; i < length; i +=1) {
		if ('A' <= str[i] && str[i] <= 'Z') {
			str[i] = str[i] + 32;
		}	
	}
	return str;
}

//This function removes any whitespace
char *removeSpace (char *str) {
	if (str == NULL) {
		return '\0';
	}
	int count = 0;
	for (int i = 0; str[i]; i +=1) {
		if (str[i] != ' ') {
			str[count] = str[i];
			count +=1;
		}
	}
	//Null terminate the string
	str[count] = '\0';
	return str;
}

//A function that only removes a punctuation at the end of the word
char *removeEndPunct (char *str) {
	if (str == NULL) {
		return '\0';
	}
	int i = strlen(str) - 1; //O(n)
	
	if (str[i] == '?' || str[i] == '.' 
		|| str[i] == ',' || str[i] == ';') {	
		str[i] = ' ';	
	}
	return str;
}

































