//A program that prints out the fibonacci series using memoisation
#include <stdio.h>
#include <stdlib.h>

unsigned int memo[47] = {0};

int calls = 0;

int fibonacci (int k) {
	calls++;
	
	if(memo[k] != 0) {
		return memo[k];
	}
			
	if (k == 1) {
		return 1;
	}
	else if (k == 0) {
		return 0;
	}
	memo[k] = fibonacci(k - 1) + fibonacci(k - 2);
	
	return memo[k]; 
}

int main(void) {
	int i = 0;
	while (scanf("%d", &i) != EOF) {
		printf("%d\n", fibonacci(i));
	}
	
	printf("There were %d calls.\n", calls);
	
	
	return EXIT_SUCCESS;
}
