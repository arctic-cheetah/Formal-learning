// swap pairs of bits of a 64-bit value, using bitwise operators

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

// return value with pairs of bits swapped
uint64_t bit_swap(uint64_t value) {
    

	int i = 0;
	uint64_t newNum = 0;
	while (i < 32) {
		uint64_t temp1 = value & ( (uint64_t)1 << 2*i );
		uint64_t temp2 = value & ( (uint64_t)1 << (2*i + 1) );
		
		temp1 = temp1 << 1;
		temp2 = temp2 >> 1;
		
		newNum = newNum | temp1 | temp2;
		
		i +=1;
	}	
	
    return newNum;
}





