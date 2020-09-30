#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

//
// Store an arbitray length Binary Coded Decimal number.
// bcd points to an array of size n_bcd
// Each array element contains 1 decimal digit.
// Digits are stored in reverse order.
//
// For example if 42 is stored then
// n_bcd == 2
// bcd[0] == 0x02
// bcd[1] == 0x04
//

typedef struct big_bcd {
    unsigned char *bcd;
    int n_bcd;
} big_bcd_t;


big_bcd_t *bcd_add(big_bcd_t *x, big_bcd_t *y);
void bcd_print(big_bcd_t *number);
void bcd_free(big_bcd_t *number);
big_bcd_t *bcd_from_string(char *string);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number> <number>\n", argv[0]);
        exit(1);
    }

    big_bcd_t *left = bcd_from_string(argv[1]);
    big_bcd_t *right = bcd_from_string(argv[2]);

    big_bcd_t *result = bcd_add(left, right);

    bcd_print(result);
    printf("\n");

    bcd_free(left);
    bcd_free(right);
    bcd_free(result);

    return 0;
}


// DO NOT CHANGE THE CODE ABOVE HERE



big_bcd_t *bcd_add(big_bcd_t *x, big_bcd_t *y) {
	//Check size of digits of x and y and get the largest
	int digitSize = (x->n_bcd >= y->n_bcd) ? x->n_bcd : y->n_bcd ;
	
	//Allocate memory for new the sum of the bcd.
	big_bcd_t *sum = malloc(sizeof(big_bcd_t));
	
	//Declare its properties
	sum->bcd = malloc( digitSize * sizeof(sum->bcd[0]) );
	sum->n_bcd = digitSize;
	
	
	int digitSum = 0;
	int xDigit = 0;
	int yDigit = 0;
	int newDigit = 0;
	int overFlow = 0;
	//use ascii to add number via moduluo--ERROR
	while (xDigit < x->n_bcd && yDigit < y->n_bcd) {
		digitSum = x->bcd[xDigit] + y->bcd[yDigit] + overFlow;
		//printf("%d\n\n", digitSum);
		//Check for overflow
		overFlow = digitSum / 10;
		sum->bcd[newDigit] = digitSum % 10;
		
		
		newDigit +=1;
		xDigit +=1;
		yDigit +=1;
	}
	
	//Perform while loop for remaining digits in either only x or only y.
	while (xDigit < x->n_bcd) {
		digitSum = x->bcd[xDigit] + overFlow;
		
		//Check for overflow
		overFlow = digitSum / 10;
		sum->bcd[newDigit] = digitSum % 10;
		
		newDigit +=1;
		xDigit +=1;
	}
	
	while (yDigit < y->n_bcd) {
		digitSum = y->bcd[yDigit] + overFlow;
		
		//Check for overflow
		overFlow = digitSum / 10;
		sum->bcd[newDigit] = digitSum % 10;
		
		newDigit +=1;
		yDigit +=1;
	}
	
	//Check if overFlow is 1 or 0
	
	if (overFlow == 1) {
		sum->n_bcd += overFlow;
		sum->bcd = realloc(sum->bcd, sum->n_bcd + 1);
		//printf("%d\n\n", sum->n_bcd);
		sum->bcd[sum->n_bcd - 1] = overFlow;
	}
	
	//Bear in mind, in addition. A max of one digit can be added
	//to the sum given that
	//both numbers have the at least the same number of digits or
	//one of the is longer than the other
	
	
	
    
	return sum;
}



// DO NOT CHANGE THE CODE BELOW HERE


// print a big_bcd_t number
void bcd_print(big_bcd_t *number) {
    // if you get an error here your bcd_add is returning an invalid big_bcd_t
    assert(number->n_bcd > 0);
    for (int i = number->n_bcd - 1; i >= 0; i--) {
        putchar(number->bcd[i] + '0');
    }
}

// free storage for big_bcd_t number
void bcd_free(big_bcd_t *number) {
    // if you get an error here your bcd_add is returning an invalid big_bcd_t
    // or it is calling free for the numbers it is given
    free(number->bcd);
    free(number);
}

// convert a string to a big_bcd_t number
big_bcd_t *bcd_from_string(char *string) {
    big_bcd_t *number = malloc(sizeof *number);
    assert(number);

    int n_digits = strlen(string);
    assert(n_digits);
    number->n_bcd = n_digits;

    number->bcd = malloc(n_digits * sizeof number->bcd[0]);
    assert(number->bcd);

    for (int i = 0; i < n_digits; i++) {
        int digit = string[n_digits - i - 1];
        assert(isdigit(digit));
        number->bcd[i] = digit - '0';
    }

    return number;
}
