// gnirts a esreveR (Reverse a string)
// Created by
//  ... (Z0000000)
// Created on 2019-??-??

#include <stdio.h>
#include <string.h>

void string_reverse(char *buffer);

int main(int argc, char *argv[]) {

    // NOTE: THIS WON'T WORK:
    // char *str = "Hello!"
    // string_reverse(str)
    //
    // str only points to a string literal, which it is not legal to change.
    // If you attempt to modify it on Linux you will get a runtime error.
    // Instead, you need to create an array to store the string in, e.g.:
    //
    // char str[] = "Hello!"
    // string_reverse(str)

    char str[] = "";
    string_reverse(str);
    printf("%s\n", str);
    return 0;
}

// Takes a string in `buffer`, and reverses it in-place.
void string_reverse(char *buffer) {
	if (buffer[0] != '\0') {
		int wordLen = strlen(buffer);
		char copyBuffer[wordLen];
		int k = 0;
		while (buffer[k] != '\0') {
			copyBuffer[k] = buffer[k];
			k++;
		}
		int i = 0;
		while (k != 0) {
			buffer[i] = copyBuffer[k - 1];
			i++;
			k--;
		}
    }
    
}






































