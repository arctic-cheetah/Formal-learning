#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 10



void *sum (char strA[MAX_LENGTH], char strB[MAX_LENGTH]);

int main() {
	char str1[MAX_LENGTH] = "23463";
	char str2[MAX_LENGTH] = "25133";
	sum (str1, str2);
	
}





void *sum (char strA[MAX_LENGTH], char strB[MAX_LENGTH]) {
	int k = MAX_LENGTH - 2;
	int sum[MAX_LENGTH];
	int holdOver = 0;
	
	
	while (k >= 0) {
		
		sum[k + 1] = (strA[k] - '0') + strB[k] - '0' + holdOver;
		
		holdOver = sum[k + 1] / 10;
		
		sum[k + 1] = sum[k + 1] % 10;
		
		k--;
	}
	if (holdOver != 0) {
		sum[0] = holdOver;
		k = 0; 
	}
	else {
		k = 1;
	}
	
	while (k < MAX_LENGTH) {
		printf("%d", sum[k]);
		k++;
		
	}
	
	return 0;
}

























