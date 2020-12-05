#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#define LEAST_BYTE 0xFF


// given a uint32_t value,
// return 1 iff the least significant (bottom) byte
// is equal to the 2nd least significant byte; and
// return 0 otherwise
int practice_q2(uint32_t value) {
    uint32_t least_byte = 0xFF;

    uint32_t lower_byte = value & least_byte;
    uint32_t high_byte = value & (least_byte << 8);
    //Get the second last byte to the correct position
    high_byte = high_byte >> 8;

    if (high_byte == lower_byte) {
        return 1;
    }
    else {
        return 0;
    }
}
