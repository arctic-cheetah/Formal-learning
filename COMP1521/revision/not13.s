#t0 = x
#t1 = y
#t2 = i

main:
    li   $v0, 5         #   scanf("%d", &x);
    syscall             #
    move $t0, $v0

    li   $v0, 5         #   scanf("%d", &y);
    syscall             #
    move $t1, $v0

    add $t2, $t0, 1     #i = x + 1

loop1:
    bge $t2, $t1, end1  #if (i >= y) goto end1

    beq $t2, 13, skip   #if (i == 13) goto skip

    move $a0, $t2        #   printf("%d\n", 42);
    li   $v0, 1
    syscall
    li   $a0, 10      #   printf("%c", '\n');
    li   $v0, 11
    syscall
skip:

    addi $t2, $t2, 1
    j loop1
end1:

    li   $v0, 0         # return 0
    jr   $ra
