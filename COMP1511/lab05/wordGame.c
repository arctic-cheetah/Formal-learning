//A word game in the halfway point of COMP1511
//Jeremy z5312813

//29/03/2020

//Reads in a string of charaacters
//Reads another string
//Checks how many letters are in the second string
//present in the first string
//Reports how many is matched


#include <stdio.h>

#define MAX_LINE_LENGTH 1023

int testChar(char single, char line[MAX_LINE_LENGTH]);
int numLetterMatches(char *word, char *line);

int main(){
	
	char line[MAX_LINE_LENGTH];
	//read in a line of text
	fgets(line, MAX_LINE_LENGTH, stdin);
	
	//read in a single character
	int inputChar;
	inputChar = getchar();
	
	while(inputChar != EOF){
		
		int count = testChar (inputChar, line);
		printf("There was %c , %d times in the line.\n", inputChar, count);
		inputChar = getchar();
		
	}
	
	//Find how many times inputChar is in the line
	int count = testChar (inputChar, line);
	printf("There was %c , %d times in the line.\n", inputChar, count);

	return 0;
}

// Find a character in a line
// Return how many times that character appears in a line
int testChar(char single, char line[MAX_LINE_LENGTH]){
	int i = 0;
	int count = 0;
	while (i < MAX_LINE_LENGTH && line[i] != '\0'){//processed i characters
		if(single == line[i]){
			count++;
		}
		i++;
	}// processed i charcters total, seen single count times
	
	return count;
}


int numLetterMatches(char *word, char *line) {
	 int i = 0;
	 int matchCount = 0;
	 while (i < MAX_LINE_LENGTH && word[i] != '\0') {
	 	if (testChar(word[i], line)) {
	 		matchCount++;
	 	}
	 	i++;
	 }
	 return matchCount;
}































