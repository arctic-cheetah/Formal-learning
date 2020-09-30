#include <stdio.h>


int main(){
	int readChar;
	readChar = getchar();
	while (readChar != EOF){
		printf("I read character: %c with ASCII code: %d. \n", readChar, readChar);
		readChar = getchar();
	
	}
	printf("User has exited the program\n");
	


	return 0;
}







