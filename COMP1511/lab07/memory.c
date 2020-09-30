//Demonstrates memory allocation

#include<stdio.h>
#include<stdlib.h>

int *mallocNumber();

int main(){

	int *iPointer = mallocNumber();

	*iPointer += 25;
	
	printf("%d\n", *iPointer);
	
	free(iPointer);
	
	return 0;
}


int *mallocNumber(){

	int *intPointer = malloc(sizeof(int));
	printf("Enter a number: ");
	scanf("%d", intPointer);
	
	return intPointer;
}







































