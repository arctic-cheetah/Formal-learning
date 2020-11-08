#  read a line from stdin and and then an integer n
#  Print the character in the nth-position

# n in $t0
# i = t1
# t2 = la the Line
# t3 = lb the line


main:
    la   $a0, str0       # printf("Enter a line of input: ");
    li   $v0, 4
    syscall

    la   $a0, line       # fgets(buffer, 256, stdin)
    la   $a1, 256
    li   $v0, 8
    syscall

    la   $a0, str1       # printf("Enter a position: ");
    li   $v0, 4
    syscall

    li   $v0, 5          # scanf("%d");
    syscall
    move $t0, $v0

    la $t2, line

loop1:
    bge $t1, $t0, end1

    addi $t2, $t2, 1

    addi $t1, $t1, 1
    j loop1
end1:

    la   $a0, str2       # printf("Character is: ");
    li   $v0, 4
    syscall


    lb $a0, ($t2)        # printf("%c", '?');
    li   $v0, 11
    syscall


    li   $a0, '\n'       # printf("%c", '\n');
    li   $v0, 11
    syscall

    li   $v0, 0          # return 0
    jr   $ra

.data
str0:
    .asciiz "Enter a line of input: "
str1:
    .asciiz "Enter a position: "
str2:
    .asciiz "Character is: "


# line of input stored here
line:
    .space 256
