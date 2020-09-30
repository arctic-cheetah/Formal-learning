#A program that sums all of the natural numbers

#int main(){
#   int i = 0;
#   int j = 0;
#   printf("Enter the the upper bound: \n");
#   scanf("%d", j);
#   while (i < j) {
#       i++;
#   }
#   printf("The sum is: \n", &i);
#}

#MIPS code
    .data
msg1: .asciiz"Enter an upper bound: \n"
msg2: .asciiz"The sum is: \n"

    .text
    .globl main
main:
    li $t0, 0
    #Ask the user to enter an upper bound
    li $v0, 4
    la $a0, msg1
    syscall

    #Obtain input from the user and store in t1
    li $v0, 5
    syscall
    move $t1, $v0

while:
    bgt $t0, $t1, MessageSum #($t1 > $t0) then continue with loop
    add $t2, $t2, $t0 # t2 = t2 + t1
    addi $t0, $t0, 1 # t1++;
    j while

MessageSum:
    #Print the text "The sum is"
    li $v0, 4
    la $a0, msg2
    syscall

    #print the sum
    li $v0, 1
    move $a0, $t2
    syscall

    #end the program
    li $v0, 10
    syscall
