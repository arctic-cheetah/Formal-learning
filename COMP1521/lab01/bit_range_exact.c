#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "print_bits.h"

//A program that obtains the bit range of a number
int main (int argc, char **argv) {

	int low_bit = strtol(argv[1], NULL, 0);
	int high_bit = strtol(argv[2], NULL, 0);
	uint32_t x = strtol(argv[3], NULL, 0);
	int n_bits = 8 * sizeof(x);
	
	
	uint32_t maskSize = high_bit - low_bit + 1;
	uint32_t mask = ((uint64_t) 1) << maskSize;
	mask = mask - 1;
	mask = mask << low_bit;
	
	uint32_t value = x & mask;
	value = value >> low_bit;
	
	printf("Value %u in binary is:\n", x);
    print_bits(x, n_bits);
    printf("\n");

    printf("Bits %d to %d of %u are:\n", low_bit, high_bit, x);
    print_bits(value, maskSize);
    printf("\n");
    
    printf("%x \n", value);
	
	return 0;
}































