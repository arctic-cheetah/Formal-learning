#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define N_BITS 16

static int array[N_BITS] = {
	1,
	2,
	4,
	8,
	16,
	32,
	64,
	128,
	256,
	512,
	1024,
	2048,
	4096,
	8192,
	16384,
	-32768
};

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
//This method uses arithmetic. It is terrible though.
int16_t sixteen_in(char *bits) {
	int sum = 0;
    for (int i = 0; i < N_BITS; i++) {
    	if (bits[i] == '1') {
    		sum += array[N_BITS - i - 1];
    	}
    }

    return sum;
}

