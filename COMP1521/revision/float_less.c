// Compare 2 floats using bit operations only

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

// float_less is given the bits of 2 floats bits1, bits2 as a uint32_t
// and returns 1 if bits1 < bits2, 0 otherwise
// 0 is return if bits1 or bits2 is Nan
// only bit operations and integer comparisons are used
uint32_t float_less(uint32_t bits1, uint32_t bits2) {
    float_components_t f1 = float_bits(bits1);
    float_components_t f2 = float_bits(bits2);
    //Check for nan
    if (is_nan(f1) || is_nan(f2)) {
    	return 0;
    }	
    /*
    //Check for inf
    if (is_positive_infinity(f1) && is_positive_infinity(f2)){
    	return 0;
    }
    else if (!is_positive_infinity(f1) && is_positive_infinity(f2)) {
    	return 1;
    }
    else if (is_positive_infinity(f1) && is_negative_infinity(f2)) {
    	return 0;
    }
    else if () {
    }
    //Check for zero;
    if (is_zero(f1) && f2.sign) {
    	return 0;
    }
    else if (is_zero(f1) && !f2.sign) {
    }
    */
    
    uint32_t FirstLess = 0;
    //Check the sign
    if (f1.sign > f2.sign) {
    	return 1;
    }
    else if (f1.sign < f2.sign) {
    	return 0;
    }
    //same sign
    else {
    	//Check the exponent
    	if (f1.exponent < f2.exponent && f1.sign == 0) {
    		return 1;
    	}
    	else if (f1.exponent < f2.exponent && f1.sign == 1) {
    		return 0;
    	}
    	//exponent and sign is the same
    	else {
    		//Check the fraction
    		if (f1.fraction < f2.fraction && f1.sign == 0) {
    			return 1;
    		}
    		else if (f1.fraction < f2.fraction && f1.sign == 1) {
    			return 0;
    		}
    		return 0;
    	} 
    } 

    return FirstLess;
}












