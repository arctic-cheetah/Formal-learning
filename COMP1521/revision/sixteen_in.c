//
// Sample solution for COMP1521 lab exercises
//
// Convert string of binary digits to 16-bit signed integer

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define N_BITS 16

int16_t sixteen_in(char *bits);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        printf("%d\n", sixteen_in(argv[arg]));
    }

    return 0;
}

//
// given a string of binary digits ('1' and '0')
// return the corresponding signed 16 bit integer
//
int16_t sixteen_in(char *bits) {

	//Convert the array into ints
	
	for (int i = 0; i < N_BITS; i +=1) {
		bits[i] -= '0';
	}
	
	int16_t count = 0;
	int end = N_BITS - 1;
	int j = 0;
    while (j < N_BITS) {
    	count = (bits[j] << end) | count;
    	end -=1;
    	j+=1;
    }

    return count;
}

















