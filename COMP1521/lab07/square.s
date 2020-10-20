#i = $t0

.text
main:

    addi $sp, $sp, -40  #allocate memory for the array by using the stack


loop1:
    bge $t0, 10, end1

    mul $t1, $t0, 4
    add $t2, $t1, $sp
    mul $t3, $t0, $t0
    sw $t3, ($t2)

    addi $t0, $t0, 1
    j loop1
end1:

    li $t0, 0

loop2:
    bge $t0, 10, end2

    mul $t1, $t0, 4
    add $t2, $t1, $sp
    lw $a0, ($t2)

    li $v0, 1
    syscall

    li $a0, '\n'
    li $v0, 11
    syscall

    addi $t0, $t0, 1
    j loop2
end2:

    addi $sp, $sp, 40

    li $v0, 10
    syscall
