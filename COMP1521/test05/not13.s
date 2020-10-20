#print the integers between x and y except 13
# x = t0
# y = t1
# i = t2
main:
    li   $v0, 5         #   scanf("%d", &x);
    syscall             #
    move $t0, $v0

    li   $v0, 5         #   scanf("%d", &y);
    syscall             #
    move $t1, $v0

    addi $t2, $t0, 1    # i = x + 1

loop1:
    bge $t2, $t1, endloop1  # if (i >= y) goto endloop1

    beq $t2, 13, skip1      # if (t == 13) goto skip1

    move $a0, $t2       # printf("%d", i)
    li $v0, 1
    syscall

    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall
skip1:

    addi $t2, $t2, 1    # i+=1
    j loop1
endloop1:

    li   $v0, 0         # return 0
    jr   $ra
