#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>


///////A prototype research program that implements normaliseWord
char *normaliseWord (char *str);
char *toLower (char *str);
char *removeSpace (char *str);

int main () {
	//char original[1000];
	char *original;
	char *token, *theRest;
	//FILE *pFile = fopen("COMP1010.txt", "r");
	/*
	while (fscanf(pFile, "%s", original) == 1) {
		printf("%s \n", original);
	}
	*/
	original = strdup("Dogs, Cats, Lions, Cows????, Goats, Seals!?");
	
	theRest = original;
	token = toLower(strtok_r(original, ",", &theRest));
	while (token != NULL) {
		printf("Token: %s\n", token);
		token = toLower( 
				strtok_r(NULL, ", ", &theRest)
				);
	}

}
/*
char *normaliseWord(char *str) {
	
	tolower(
	
	
}
*/
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
			str[i] = str[count];
			count +=1;
		}
	}
	//Null terminate the string
	str[count] = '\0';
	return str;
}

//
char *removeEndPunct (char *str) {
	if (str == NULL) {
		return '\0';
	}
	int length = strlen(str);
	int i = 0;
	while (i <= length) {
		i +=1;
	}
	if (str[i] != '?' && str[i] != '.' 
		&& str[i] != ',' && str != ';') {
		
		str[i] = '\0';	
	}
	return str;
}

































