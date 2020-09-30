#A program that sums all of the natural numbers

#int main(){
#   int i = 0;
#   while (i < 10) {
#       i++;
#   }
#   printf("The sum is: \n", &i);
#}

#MIPS code
    .data
msg1: .asciiz"The sum is: \n"

    .text
    .globl main
main:
    li $t0, 0

while:
    beq $t0, 10, MessageSum
    addi $t0, $t0, 1
    j while

MessageSum:
    li $v0, 4
    la $a0, msg1
    syscall

    li $v0, 1
    move $a0, $t0
    syscall

    li $v0, 10
    syscall
