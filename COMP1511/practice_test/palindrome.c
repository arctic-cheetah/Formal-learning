#include <stdio.h>


int main () {
	int temp;
	int reverse = 0;
	int remainder = 0;
	int num = 0;
	
	printf("Enter a number: ");
	scanf("%d", &num);
	temp = num;
	while (temp != 0) {
		remainder = temp % 10;
		reverse = reverse * 10 + remainder;
		temp = temp / 10;
	}
	
	if (reverse == num) {
		printf("The number is a palindrome\n");
	}
	else {
		printf("The number is not a palindrome\n");
	}

	
}
































































