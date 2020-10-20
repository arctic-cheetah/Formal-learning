.text
main:

    addi $sp, $sp, -4
    sw $ra, 0($sp)

    la $a0, string

    jal strlen

    move $a0, $v0
    li $v0, 1
    syscall

    li $a0, '\n'
    li $v0, 11
    syscall

    lw $ra, 0($sp)
    addi $sp, $sp, 4

    li $v0, 10
    syscall

strlen:
    li $v0, 0
loop:
    add $t1, $a0, $v0
    lb $t2, ($t1)
    beq $t2, 0, end
    addi $v0, $v0, 1
    j loop
end:
    jr $ra




.data
    string: .asciiz "Hello"
