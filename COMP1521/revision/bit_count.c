// count bits in a uint64_t

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

// return how many 1 bits value contains
int bit_count(uint64_t value) {
    
    int i = 0;
    int count = 0;
    while (i < 64) {
    	if (value & (uint64_t)1) {
    		count +=1;
    	} 
    	value = value >> 1;
    	i +=1;
    }

    return count;
}
