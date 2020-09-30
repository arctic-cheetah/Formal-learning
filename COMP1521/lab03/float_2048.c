// Multiply a float by 2048 using bit operations only

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
	float_components_t myFloat = float_bits(f);
    //Check base case
    if ( is_nan(myFloat) || is_positive_infinity(myFloat) 
    	|| is_negative_infinity(myFloat) || is_zero(myFloat) ) {
    	return f;
    }
	
	uint32_t sign = f >> SIGN;
	
	//Extract bit range of exponent
	uint32_t exponent = f << (32 - SIGN);
	exponent >>= (32 - SIGN);
	exponent >>= EXPONENT;
	exponent +=11;
	
	//printf("%d\n", exponent);
	//Consider if exponent is out of range
	//Exponent is 8 bits:
	//If adding 11 causes 0b1111 1111, then return either +inf or -inf
	if (exponent > 254 && sign == 0) {
		uint32_t infP = 1;
		infP <<= 8;
		infP -=1;
		infP <<= 23;
		//0000 0000 0000 0000 0000 0000 1111 1111
		return infP;
	}
	else if (exponent > 254 && sign == 1) {
		uint32_t infN = 1;
		infN <<= 9;
		//0000 0000 0000 0000 0000 0001 1111 1111
		infN -=1;
		infN <<= 23;
		return infN;
	}
	exponent <<= EXPONENT;
	
	//Replace original exponent bits
	uint32_t mask = 1;
	
	//Make a mask
	mask <<= SIGN;
	//1000 0000 0000 0000 0000 0000 0000 0000
	mask = ~mask;
	//0111 1111 1111 1111 1111 1111 1111 1111
	mask >>= EXPONENT;
	//0000 0000 0000 0000 0000 0000 1111 1111
	mask <<= EXPONENT;
	
	//Apply mask to float
	f = mask | f;
	f = mask ^ f;
	f = f | exponent;
	
    return f;
}

































































