// Compare 2 floats using bit operations only

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "floats.h"

#define SIGN 31
#define EXPONENT 23
#define FRACTION 22


// float_less is given the bits of 2 floats check1, check2 as a uint32_t
// and returns 1 if check1 < check2, 0 otherwise
// 0 is return if check1 or check2 is Nan
// only bit operations and integer comparisons are used
uint32_t float_less(uint32_t bits1, uint32_t bits2) {
    
    float_components_t check1 = float_bits(bits1);
    float_components_t check2 = float_bits(bits2);
    
    //Consider case where if bits are NAN
    if (is_nan(check1) || is_nan(check2)) {
    	return 0;
    }
    //INFINITY CASES:
    //check1 < check2
    if (is_negative_infinity(check1) && is_positive_infinity(check2)) {
    	return 1;
    }
    //check1 > check2
    if (is_positive_infinity(check1) && is_negative_infinity(check2)) {
    	return 0;
    }
    if (is_positive_infinity(check1) && is_positive_infinity(check2)) {
    	return 0;
    }
    if (is_negative_infinity(check1) && is_negative_infinity(check2)) {
    	return 0;
    }
    
    //Check for zero
    if (is_zero(check1) && is_zero(check2)) {
    	return 0;
    }
    
    int check = 2;
    //Check sign
    if (check1.sign == 1 && check2.sign == 0) {
    	check = 1;
    }
    else if (check1.sign == 0 && check2.sign == 1) {
    	check = 0;
    }
    else {
    	//If sign are the same
    	//Check exponents
    	
    	//If both are positive
    	if (check1.sign == 0 && check2.sign == 0) {
    		if (check1.exponent < check2.exponent) {
    			check = 1;
    		}
    		else {
    			check = 0;
    		}
    		
    		//if exponents are equal, 
    	//then check fraction
    		if (check1.exponent == check2.exponent) {
    			if (check1.fraction < check2.fraction) {
    				check = 1;
    			}
    			else {
					check = 0;
    			}
    		}
    	}
    	//If both are negative
    	else if (check1.sign == 1 && check2.sign == 1) {
    		if (check1.exponent < check2.exponent) {
    			check = 0;
    		}
    		else {
    			check = 1;
    		}
    		
    		//if exponents are equal, 
    	//then check fraction
    		
    		if (check1.exponent == check2.exponent) {
    			if (check1.fraction < check2.fraction) {
    				check = 0;
    			}
    			else if (check1.fraction == check2.fraction) {
    				check = 0;
    			}
    			else {
					check = 1;
				}
    		}
    		
    	}
    	
    }
    

    return check;
}

//////////////////////////////////////////////////////////////////////////////////
///HELPER FUNCTIONS BELOW

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














