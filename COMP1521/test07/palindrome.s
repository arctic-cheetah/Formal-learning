# read a line and print whether it is a not_palindrome

#i = t0
#j = t1
#k = t2
# t3, t5 hold mem address line
# t4, t6 to hold char

main:
    la   $a0, str0       # printf("Enter a line of input: ");
    li   $v0, 4
    syscall

    la   $a0, line
    la   $a1, 256
    li   $v0, 8          # fgets(buffer, 256, stdin)
    syscall              #


    la $t3, line        #get the line length
    lb $t4, ($t3)

 loop1:
    beq $t4, 0, end1    #if (line[i] == 0) goto end1

    addi $t3, $t3, 1    #get line[i]
    lb $t4, ($t3)

    addi $t0, $t0, 1
    j loop1
 end1:

    or $t2, $t2, $t0    #k = i - 2
    addi $t2, $t2, -2

    li $t1, 0           #j = 0

    la $t3, line
    la $t5, line
    add $t5, $t5, $t2

loop2:
    bge $t1, $t2, end2

    lb $t4, ($t3)
    lb $t6, ($t5)

    beq $t4, $t6, continue
    la   $a0, not_palindrome
    li   $v0, 4
    syscall
    j end
continue:

    addi $t3, $t3, 1
    addi $t5, $t5, -1

    addi $t1, $t1, 1    #j +=1
    addi $t2, $t2, -1   #k -=1
    j loop2
end2:

    la   $a0, palindrome
    li   $v0, 4
    syscall

end:
    li   $v0, 0          # return 0
    jr   $ra


.data
str0:
    .asciiz "Enter a line of input: "
palindrome:
    .asciiz "palindrome\n"
not_palindrome:
    .asciiz "not palindrome\n"


# line of input stored here
line:
    .space 256
