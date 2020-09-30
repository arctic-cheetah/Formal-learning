#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


char *encrypt(char *message, char code[]){
	int length = strlen(message);
	char *encrypted_message = (char *) malloc(sizeof(char)*length);
	
	for(int i = 0; i < length; i++){
		int encryption_index = tolower(message[i]) - 'a';
		if(encryption_index >= 0 && encryption_index < 26){
			encrypted_message[i] = code[encryption_index];
		}
		else{
			encrypted_message[i] = message[i];
		}
	}
	return encrypted_message;
}








int main(){

	char *message = "Hello";
	char code[26] = {'b','a','c','d','s','f','g','h','i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r','e','t','u','v','w','x','y','z'
	};
	char *encrypted_message = encrypt(message, code);
	printf("Original message: %s\n", message);
	printf("Encrypted message: %s", encrypted_message);
	
}






