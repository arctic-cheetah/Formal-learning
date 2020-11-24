
main:

    li $t0, 300000
    add $a0, $t0, $a0
    li $v0, 1
    syscall

    li $v0, 10
    syscall

.data
