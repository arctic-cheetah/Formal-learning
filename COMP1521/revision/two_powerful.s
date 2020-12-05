
#t1, a1 = upperBound
#a0 = i

main:
    addi $sp, $sp, -4
    sw $ra, 0($sp)

    la $a0, prompt          #printf("Enter a size: ")
    li $v0, 4
    syscall

    li $a0, 1

    li $v0, 5               #scanf("%d", &upperBound);
    syscall
    move $a1, $v0

    jal two

    lw $ra, 0($sp)
    addi $sp, $sp, 4

    li $v0, 10
    syscall

two:
    addi $sp, $sp, -12
    sw $a0, 8($sp)
    sw $a1, 4($sp)
    sw $ra, 0($sp)

    li $v0, 1
    syscall

    li $a0, 10
    li $v0, 11
    syscall

    lw $a0, 8($sp)

    bge $a0, $a1, skip
    mul $a0, $a0, 2
    jal two
skip:

    lw $ra, 0($sp)
    addi $sp, $sp, 12

    jr $ra

.data
prompt: .asciiz "Enter a size: "
