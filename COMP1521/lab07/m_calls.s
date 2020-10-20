.text
main:
    addi $sp, $sp, -4
    sw $ra, ($sp)

    li $a0, 10
    li $a1, 12
    jal sum_product

    lw $ra, ($sp)
    addi $sp, $sp, 4

    move $a0, $v0
    li $v0, 1
    syscall

    li $a0, '\n'
    li $v0, 11
    syscall

    li $v0, 10
    syscall


sum_product:
    addi $sp, $sp, -12
    sw $ra, 8($sp)
    sw $a0, 4($sp)
    sw $a1, 0($sp)

    li $a0, 6
    li $a1, 7
    jal product

    lw $ra, 8($sp)
    lw $a0, 4($sp)
    lw $a1, 0($sp)
    addi $sp, $sp, 12

    add $v0, $a0, $v0
    add $v0, $a1, $v0

    jr $ra

product:
    mul $v0, $a0, $a1
    jr $ra


.data
