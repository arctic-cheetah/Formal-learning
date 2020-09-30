
    .data
    .text
    .globl main
        main:
        li $t0, 4
        li $t1, 4

        bge $t0, $t1, division
        add $t0, $t0, $t1

    division:
        div $t0, $t1
    exit:
    li $v0, 10
    syscall
