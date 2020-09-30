#C code:
#
#int main() {
#   int var1, var2, var3;
#   printf("Hello, please enter a number \n");
#   scanf("%d", &var1);
#   printf("Please enter a second number \n");
#   scanf("%d", &var2);
#   var3 = var1 + var2;
#   printf("The result is %d \n", var3);
#}

#MIPS code
    .data
msg1: .asciiz"Hi, please enter a number \n"
msg2: .asciiz"Please enter a second number \n"
msg3: .asciiz"The sum is: "
newLine: .asciiz"\n"

    .text
    .globl main

main:
    #display prompt
    li $v0, 4
    la $a0, msg1
    syscall

    #input the first number
    li $v0, 5
    syscall
    move $t0, $v0

    #display prompt for second input
    li $v0, 4
    la $a0, msg2
    syscall

    #input the second number
    li $v0, 5
    syscall
    move $t1, $v0

    #add the numbers
    add $t2, $t1, $t0

    #display the result text
    li $v0, 4
    la $a0, msg3
    syscall

    #display the sum
    li $v0, 1
    move $a0, $t2
    syscall

    #Print new newLine
    li $v0, 5
    la $a0, newLine
    syscall

    li $v0, 10
    syscall
