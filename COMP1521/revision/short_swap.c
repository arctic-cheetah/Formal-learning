// Swap bytes of a short

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define BYTES 0xFF

// given uint16_t value return the value with its bytes swapped
uint16_t short_swap(uint16_t value) {
    
    uint16_t temp = value & BYTES;
    temp = temp << 8;
    value = value >> 8;
    value = value | temp;

    return value;
}
