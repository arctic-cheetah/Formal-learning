//A program encrypts texts using letter substitution
//By Jeremy Mang z5312813, with assistance from Alex Brown and Jasper DiFrancio.
// 02/04/2020

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX_LENGTH 26

int encrypt (int key[MAX_LENGTH], int keyChar);


int main() {
	
	int keyChar = getchar();
	int key[MAX_LENGTH] = {}; // This stores the key as an array
	
	for (int i = 0; i < MAX_LENGTH && keyChar != EOF; i++){//This takes in a character of a key And saves it in an array
		key[i] = keyChar - 'a'; //Get the position number of the alphabet
		keyChar = getchar();
	}
	
	keyChar = getchar();
	
	while (keyChar != EOF){//This takes in a sentence	
		int phrase = encrypt(key, keyChar);
		
		putchar(phrase);//print the encrypted letter of the phrase
		keyChar = getchar();	
	}
	
	return 0;
}


int encrypt (int key[MAX_LENGTH], int keyChar){
	
	if('A' <= keyChar && keyChar <= 'Z'){
		int remainder = keyChar - 'A';
		return keyChar = key[remainder] + 'A';
	
	}
	else if ('a' <= keyChar && keyChar <= 'z'){
		int remainder = keyChar - 'a';
		return keyChar = key[remainder] + 'a';
	}
	else{
		return keyChar;
	}
}
























