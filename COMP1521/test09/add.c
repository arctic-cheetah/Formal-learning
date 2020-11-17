#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "add.h"

#define DEST_REG 11
#define TEMP_REG 16
#define SRC_REG 21


// return the MIPS opcode for add $d, $s, $t
uint32_t add(uint32_t d, uint32_t s, uint32_t t) {
	uint32_t code = (d << DEST_REG);
	code = code | (t << TEMP_REG);
	code = code | (s << SRC_REG);
	code = code | (32);

    return code; // REPLACE WITH YOUR CODE

}
