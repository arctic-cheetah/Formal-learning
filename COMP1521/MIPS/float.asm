
    .data
PI: .float 3.1415

    .text
    .globl main
main:
    li $v0, 2
    lwc1 $f12, PI
    syscall

    li $v0, 10
    syscall
