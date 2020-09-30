#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 12



void *sum (int strA[MAX_LENGTH], int strB[MAX_LENGTH]);
void reverse_array(int strA[MAX_LENGTH]);
void print_array (int str[MAX_LENGTH]);

int main() {
	int str1[MAX_LENGTH + 2] = {5, 8, 3, 4, 5};
	int str2[MAX_LENGTH + 2] = {6, 7, 8, 9, 0};
	
	sum (str1, str2);
	
}





void *sum (int strA[MAX_LENGTH], int strB[MAX_LENGTH]) {
	int k = MAX_LENGTH;
	int sum[MAX_LENGTH + 2];
	int holdOver = 0;
	
	
	while (k >= 0) {
		sum[k + 1] = strA[k] + strB[k] + holdOver;
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
		printf("%d ", sum[k]);
		k++;
		
	}
	printf("\n");
	
	return 0;
}


void reverse_array(int strA[MAX_LENGTH]) {
	int dummyArray[MAX_LENGTH];
	int k = 0;
	int j = 0;
	while (k < MAX_LENGTH) {
		dummyArray[k] = strA[k]; 
		k++;
	}
	//print_array(dummyArray);
	k = k - 1;
	while (k >= 0) {
		strA[j] = dummyArray[k];
		j++;
		k--;
	}

}

void print_array (int str[MAX_LENGTH]) {
	for (int i = 0; i < MAX_LENGTH; i++ ) {
		printf("%d", str[i]);
	}
	printf("\n");

}























