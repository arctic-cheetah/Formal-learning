#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "add.h"

#define LOWADD 32
#define S_REG 21
#define T_REG 16
#define D_REG 11

// return the MIPS opcode for add $d, $s, $t
uint32_t add(uint32_t d, uint32_t s, uint32_t t) {
	uint32_t instruct = LOWADD;
	instruct = instruct | (s << S_REG);
	instruct = instruct | (t << T_REG);
	instruct = instruct | (d << D_REG);
    return instruct; 

}
