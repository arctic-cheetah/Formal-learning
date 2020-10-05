#A MIPS program that implements a basic calculator

    .data
msg1: .asciiz "Enter the first number \n"
msgOp: .asciiz "Enter an operation + , - , *, / \n"
userOp: .space 3
msg2: .asciiz "Enter the second number \n"
msg3: .asciiz "The result is: \n"

plus: .asciiz "+"
minus: .asciiz "-"
times: .asciiz "*"
divide: .asciiz "\ "


    .text
    .globl main

main:
    #print the first message
    li $v0, 4
    la $a0, msg1
    syscall

    #Scan the first number and store in t0
    li $v0, 5
    syscall
    move $t0, $v0

    #Ask for the operation
    li $v0, 4
    la $a0, msgOp
    syscall

    #Store the operation
    li $v0, 8
    la $a0, userOp
    li $a1, 3
    move $t2, $a0
    syscall

    #Ask for the second number
    li $v0, 4
    la $a0, msg2
    syscall

    #Scan the second number and store in t1
    li $v0, 5
    syscall
    move $t1, $v0

    #Check if '+' is in t2... YES!
    #li $v0, 4
    #move $a0, $t2
    #syscall

    li $v0, 4
    la $a0, msg3
    syscall

    #If statements are here...aka branching
    move $a0, $t2
    la $a1, plus
    beq $a1, $a0, Add
    #la $a1, minus
    #beq $a1, $a0, Subtract
    #la $a1, times
    #beq $a1, $a0, Multiply

    #If there are no valid operations, terminate
    bne $a1, $a0, Exit


Add:
    add $t7, $t1, $t0

#Subtract:
    #sub $t9, $t1, $t0
#Multiply:
    #mul $t9, $t1, $t0

    #add the two integers
    #add $t9, $t1, $t0

    #display the sum

Exit:
    li $v0, 1
    move $a0, $t7
    syscall

    li $v0, 10
    syscall
