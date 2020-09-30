
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "print_bits.h"

int main(int argc, char **argv) {
	
	uint32_t x, y, z;
	int n_bits = 8 * sizeof(x);
	
	x = strtol(argv[1], NULL, 10);
	y = strtol(argv[2], NULL, 10);
	
	printf("x = %d \n", x);
	
	print_bits(x, n_bits);
	printf("\n");
	
	z = ((uint32_t)1) << x;

    print_bits(z, n_bits);
    printf("\n");

    return 0;
}
