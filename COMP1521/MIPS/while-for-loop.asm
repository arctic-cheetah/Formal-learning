#implementation of while/for loop in MIPS
    .data
    .text
    .globl main
        main:
        li $t0, 0 #int iterator = 0;
        li $t1, 0 #int counter = 0;
    while:
        beq $t0, 11, exit # if (iterator == 11) {end loop}
        add $t0, $t1, $t0 # iterator = counter + iterator
        addi $t0, $t0, 1 # counter++;
        j while # execute the branch "while",

    exit:
        li $v0, 10
        syscall
