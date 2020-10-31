// Sample solution for COMP1521 lab exercises
//
// generate the opcode for an addi instruction

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "addi.h"

#define OPCODE 26 
#define T_REGISTER 16
#define S_REGISTER 21

// return the MIPS opcode for addi $t,$s, i
uint32_t addi(int t, int s, int i) {
	
	//COnvert immediate to an unsigned 16 bit
	uint16_t imm = i;
	uint32_t code = 1;
	code = code << 29;
	code += imm;
	s = s << S_REGISTER;
	t = t << T_REGISTER;
	code +=(s + t);
	
    return code;

}
