#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 10

int *sum (int strA[MAX_LENGTH], int strB[MAX_LENGTH], int strC[MAX_LENGTH], int str[MAX_LENGTH]);
int *sum2 (int strA[MAX_LENGTH], int strB[MAX_LENGTH], int str[MAX_LENGTH]);
void print_array (int str[MAX_LENGTH]);
void copy_array (int destination[MAX_LENGTH], int source[MAX_LENGTH]);

int main (int argc, char *argv[]) {	
	int iteration = atoi(argv[1]);
	
	printf("%d\n", iteration);
	//These are the variables for summing
	int strA[MAX_LENGTH] = {1};
	int strB[MAX_LENGTH] = {1};
	int strC[MAX_LENGTH] = {1};
	int strD[MAX_LENGTH] = {1};
	int strO[MAX_LENGTH] = {1};
	//These hold the sums
	int strE[MAX_LENGTH] = {0};
	int strF[MAX_LENGTH] = {0};
	/*
	strA[MAX_LENGTH - 2] = 1;
	strB[MAX_LENGTH - 2] = 1;
	strC[MAX_LENGTH - 2] = 1;
	*/
	int i = 0;
	
	//print_array(strB);
	//print_array(strA);
	while (i < iteration) {
		//a = z + y + x;
		
		//x + y
		sum(strA, strB, strC, strE);
		//sum2(strE, strE, strB);
		copy_array(strB, strE);
		//x + y + z
		//sum2(strO, strC, strE);
		//x = y;
		/*copy_array(strA, strB);
		//y = z;
		copy_array(strB, strC);
		//z = a;
		copy_array(strD, strC);*/
		//printf("%d ", a);
		//print_array(strB);
		//print_array(strE);
		i++;
	}
	
}

//Sum all the digits in the array
int *sum (int strA[MAX_LENGTH], int strB[MAX_LENGTH], int strC[MAX_LENGTH], int str[MAX_LENGTH]) {
	int k = MAX_LENGTH - 2;
	int holdOver = 0;
	
	//print_array (strB);
	
	while (k >= 0) {
		str[k + 1] = strA[k] + strB[k] + strC[k] + holdOver;
		holdOver = str[k + 1] / 10;
		str[k + 1] = str[k + 1] % 10;
		k--;
	}
	if (holdOver != 0) {
		str[0] = holdOver;
		k = 0; 
	}
	else {
		k = 1;
	}
	while (k < MAX_LENGTH) {
		printf("%d ", str[k]);
		k++;
		
	}
	printf("\n");
	return 0;
}


int *sum2 (int strA[MAX_LENGTH], int strB[MAX_LENGTH], int str[MAX_LENGTH]) {
	int k = MAX_LENGTH - 2;
	int holdOver = 0;
	
	//print_array (strB);
	
	while (k >= 0) {
		str[k + 1] = strA[k] + strB[k] + holdOver;
		holdOver = str[k + 1] / 10;
		str[k + 1] = str[k + 1] % 10;
		k--;
	}
	if (holdOver != 0) {
		str[0] = holdOver;
		k = 0; 
	}
	else {
		k = 1;
	}
	while (k < MAX_LENGTH) {
		printf("%d ", str[k]);
		k++;
		
	}
	printf("\n");
	return 0;
}

void print_array (int str[MAX_LENGTH]) {
	for (int i = 0; i < MAX_LENGTH ; i++ ) {
		printf("%d", str[i]);
	}
	printf("\n");

}

void copy_array (int destination[MAX_LENGTH], int source[MAX_LENGTH]) {
	for (int i = 0; i < MAX_LENGTH; i++ ) {
		destination[i] = source[i];
	}

}

































































