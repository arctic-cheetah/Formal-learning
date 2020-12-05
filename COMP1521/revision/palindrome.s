# read a line and print whether it is a palindrom
#t0 = i
#t1 = k
#t2 = j
#t3, t4 = line[]

main:
    la   $a0, str0       # printf("Enter a line of input: ");
    li   $v0, 4
    syscall

    la   $a0, line
    la   $a1, 256
    li   $v0, 8          # fgets(buffer, 256, stdin)
    syscall              #

loop0:
    beq $t3, '\n', end0  # if (line[i] == '\n') goto end0

    la $t3, line
    add $t3, $t3, $t0
    lb $t3, 0($t3)

    addi $t0, $t0, 1    # i+=1
    j loop0
end0:

    li $t2, 0           #j = 0
    addi $t1, $t0, -2   #k = i - 2

loop1:
    bge $t2, $t1, end1  #if (j >= k) goto end1

    la $t3, line        #line[j]
    add $t3, $t3, $t2
    lb $t3, 0($t3)

    la $t4, line        #line[k]
    add $t4, $t4, $t1
    lb $t4, 0($t4)

    beq $t3, $t4, skip  #if (line[j] == line[k]) goto skip

    la   $a0, not_palindrome
    li   $v0, 4
    syscall             #printf("not palindrome\n");
    j endprog
skip:

    addi $t2, $t2, 1    #j++;
    addi $t1, $t1, -1   #k--;
    j loop1
end1:

    la   $a0, palindrome
    li   $v0, 4
    syscall

endprog:
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
