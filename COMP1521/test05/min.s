#  print the minimum of two integers
# x = t0
# y = t1
main:
    li   $v0, 5         #   scanf("%d", &x);
    syscall             #
    move $t0, $v0

    li   $v0, 5         #   scanf("%d", &y);
    syscall             #
    move $t1, $v0

    bge $t0, $t1, cond2 # if (x >= y) goto cond2

cond1:
    move $a0, $t0       # printf("%d", x)
    li   $v0, 1
    syscall
    j end

cond2:
    move $a0, $t1       # printf("%d", y)
    li   $v0, 1
    syscall
    j end

end:
    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall

    li   $v0, 0         # return 0
    jr   $ra
