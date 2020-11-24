#include "sign_flip.h"

#define SIGN 31

// given the 32 bits of a float return it with its sign flipped
uint32_t sign_flip(uint32_t f) {
    
    uint32_t sign = f >> SIGN;  
    
    if (sign == 1) {
        sign = sign << SIGN;
        f = sign ^ f;
    }
    else if (sign == 0) {
        sign = ~sign;
        sign = sign << SIGN;
        f = sign | f;
    }
    
    return f;
}
