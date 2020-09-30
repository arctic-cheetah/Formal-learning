//A program that prints out the strings of the arguments.
#include <stdio.h>

int main(int argc, char **argv) {
	printf("Program name: %s\n", argv[0]);
	if (argc == 1) {
		printf("There are no other arguments\n");
	}
	else {
		int i = 1;
		printf("There are %d arguments:\n", argc - 1);
		while (i < argc) {
			printf("	Argument %d is \"%s\" \n", i , argv[i]);
			i++;
		}
	}
	 
	return 0;
}




