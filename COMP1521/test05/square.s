#print a square of asterisks
# x = t0
# i = t1
# j = t2
main:
    li   $v0, 5         #   scanf("%d", &x);
    syscall             #
    move $t0, $v0

loop1:
    bge $t1, $t0, end1  # if (i >= x) goto end1
    li $t2, 0           # j = 0

loop2:
    bge $t2, $t0, end2   # if (j >= x) goto end2

    li   $a0, '*'      #   printf("*")
    li   $v0, 11
    syscall

    addi $t2, $t2, 1    # j+=1
    j loop2
end2:

    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall

    addi $t1, $t1, 1    # i+=1
    j loop1
end1:

    li   $v0, 0         # return 0
    jr   $ra
