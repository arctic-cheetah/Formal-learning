//A program which decodes substitution.c
//By Jeremy Mang z5312813, with assistance from Alex Brown.
// 03/04/2020

#include <stdio.h>

#define MAX_LENGTH 26

int decrypt(int key[MAX_LENGTH], int keyChar);
int Offset(int key[MAX_LENGTH], int remainder);

int main(){

	int keyChar = getchar();
	int key[MAX_LENGTH] = {};
	
	for(int i = 0; i < MAX_LENGTH ;i++){
		key[i] = keyChar - 'a';	
		keyChar = getchar();
	}
	
	keyChar = getchar();
	while (keyChar != EOF){
		int letter = decrypt(key, keyChar);
		putchar(letter);
		keyChar = getchar();
	}


	return 0;
}

int decrypt(int key[MAX_LENGTH], int keyChar){

	if('A' <= keyChar && keyChar <= 'Z'){
		int remainder = keyChar - 'A'; // Gives the index number of the character in the array
		return 'A' + Offset(key, remainder);
	}
	if('a' <= keyChar && keyChar <= 'z'){
		int remainder = keyChar - 'a';
		return 'a' + Offset(key, remainder);
	}
	else{
		return keyChar;
	}

}
//We need to map the index number of the character in the array to the numbering of letters in the alphabet
int Offset(int key[MAX_LENGTH], int remainder){
	for(int i = 0; i < MAX_LENGTH; i++){
		if (key[i] == remainder){
			return i;
		}
	}
	return 0;
}








































