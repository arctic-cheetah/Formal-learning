#A program that takes user input

    .data
msg1: .asciiz"Enter a name \n"
msg2: .asciiz"Hi "
userInput: .space 2

    .text
    .globl main

main:

    #Ask name
    li $v0, 4
    la $a0, msg1
    syscall

    #Store user's name
    li $v0, 8
    la $a0, userInput
    li $a1, 3
    syscall

    #Print Hi
    li $v0, 4
    la $a0, msg2
    syscall

    #Print User name
    li $v0, 4
    la $a0, userInput
    syscall

    #end program
    li $v0, 10
    syscall
