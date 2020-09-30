#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1023

void string_sort(char word[], int wordLen);

int main() {
	char word[MAX_LENGTH];
	printf("Enter a string: ");
	scanf("%s", word);
	int wordLen = strlen(word);
	
	string_sort(word, wordLen);
	
	printf("%s\n", word);
	
	return 0;
}

//Loops through a string and arranges them to ascending order
//by ASCII convention
void string_sort(char word[], int wordLen) {
	char Temp;
	int i = 1;
	//Loop through the array and store a character into a char variable
	//Then compare if the char variable is greater than in the source array
	//
	//and store it inside the destination array
	
	while (i < wordLen) {
		
		int k = 0;
		while (k < wordLen - i) {
			if (word[k] > word[k+1]) {
				Temp = word[k];
				word[k] = word[k+1];
				word[k+1] = Temp;
			}
			k++;
		}
		i++;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	/*
	while (i < wordLen) {
		
		int k = 0;
		while (k < wordLen - i) {
			if (word[k] > word[k+1]) {
				Temp = word[k];
				word[k] = word[k+1];
				word[k+1] = Temp;
			}
			k++;
		}
		//printf("%s", word);
		i++;
	}
	printf("%s", word);
	printf("\n");
	//printf("%s\n", sorted);
	*/
}








































