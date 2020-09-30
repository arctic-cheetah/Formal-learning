//A program that prints out the fibonacci series
#include <stdio.h>
#include <stdlib.h>

unsigned int memo[47] = {0};


int fibonacci (int k) {	
		
	if (k == 1) {
		return 1;
	}
	else if (k == 0) {
		return 0;
	}
	
	return (fibonacci(k - 1) + fibonacci(k - 2));
}

int main(void) {
	int i = 0;
	while (scanf("%d", &i) != EOF) {
		printf("%d\n", fibonacci(i));
	}
	
	
	return EXIT_SUCCESS;
}
