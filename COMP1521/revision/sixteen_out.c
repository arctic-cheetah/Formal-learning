//
// Sample solution for COMP1521 lab exercises
//
// Convert a 16-bit signed integer to a string of binary digits

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define N_BITS 16

char *sixteen_out(int16_t value);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= INT16_MIN && l <= INT16_MAX);
        int16_t value = l;

        char *bits = sixteen_out(value);
        printf("%s\n", bits);

        free(bits);
    }

    return 0;
}

// given a signed 16 bit integer
// return a null-terminated string of 16 binary digits ('1' and '0')
// storage for string is allocated using malloc
char *sixteen_out(int16_t value) {
	
	char *integer = (char *)calloc(N_BITS + 1, sizeof(char) );
	//Null terminate the string
	integer[16] = '\0';
	
	//check if the number is negatives
    if (value < 0) {
    	integer[0] = '1';
    }
    else {
    	integer[0] = '0';
    }
    
    //Remove the 16th bit, which will cause a negative number
    uint16_t noNegative = value;
    noNegative = noNegative << 1;
    noNegative = noNegative >> 1;
    
    int i = 0;
    int j = 15;
    while (i < 15) {
    	uint16_t result = (noNegative >> i) & (uint16_t)1;
    	
    	//Check if result is one
    	if (result) {
    		integer[j] = result + '0';
    	}
    	else {
    		integer[j] = '0';
    	}
    	
    	j -=1;
    	i +=1;
    }
    
    return integer;
}





















