#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define MASK 15 //BCD 15 == 0b1111
#define BCD_DIGITS 4 //Every four binary digits represents a decimal digit
#define MAX_LENGTH 2 //The BCD encoded value is between 0...99. We only need 2 powers of ten, we only need 

int bcd(int bcd_value);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= 0x0909);
        int bcd_value = l;

        printf("%d\n", bcd(bcd_value));
    }

    return 0;
}

// given a  BCD encoded value between 0 .. 99
// return corresponding integer
int bcd(int bcd_value) {
	int sum = 0;
    int temp = 0;
    //BCD's are not designed to store negative numbers.
    int storeDigits[MAX_LENGTH] = {0};
    int i = 0;
    while (bcd_value != 0) {	
    	temp = MASK & bcd_value;
    	printf("%d\n", temp);
    	bcd_value = bcd_value >> BCD_DIGITS;
    	if (temp != 0) (
			storeDigits[i] = temp; 
		)
		i++;
    }
    //Now iterate through the array and add powers of ten
    int pow10 = 1;
    int k = 0;
    while (k < MAX_LENGTH) {
    	sum = sum + pow10 * storeDigits[k];
    	pow10 *=10;
    	k +=1;
    }
    /*
    sum = sum + 1 * storeDigits[0];
    sum = sum + 10 * storeDigits[1];
    */
    return sum;
}




















