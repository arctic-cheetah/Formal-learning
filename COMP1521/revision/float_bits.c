// Extract the 3 parts of a float using bit operations only

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

#define GETSIGN 31
#define GETEXP 23
#define GETFRAC 9

// separate out the 3 components of a float
float_components_t float_bits(uint32_t f) {
	float_components_t value;
	
	//Fetch the sign
	value.sign = f >> GETSIGN;
	
	//Fetch the fraction
	uint32_t temp = f;
	temp = temp << GETFRAC;
	temp = temp >> GETFRAC;
	value.fraction = temp;
	
	//Fetch the exponent
	temp = f;
	//Remove the sign
	temp = temp << 1;
	temp = temp >> 1;
	//Remove the fraction
	temp = temp >> GETEXP;
	value.exponent = temp;
	
    return value;
}

// given the 3 components of a float
// return 1 if it is NaN, 0 otherwise
int is_nan(float_components_t f) {
    if (f.exponent == 0xFF && f.fraction) {
    	return 1;
    }
    return 0;
}

// given the 3 components of a float
// return 1 if it is inf, 0 otherwise
int is_positive_infinity(float_components_t f) {
    if (f.exponent >= 0xFF && !f.fraction && !f.sign) {
    	return 1;
    }
    return 0;
}

// given the 3 components of a float
// return 1 if it is -inf, 0 otherwise
int is_negative_infinity(float_components_t f) {
    if (f.exponent >= 0xFF && !f.fraction && f.sign) {
    	return 1;
    }
    return 0;
}

// given the 3 components of a float
// return 1 if it is 0 or -0, 0 otherwise
int is_zero(float_components_t f) {
    if (!f.exponent) {
    	return 1;
    }
    return 0;
}
