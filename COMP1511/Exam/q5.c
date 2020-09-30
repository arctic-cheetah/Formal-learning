#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 1024

int main (int argc, char *argv[]) {

	char wordArray[MAX_LENGTH][MAX_LENGTH];
	int wordCount[MAX_LENGTH] = {0};
	
	//Copy argv in word Array
	int wordArrayIndex = 0;
	int k = 1;
	while (k < argc) {
		//Check if argv strings are the same in word Array
		int j = 0;
		int isSame = 0;
		//Loop to through the entire word array to check if the strings are the same
		while (j < wordArrayIndex) {
			if (strcmp(wordArray[j], argv[k]) == 0) {
				isSame = 1;
				break;
			}
			//j will be the same index as the location of the same word!
			j++;	
		}
		
		//If they're different, add them to the wordArray
		if (isSame != 1) {
			strcpy(wordArray[wordArrayIndex], argv[k]);
			wordCount[wordArrayIndex]++;
			wordArrayIndex++;
		}
		//If they're the same, add them to number of current words
		else {
			wordCount[j]++;
		}
	
		k++;
	}
	//Loop through the wordCount
	int highNum = 0;
	for (int i = 0; i < wordArrayIndex; i++) {
		//Obtain the highest values
		if (wordCount[highNum] < wordCount[i]) {
			highNum = i;
		}
	}
	
	printf("%s\n", wordArray[highNum]);
	return 0;
}































































