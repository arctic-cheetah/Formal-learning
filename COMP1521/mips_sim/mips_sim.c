// COMP1521 20T3 Assignment 1: mips_sim -- a MIPS simulator
// starting point code v0.1 - 13/10/20
//By z5312813


// NEED TO CONSIDER HALTING CASES


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#define MAX_LINE_LENGTH 256
#define INSTRUCTIONS_GROW 64


// ADD YOUR #defines HERE
#define FUNCT 11
#define OPCODE 26
#define D_REGISTER 16
#define T_REGISTER 21
#define S_REGISTER 0
#define EXTRACT 5
#define NUMREG 32
#define MAX_LEN 100
//Need to check register and # defines

void execute_instructions(int n_instructions,
                          uint32_t instructions[n_instructions],
                          int trace_mode);
char *process_arguments(int argc, char *argv[], int *trace_mode);
uint32_t *read_instructions(char *filename, int *n_instructions_p);
uint32_t *instructions_realloc(uint32_t *instructions, int n_instructions);

/////////////////////////////////////////////////////////////////////////////////
// ADD YOUR FUNCTION PROTOTYPES HERE
uint32_t function(int instruction);
char *opCodeCheck(int opCode);
uint32_t src_reg(int instruction);
uint32_t dest_reg(int instruction);
uint32_t temp_reg(int instruction);
int16_t get_imm(int instruction);
char *instructCode(int opCode, int funct);
void print_instruct(char *instruct, int instruction);
int execute_op_code(char *instruct, int instruction, int *reg);
int execute_op_code_NP(char *instruct, int instruction, int *reg);
int execute_syscall(int call, int *reg);
int execute_syscall_NP(int call, int *reg);

// YOU SHOULD NOT NEED TO CHANGE MAIN

int main(int argc, char *argv[]) {
	//trace_mode is 1 if -r is absent
	// 0 if present
    int trace_mode; 
    char *filename = process_arguments(argc, argv, &trace_mode);

    int n_instructions;
    uint32_t *instructions = read_instructions(filename, &n_instructions);

    execute_instructions(n_instructions, instructions, trace_mode);

    free(instructions);
    return 0;
}


// simulate execution of  instruction codes in  instructions array
// output from syscall instruction & any error messages are printed
//
// if trace_mode == 1:
//     information is printed about each instruction as it executed
//
// execution stops if it reaches the end of the array

void execute_instructions(int n_instructions,
                          uint32_t instructions[n_instructions],
                          int trace_mode) {
  	//program counter
    int pc = 0;
    int prevPc = 0;
    //Assign all 32 registers to 0
    int reg[NUMREG] = {0};
    
    char instruct[MAX_LEN];

    while (pc < n_instructions) {
    	//Check if branch landed before 0 instructions
    	if (pc < 0) {
    		printf("Illegal branch to address before instructions: PC = %d\n", pc);
    		break;
    	}
    	if (trace_mode) {
            printf("%d: 0x%08X ", pc, instructions[pc]);
            
			//Obtain opCode
			uint32_t opCode = instructions[pc] >> OPCODE;
			
			//extract the funct section
			uint32_t funct = function(instructions[pc]);
				
			strcpy(instruct, instructCode(opCode, funct));
			//print out the instruction
			if (!strcmp(instruct, "addi")) {
				printf("%s ", instruct);
			}
			else {
				printf("%s  ", instruct);
			}
			
			print_instruct(instruct, instructions[pc]);
			printf("\n");
			//Check for bad instructions
			if (!strcmp(instruct, "invalid instruction code")) {
				break;
			}
			//Check if syscall 10 or bad syscall is executed
			if (!execute_op_code(instruct, instructions[pc], reg)) {
				break;
			}
			
			//Check for branching
			//Terminate program for bad branches
			uint32_t Sreg = src_reg(instructions[pc]);
			uint32_t Treg = temp_reg(instructions[pc]);
			int16_t imm = get_imm(instructions[pc]);
			if (!strcmp(instruct, "beq")) {
				if (reg[Sreg] == reg[Treg]) {
					printf(">>> branch taken to PC = %d\n", pc + imm);
					prevPc = pc;
					pc = pc + imm;
					continue;
				}
				else {
					printf(">>> branch not taken\n");
				} 
			}
			else if (!strcmp(instruct, "bne")) {
				if (reg[Sreg] != reg[Treg]) {
					printf(">>> branch taken to PC = %d\n", pc + imm);
					prevPc = pc;
					pc = pc + imm;
					continue;
				}
				else {
					printf(">>> branch not taken\n");
				} 
			}
			

        }
        //Consider if trace_mode is off
        else {
        	
    		if (instructions[pc] <= 0) {
    			printf("invalid instruction code\n");
    			break;
    		}
        	//Obtain opCode
			uint32_t opCode = instructions[pc] >> OPCODE;
			
			//extract the funct section
			uint32_t funct = function(instructions[pc]);
				
			strcpy(instruct, instructCode(opCode, funct));
			
			if (!execute_op_code_NP(instruct, instructions[pc], reg)) {
				break;
			}
			//Consider branching
			uint32_t Sreg = src_reg(instructions[pc]);
			uint32_t Treg = temp_reg(instructions[pc]);
			int16_t imm = get_imm(instructions[pc]);
			if (!strcmp(instruct, "beq")) {
				if (reg[Sreg] == reg[Treg]) {
					pc = pc + imm;
					continue;
				}
			}
			else if (!strcmp(instruct, "bne")) {
				if (reg[Sreg] != reg[Treg]) {
					pc = pc + imm;
					continue;
				}
			}
        	
        }
        pc++;
    }
    //Check if branch landed after the instructions
    if (pc > n_instructions) {
    	printf("Illegal branch to address after instructions: PC = %d\n", prevPc);
    }
}
///////////////////////////////////////////////////////////////////////////
// ADD YOUR FUNCTIONS HERE

//An instruction that extracts the funct section of an instruction
uint32_t function(int instruction) {
	uint32_t funct = 1;
	funct = funct << (FUNCT);
	funct -=1;
	funct = funct & instruction;
	return funct;
}
//A group of functions that returns the source, dest and temp register
uint32_t src_reg(int instruction) {
	uint32_t Sreg = 1;
	Sreg = Sreg << EXTRACT;
	Sreg -=1;
	Sreg = Sreg & (instruction >> T_REGISTER);
	return Sreg;
}
uint32_t dest_reg(int instruction) {
	uint32_t Dreg = 1;
	Dreg = Dreg << EXTRACT;
	Dreg -=1;
	Dreg = Dreg & (instruction >> FUNCT);
	return Dreg;
}
uint32_t temp_reg(int instruction) {
	uint32_t Treg = 1;
	Treg = Treg << EXTRACT;
	Treg -=1;
	Treg = Treg & (instruction >> D_REGISTER);
	return Treg;
}

//A function which obtains the immediate value
int16_t get_imm(int instruction) {
	int16_t imm = 1;
	imm = imm << (D_REGISTER);
	imm -=1;
	imm = imm & instruction;
	return imm;
}

//A function that returns the instruction as a string
//CHECK FOR BUGS

char *instructCode(int opCode, int funct) {
	if (opCode == 0) {
		if (funct == 32) {
			return "add";
		}
		else if (funct == 34) {
			return "sub";
		}
		else if (funct == 42) {
			return "slt";
		}
		else if (funct == 12) {
			return "syscall";
		}
	}
	else if (opCode == 28) {
		return "mul";
	}
	else if (opCode == 4) {
		return "beq";
	}
	else if (opCode == 5) {
		return "bne";
	}
	else if (opCode == 8) {
		return "addi";
	}
	else if (opCode == 13) {
		return "ori";
	}
	else if (opCode == 15) {
		return "lui";
	}
	//Invalid instruction entered
	return "invalid instruction code";
}
//A function which prints out the appropriate format for the registers
//On the same line as the registers
void print_instruct(char *instruct, int instruction) {
	uint32_t Sreg = src_reg(instruction);
	uint32_t Treg = temp_reg(instruction);
	uint32_t Dreg = dest_reg(instruction);
	int16_t imm = get_imm(instruction);
	
	//Need to implement branch
	
	if (!strcmp(instruct, "add")) {
		printf("$%d, ", Dreg);
		printf("$%d, ", Sreg);
		printf("$%d", Treg);
	}
	else if (!strcmp(instruct, "sub")) {
		printf("$%d, ", Dreg);
		printf("$%d, ", Sreg);
		printf("$%d", Treg);
	}
	else if (!strcmp(instruct, "slt")) {
		printf("$%d, ", Dreg);
		printf("$%d, ", Sreg);
		printf("$%d", Treg);
	}
	else if (!strcmp(instruct, "mul")) {
		printf("$%d, ", Dreg);
		printf("$%d, ", Sreg);
		printf("$%d", Treg);
	}
	else if (!strcmp(instruct, "beq")) {
		printf("$%d, ", Sreg);
		printf("$%d, ", Treg);
		printf("%d", imm);
	}
	else if (!strcmp(instruct, "bne")) {
		printf("$%d, ", Sreg);
		printf("$%d, ", Treg);
		printf("%d", imm);
	}
	else if (!strcmp(instruct, "addi")) {
		printf("$%d, ", Treg);
		printf("$%d, ", Sreg);
		printf("%d", imm);
	}
	else if (!strcmp(instruct, "ori")) {
		printf("$%d, ", Treg);
		printf("$%d, ", Sreg);
		printf("%d", imm);
	}
	else if (!strcmp(instruct, "lui")) {
		printf("$%d, ", Treg);
		printf("%d", imm);
	}
}

//A function that executes the instructions, 
//prints and stores any value into the registers
//Returns zero if syscall exit(10) is executed
int execute_op_code(char *instruct, int instruction, int *reg) {
	uint32_t Sreg = src_reg(instruction);
	uint32_t Treg = temp_reg(instruction);
	uint32_t Dreg = dest_reg(instruction);
	int16_t imm = get_imm(instruction);
	
	int good = 1;
	
	if (!strcmp(instruct, "add")) {
		reg[Dreg] = reg[Sreg] + reg[Treg];
		printf(">>> $%d = %d\n", Dreg, reg[Dreg]);
	}
	else if (!strcmp(instruct, "sub")) {
		reg[Dreg] = reg[Sreg] - reg[Treg];
		printf(">>> $%d = %d\n", Dreg, reg[Dreg]);
	}
	else if (!strcmp(instruct, "slt")) {
		reg[Dreg] = reg[Sreg] < reg[Treg];
		printf(">>> $%d = %d\n", Dreg, reg[Dreg]);
	}
	else if (!strcmp(instruct, "mul")) {
		reg[Dreg] = reg[Sreg] * reg[Treg];
		printf(">>> $%d = %d\n", Dreg, reg[Dreg]);
	}
	else if (!strcmp(instruct, "addi")) {
		reg[Treg] = reg[Sreg] + imm;
		printf(">>> $%d = %d\n", Treg, reg[Treg]);
	}
	else if (!strcmp(instruct, "ori")) {
		reg[Treg] = reg[Sreg] | imm;
		printf(">>> $%d = %d\n", Treg, reg[Treg]);
	}
	else if (!strcmp(instruct, "lui")) {
		reg[Treg] = imm << 16;
		printf(">>> $%d = %d\n", Treg, reg[Treg]);
	}
	else if (!strcmp(instruct, "syscall")) {
		//Check the syscall
		good = execute_syscall(reg[2], reg);
	}
	//$0 must always be zero
	reg[0] = 0;
	
	return good;
}

//A function that does not print and only executes the instructions 
//and stores any value into the registers
//Returns zero if syscall exit(10) is executed
int execute_op_code_NP(char *instruct, int instruction, int *reg) {
	uint32_t Sreg = src_reg(instruction);
	uint32_t Treg = temp_reg(instruction);
	uint32_t Dreg = dest_reg(instruction);
	int16_t imm = get_imm(instruction);
	
	int good = 1;
	
	if (!strcmp(instruct, "add")) {
		reg[Dreg] = reg[Sreg] + reg[Treg];
	}
	else if (!strcmp(instruct, "sub")) {
		reg[Dreg] = reg[Sreg] - reg[Treg];
	}
	else if (!strcmp(instruct, "slt")) {
		reg[Dreg] = reg[Sreg] < reg[Treg];
	}
	else if (!strcmp(instruct, "mul")) {
		reg[Dreg] = reg[Sreg] * reg[Treg];
	}
	else if (!strcmp(instruct, "beq")) {
	}
	else if (!strcmp(instruct, "bne")) {
	}
	else if (!strcmp(instruct, "addi")) {
		reg[Treg] = reg[Sreg] + imm;
	}
	else if (!strcmp(instruct, "ori")) {
		reg[Treg] = reg[Sreg] | imm;
	}
	else if (!strcmp(instruct, "lui")) {
		reg[Treg] = imm << 16;
	}
	else if (!strcmp(instruct, "syscall")) {
		//Check the syscall
		good = execute_syscall_NP(reg[2], reg);
	}
	else {
		//Bad instruction
		printf("invalid instruction code\n");
		good = 0;
	}
	//$0 must always be zero
	reg[0] = 0;
	
	return good;
}

//A function that executes syscalls
int execute_syscall(int call, int *reg) {
	printf(">>> syscall %d\n", call);
	int good = 1;
	if (call == 1) {
		printf("<<< %d\n", reg[4]);
	}
	else if (call == 11) {
		printf("<<< %c\n", reg[4]);
	}	
	else if (call == 10) {
		good = 0;
	}
	else {
		//bad syscall
		printf("Unknown system call: %d\n", call);
		good = 0;
	}
	return good;
}

//A function that executes syscalls
int execute_syscall_NP(int call, int *reg) {
	int good = 1;
	if (call == 1) {
		printf("%d", reg[4]);
	}
	else if (call == 11) {
		printf("%c", reg[4]);
	}	
	else if (call == 10) {
		good = 0;
	}
	else {
		//bad syscall
		printf("Unknown system call: %d\n", call);
		good = 0;
	}
	return good;
}



/////////////////////////////////////////////////////////////////////////////////
// YOU DO NOT NEED TO CHANGE CODE BELOW HERE


// check_arguments is given command-line arguments
// it sets *trace_mode to 0 if -r is specified
//          *trace_mode is set to 1 otherwise
// the filename specified in command-line arguments is returned

char *process_arguments(int argc, char *argv[], int *trace_mode) {
    if (
        argc < 2 ||
        argc > 3 ||
        (argc == 2 && strcmp(argv[1], "-r") == 0) ||
        (argc == 3 && strcmp(argv[1], "-r") != 0)) {
        fprintf(stderr, "Usage: %s [-r] <file>\n", argv[0]);
        exit(1);
    }
    *trace_mode = (argc == 2);
    return argv[argc - 1];
}


// read hexadecimal numbers from filename one per line
// numbers are return in a malloc'ed array
// *n_instructions is set to size of the array

uint32_t *read_instructions(char *filename, int *n_instructions_p) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "%s: '%s'\n", strerror(errno), filename);
        exit(1);
    }

    uint32_t *instructions = NULL;
    int n_instructions = 0;
    char line[MAX_LINE_LENGTH + 1];
    while (fgets(line, sizeof line, f) != NULL) {

        // grow instructions array in steps of INSTRUCTIONS_GROW elements
        if (n_instructions % INSTRUCTIONS_GROW == 0) {
            instructions = instructions_realloc(instructions, n_instructions + INSTRUCTIONS_GROW);
        }

        char *endptr;
        instructions[n_instructions] = strtol(line, &endptr, 16);
        if (*endptr != '\n' && *endptr != '\r' && *endptr != '\0') {
            fprintf(stderr, "%s:line %d: invalid hexadecimal number: %s",
                    filename, n_instructions + 1, line);
            exit(1);
        }
        n_instructions++;
    }
    fclose(f);
    *n_instructions_p = n_instructions;
    // shrink instructions array to correct size
    instructions = instructions_realloc(instructions, n_instructions);
    return instructions;
}


// instructions_realloc is wrapper for realloc
// it calls realloc to grow/shrink the instructions array
// to the speicfied size
// it exits if realloc fails
// otherwise it returns the new instructions array
uint32_t *instructions_realloc(uint32_t *instructions, int n_instructions) {
    instructions = realloc(instructions, n_instructions * sizeof *instructions);
    if (instructions == NULL) {
        fprintf(stderr, "out of memory");
        exit(1);
    }
    return instructions;
}
