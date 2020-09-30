#include <stdio.h>

#define MAX_LENGTH 1023

int main () {
	
	char str [MAX_LENGTH]; 
	int PalindromeCheck = 1;
	printf("Enter a string: ");
	scanf("%s", str);
	
	int k = 0;
	//Get the length of the string
	while (str[k] != '\0') {
		k++;
	}
	k--;
	//Loop through the front and rear end of the array
	int j = 0;
	while (str[j] != '\0') {
	//Check if the characters are identical
	
	if (str[j] != str[k]) {
		PalindromeCheck = 0;
		break;
	}
	//Else, break from the loop and return false
		k--;
		j++;
	}
	
	if (PalindromeCheck == 1) {
		printf("The string is a palindrome\n");
	}
	else {
		printf("The string is not a palindrome\n");
	}
	
}
























































