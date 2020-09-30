#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "print_bits.h"

//A program that obtains the bit range of a number
int main (int argc, char **argv) {

	//uint32_t x = strtol(argv[1], NULL, 10);
	int low_bit = strtol(argv[1], NULL, 10);
	int high_bit = strtol(argv[2], NULL, 10);
	
	uint32_t mask = 1;
	int n_bits = 8 * sizeof(mask);
	int maskSize = high_bit - low_bit + 1;
	mask = mask << maskSize;
	mask = mask - 1;
	mask = mask << low_bit;
	
	printf("Bits %d to %d of %u are ones: \n", low_bit, high_bit, mask);
	print_bits(mask, n_bits);
	printf("\n");
	
	return 0;
}































