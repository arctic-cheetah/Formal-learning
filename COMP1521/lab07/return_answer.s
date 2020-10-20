.text
main:

    addi $sp, $sp, -4
    sw $ra, ($sp)

    jal answer

    lw $ra, ($sp)
    addi $sp, $sp, 4

    li $v0, 1
    syscall

    li $v0, 10
    syscall





answer:
    la $t0, myNum
    lw $a0, ($t0)
    jr $ra


.data
    myNum: .word 42
