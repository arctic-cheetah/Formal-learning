// Sample solution for COMP1521 lab exercises
//
// generate the opcode for an addi instruction

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "addi.h"
#define ADDI 8
#define OPCODE 26

// return the MIPS opcode for addi $t,$s, i
uint32_t addi(int t, int s, int i) {

    uint32_t instruct = 8 << OPCODE;
    instruct = instruct | ((uint32_t)s << 21);
    instruct = instruct | ((uint32_t)t << 16);
    instruct = instruct | (uint16_t)i;
    return instruct;
}
