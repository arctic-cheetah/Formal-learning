// COMP1521 20T3 final exam Q2 starter code

#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

// given a uint32_t,
// return 1 iff the least significant bit
// is equal to the most significant bit
// return 0 otherwise
int final_q2(uint32_t value) {
    uint32_t highBit = value >> 31;
    uint32_t lowBit = value & 1;
    return (highBit == lowBit);    // REPLACE ME WITH YOUR CODE
}
