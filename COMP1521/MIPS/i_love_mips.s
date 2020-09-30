main:
    la $a0, string
    li $v0, 4
    syscall
    jr $ra

    .data
string:
    .asciiz "I love MIPS!\n"
