//A program that converts decimal numbers into hexadecimal or binary

#include <stdio.h>

#define MAX_LENGTH 100


//
int static number[MAX_LENGTH];
char static hexNumber[MAX_LENGTH];

//Functions to convert number systems


//Calculates powers of 2^n
int powOf2(int num){
	if (num > 0) {
		int Pow2 = 1;
		num -=1; 
		return Pow2 = 2 * powOf2(num);
	}
	else if (num == 0){
		return 1;
	}
	return 0;
}

//Calculates powers of 16^n

int powOf16(int num) {
	int Pow16 = 1;
	while (num > 0) {
		Pow16 *=16;
		num -=1;
	}
	
	return Pow16;
}

//A function that inputs a decimal number and ouputs a hexadecimal digit
char hexaDecimalDigits(int num) {
	char c = '\0';
	if (num == 0) {
		c = '0';
	}
	else if (num == 1) {
		c = '1';
	}
	else if (num == 2) {
		c = '2';
	}
	else if (num == 3) {
		c = '3';
	}
	else if (num == 4) {
		c = '4';
	}
	else if (num == 5) {
		c = '5';
	}
	else if (num == 6) {
		c = '6';
	}
	else if (num == 7) {
		c = '7';
	}
	else if (num == 8) {
		c = '8';
	}
	else if (num == 9) {
		c = '9';
	}
	else if (num == 10) {
		c = 'A';
	}
	else if (num == 11) {
		c = 'B';
	}
	else if (num == 12) {
		c = 'C';
	}
	else if (num == 13) {
		c = 'D';
	}
	else if (num == 14) {
		c = 'E';
	}
	else if (num == 15) {
		c = 'F';
	}
	
	return c;
}

//Converts hexadecimal digits to deciaml numbers
int decimalDigits(char c) {
	int decimal = 0;
	if (c == '0') {
		decimal = 0;
	}
	else if (c == '1') {
		decimal = 1;
	}
	else if (c == '2') {
		decimal = 2;
	}
	else if (c == '3') {
		decimal = 3;
	}
	else if (c == '4') {
		decimal = 4;
	}
	else if (c == '5') {
		decimal = 5;
	}
	else if (c == '6') {
		decimal = 6;
	}
	else if (c == '7') {
		decimal = 7;
	}
	else if (c == '8') {
		decimal = 8;
	}
	else if (c == '9') {
		decimal = 9;
	}
	else if (c == 'A') {
		decimal = 10;
	}
	else if (c == 'B') {
		decimal  = 11;
	}
	else if (c == 'C') {
		decimal = 12;
	}
	else if (c == 'D') {
		decimal = 13;
	}
	else if (c == 'E') {
		decimal = 14;
	}
	else if (c == 'F') {
		decimal = 15;
	}
	
	return decimal;
}


//Converts a decimal to binary and returns the length of the binary number
int decimal_to_binary(int myNum){
	int i = 0;
	while (myNum - powOf2(i) > 0) {
		i +=1;
	}
	
	if (myNum - powOf2(i) == 0) {
		i +=1;
	}
	int k = 0;
	int m = i - 1;
	int binNum[i];
	
	while (i > 0) {
		if (myNum - powOf2(m) >= 0) {
			binNum[k] = 1;
			myNum -= powOf2(m);
		}
		else {
			binNum[k] = 0;
		} 
		i-=1;
		m = i - 1;	
		k++;
	}
	
	int j = 0;
	while (j < k) {
		printf("%d", binNum[j]);
		number[j] = binNum[j];
		j++;
	}
	printf("\n");
	number[j] = -1;
	return k;
}

int binary_to_decimal(int *arrayNum, int length){
	int i = 0;
	int decimal = 0;
	while (i <= length) {
		if (arrayNum[i] == 1) {
			decimal += powOf2(i);
		}
		i++;
	}
	return decimal;
}




int decimal_to_hexadecimal(int myNum){

	int i = 0;
	while (myNum - powOf16(i) > 0) {
		i +=1;
	}
	if (myNum - powOf16(i) == 0) {
		i++;
	}
	printf("%d\n", i);
	int k = 0;
	int m = i - 1;
	char hexNum[i];
	
	while (i > 0) {
	
		//printf("%d\n", myNum - powOf16(m) );
		if (myNum - powOf16(m) > 0) {
			hexNum[k] = hexaDecimalDigits(myNum / powOf16(m) );
			myNum -= (powOf16(m) * 
						(myNum / powOf16(m)) 
					 );
		}
		else {
			hexNum[k] = '0';
		}
		
		i--;
		m -=1;
		k++;
	}
	int j = 0;
	while (j < k) {
		printf("%c", hexNum[j]);
		hexNumber[j] = hexNum[j];
		j++;
	}
	hexNumber[j] = '\0';
	printf("\n");
	return k;	
}

int hexadecimal_to_decimal(char *arrayNum, int length) {
	int decimal = 0;
	int i = 0;
	while (length >= 0) {
		decimal +=( decimalDigits(arrayNum[i]) * powOf16(length) );
		i +=1;
		length -=1;
	}
	printf("%d\n", decimal);
	return decimal;
}




int main(){
	
	int myNum;
	scanf("%d", &myNum);	
	/*
	int length = decimal_to_binary(myNum);
	printf("Decimal number is: %d\n", binary_to_decimal(number, length));
	*/
	int length = decimal_to_hexadecimal(myNum);
	hexadecimal_to_decimal(hexNumber, length - 1);
	
}




































































































