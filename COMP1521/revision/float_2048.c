// Multiply a float by 2048 using bit operations only

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "floats.h"

#define MULT 11
#define GETSIGN 31
#define GETEXP 23
#define GETFRAC 9

#define INF 0xFF

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

// float_2048 is given the bits of a float f as a uint32_t
// it uses bit operations and + to calculate f * 2048
// and returns the bits of this value as a uint32_t
//
// if the result is too large to be represented as a float +inf or -inf is returned
//
// if f is +0, -0, +inf or -inf, or Nan it is returned unchanged
//
// float_2048 assumes f is not a denormal number
//
uint32_t float_2048(uint32_t f) {
	float_components_t value = float_bits(f);
	
    //Check if the number is inf or NAN or zero
    if (is_nan(value)) {
    	return f;
    }
    else if (is_positive_infinity(value)) {
    	return f;
    }
    else if (is_negative_infinity(value)) {
    	return f;
    }
    else if (is_zero(value)) {
    	return f;
    }
    
    //Multiply by 2048
    value.exponent = value.exponent + MULT;
    
    //Check if the exponent is out of bounds
    //if positive infinity
    if (value.exponent >= INF && !value.sign) {
    	uint32_t infP = INF;
    	infP = infP << GETEXP;
    	infP = infP | (value.sign << GETSIGN);
    	return infP;
    }
    else if (value.exponent >= INF && value.sign) {
    	uint32_t infN = INF;
    	infN = infN << GETEXP;
    	infN = infN | (value.sign << GETSIGN);
    	return infN;
    }
    
    //reconstruct the number
    uint32_t f1 = 0;
    f1 = value.sign << GETSIGN;
    f1 = f1 | (value.exponent << GETEXP);
    f1 = f1 | value.fraction;
    

    return f1;
}
























