
    .text
    .globl main
main:
    #Show first prompt
    li $v0, 4
    la $a0, msg1
    syscall

    li $v0, 5
    syscall
    move $t0, $v0

    li $v0, 4
    la $a0, msg2
    syscall

    li $v0, 5
    syscall
    move $t1, $v0

    add $t2, $t1, $t0

    li $v0, 4
    la $a0, msg3
    syscall

    li $v0, 1
    move $a0, $t2
    syscall

    li $v0, 4
    la $a0, newline
    syscall

    li $v0, 10
    syscall


    .data

msg1:   .asciiz"Hello user, enter a first number \n"
msg2:   .asciiz"Hello again, enter a second number \n"
msg3:   .asciiz"The sum is: "
newline:    .asciiz"\n"
