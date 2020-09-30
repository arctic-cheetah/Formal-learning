//A program that converts BCD into decimals
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define N_BCD_DIGITS 8//The BCD encoded value is between 0...99. We only need 2 powers of ten, we only need 
#define MASK 15 //BCD 15 == 0b1111
#define COLLECT_DIGITS 4 //Every four binary digits represents a decimal digit

uint32_t packed_bcd(uint32_t packed_bcd);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= UINT32_MAX);
        uint32_t packed_bcd_value = l;

        printf("%lu\n", (unsigned long)packed_bcd(packed_bcd_value));
    }

    return 0;
}

// given a packed BCD encoded value between 0 .. 999 999 99 (8 digits => 32 binary digits)

// return the corresponding integer
uint32_t packed_bcd(uint32_t packed_bcd_value) {

    int sum = 0;
    int temp = 0;
    //BCD's are not designed to store negative numbers.
    int storeDigits[N_BCD_DIGITS] = {-1};
    int i = 0;
    while (packed_bcd_value != 0) {	
    	temp = MASK & packed_bcd_value;
    	//printf("%d\n", temp);
    	packed_bcd_value = packed_bcd_value >> COLLECT_DIGITS;
		storeDigits[i] = temp; 
		i++;
    }
    //Now iterate through the array and add powers of ten
    int pow10 = 1;
    int k = 0;
    while (k < N_BCD_DIGITS && storeDigits[k] != -1) {
    	sum = sum + pow10 * storeDigits[k];
    	pow10 *=10;
    	k +=1;
    }
    return sum;
}
