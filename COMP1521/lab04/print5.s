# i = t0

.text
main:
    li $t0, 0

loop:
    bge $t0, 5, endloop
    la $t1, numbers     #remember t1 is a memory address!
    mul $t2, $t0, 4
    add $t3, $t2, $t1

    lw $a0, ($t3)
    li $v0, 1
    syscall

    li $a0, '\n'
    li $v0, 11
    syscall

    addi $t0, $t0, 1
    j loop
endloop:
    li $v0, 10
    syscall

.data
    numbers: .word 3, 9, 27, 81, 243
