#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

int isVowel (char myChar) {
	if ( myChar == 'A' || myChar == 'E' || myChar == 'I' 
	|| myChar == 'O'
	|| myChar == 'U' || myChar == 'a' 
	|| myChar == 'e' || myChar == 'i' 
	||myChar == 'o' || myChar == 'u' 
	) {
		return 1;
	}
	return 0;
}

int main(void) {
	char myChar;
	char array[MAX_LENGTH];
	int i = 0;
	while (scanf("%c", &myChar) == 1) {
		if (isVowel(myChar) == 0) {
			array[i] = myChar;
			i++;
		}
	}
	array[i] = '\0';
	
	for (int k = 0; k < i; k++) {
	    printf("%c", array[k]);
	}
	return 0;
}

