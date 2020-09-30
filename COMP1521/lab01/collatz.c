//A function program that prints out the collatz chain from the collatz conjecture
#include <stdio.h>
#include <stdlib.h>

int collatz (int myNum) {
	if (myNum == 1) {
		//printf("%d\n", myNum);
		return 1;
	}
	else if ( (myNum & 1) ) {
		myNum = 3*myNum + 1;
		printf("%d\n", myNum);
		collatz(myNum);
	}
	else if ( !(myNum & 1) ) {
		myNum = myNum / 2;
		printf("%d\n", myNum);
		collatz(myNum);
	}
	return myNum;
}

int main(int argc, char **argv)
{
	if (argc == 1) {
		printf("There are no arguments\n");
	}
	int myNum = atoi(argv[argc - 1]);
	printf("%d\n", myNum);
	collatz(myNum);
	
	return EXIT_SUCCESS;
}
