#include "bit_rotate.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// return the value bits rotated left n_rotations
uint16_t bit_rotate(int n_rotations, uint16_t bits) {
	uint16_t value = bits;
	
	if (n_rotations < 0) {
		n_rotations = (n_rotations % 16) + 16;
	}
	
	uint16_t Upper = value << ( n_rotations % 16 );
	uint16_t Lower = value >> (16 - ( n_rotations % 16 ));
	
	uint16_t newVal = Upper | Lower;
	return newVal;
}
