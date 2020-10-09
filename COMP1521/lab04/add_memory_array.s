.text
main:
    la $t0, x
    lw $t1, 0($t0)  # t1 = array[0]
    lw $t2, 4($t0)  # t2 = array[1]
    add $t3, $t2, $t1
    sw $t3, 8($t0)  # array[2] = array[1] + array[0]

    lw $a0, 8($t0)  # printf("%d", z)
    li $v0, 1
    syscall

    li $a0, '\n'    # printf("\n")
    li $v0, 11
    syscall

    li $v0, 10
    syscall



.data
x: .word 17, 25, 0
