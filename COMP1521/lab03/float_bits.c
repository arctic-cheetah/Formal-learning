// Extract the 3 parts of a float using only bit operations

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

#define SIGN 31
#define EXPONENT 23
#define FRACTION 22

// separate out the 3 components of a float
float_components_t float_bits(uint32_t f) {
    float_components_t deconstruct;
    printf("%d\n", f);
    //extract sign
    deconstruct.sign = f >> SIGN;
    
    //extract exponent bit range
    uint32_t exponent = f;
    exponent <<= (32 - SIGN);
    exponent >>= (32 - SIGN);
    exponent >>= EXPONENT;
    deconstruct.exponent = exponent;
    
    //extract fraction bit range
    uint32_t fraction = f;
    fraction <<= 32 - EXPONENT;
    fraction >>= 32 - EXPONENT;
    deconstruct.fraction = fraction;
	
    return deconstruct;
}

// given the 3 components of a float
// return 1 if it is NaN, 0 otherwise
int is_nan(float_components_t f) {
    if (f.exponent == 0xFF && f.fraction != 0) {
    	return 1;
    }
    return 0;
}

// given the 3 components of a float
// return 1 if it is inf, 0 otherwise
int is_positive_infinity(float_components_t f) {
    if (f.exponent == 0xFF && f.fraction == 0 && f.sign == 0) {
    	return 1;
    }
    return 0;
}

// given the 3 components of a float
// return 1 if it is -inf, 0 otherwise
int is_negative_infinity(float_components_t f) {
    if (f.exponent == 0xFF && f.fraction == 0 && f.sign == 1) {
    	return 1;
    }
    return 0;
}

// given the 3 components of a float
// return 1 if it is 0 or -0, 0 otherwise
int is_zero(float_components_t f) {
    if (f.exponent == 0) {
    	return 1;
    }
    return 0;
}
