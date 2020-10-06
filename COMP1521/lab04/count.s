# read a number n and print the integers 1..n one per line
# t0 == number
# t1 == i


main:                           # int main(void)
    la  $a0, prompt             # printf("Enter a number: ");
    li  $v0, 4
    syscall

    li  $v0, 5                  # scanf("%d", number);
    syscall
    move $t0, $v0               # store in number

    li $t1, 1                   # i = 1;

loop:
    bgt $t1, $t0, endloop       # i > number, endloop

    move $a0, $t1                 # printf("%d", i);
    li $v0, 1
    syscall

    li   $a0, '\n'               # printf("%c", '\n');
    li   $v0, 11
    syscall

    addi $t1, $t1, 1              # i +=1
    b loop

endloop:
    li $v0, 10
    syscall


    .data
prompt: .asciiz "Enter a number: "
