
    .text
    .globl main
main:
    li $t1, 5
    li $t2, 5

    j jump_here

jump_here:
    li $t4, 5
    li $t5, 6

end:
    li$v0, 10
    syscall
