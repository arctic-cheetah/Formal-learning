.text

main:
    la $t0, numbers
    addi $t1, $t0, 16
loop:
    bgt $t0, $t1, endloop

    lw $a0, ($t0)
    li $v0, 1
    syscall

    li $a0, '\n'
    li $v0, 11
    syscall

    addi $t0, $t0, 4
    j loop
endloop:
    li $v0, 10
    syscall



.data
    numbers: .word 3, 9, 27, 81, 243
