//A program that reads in arguments and applies elementary statistics, min, max, total product and total sum

#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 1023

void print_array (int *array, int length) {
	for (int i = 1; i < length; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

//Find the minimum number in the array and return it
int min (int *array, int length) {
	int minNum = array[1];
	for (int i = 1; i < length; i++) {
		if (minNum > array[i]) {
			minNum = array[i];
		}
	}
	return minNum;
}
//Find the maximum numeber in the array and return it
int max (int *array, int length) {
	int maxNum = array[1];
	for (int i = 1; i < length; i++) {
		if (maxNum < array[i]) {
			maxNum = array[i];
		}
	}
	return maxNum;
}
//Find the total sum of the numbers and return it
int sum (int *array, int length) {
	int totalSum = 0;
	for (int i = 1; i < length; i++) {
		totalSum += array[i];
	}
	return totalSum;
}

//Find the total product of the numbers 

int product (int *array, int length) {
	int totalProduct = 1;
	for (int i = 1; i < length; i++) {
		totalProduct *= array[i];
	}
	return totalProduct;
}

//Find the mean of the numbers
int mean (int *array, int length) {
	return sum(array, length) / (length - 1);
}


int main(int argc, char **argv) {
	int array[MAX_LENGTH];
	int i = 1;
	while (i < argc) {
		array[i] = atoi(argv[i]);
		i++;
	}
	int length = i;
	
	//print_array(array, length);
	
	printf("MIN:  %d\n", min(array, length));
	printf("MAX:  %d\n", max(array, length));
	printf("SUM:  %d\n", sum(array, length));
	printf("PROD: %d\n", product(array, length));
	printf("MEAN: %d\n", mean(array, length));
	return 0;
}


