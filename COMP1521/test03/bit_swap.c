// swap pairs of bits of a 64-bit value, using bitwise operators

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

// return value with pairs of bits swapped
uint64_t bit_swap(uint64_t value) {
    
    int length = 32;
    int i = 0;
    uint64_t mask = value;
    uint64_t newNum = 0;
    
    while (length != 0) {
        uint64_t y = 1; // 0001
        uint64_t x = 2; // 0010
        y = y & mask;
        x = x & mask;
        mask = mask >> 2;
        
        uint64_t temp2 = y;
        y = x >> 1;
        x = temp2 << 1;
        
        
        y = y | x;
        y = y << i;
        
        newNum = newNum | y;
        
        i +=2;
        length -=1;
    }

    return newNum;
}


