#include <stdio.h>

#define MAX_LENGTH 1024

int main () {

	int num;
	int positive[MAX_LENGTH];
	int negative[MAX_LENGTH];
	scanf("%d", &num);
	int countPos = 0;
	int countNeg = 0;
	//Get user input until zero is obtained
	while (num != 0) {
		if (num < 0) {
			negative[countNeg] = num;
			countNeg++;
		}
		else if (num > 0) {
			positive[countPos] = num;
			countPos++;
		}
		scanf("%d", &num);
	}
	
	//Print positive first
	int i = 0;
	printf("Positive numbers were: ");
	while (i < countPos) {
		printf("%d ", positive[i]);
		i++;
	}
	printf("\n");
	//Print negative second
	int k = 0;
	printf("Negative numbers were: ");
	while (k < countNeg) {
		printf("%d ", negative[k]);
		k++;
	}
	printf("\n");


	return 0;
}
























































