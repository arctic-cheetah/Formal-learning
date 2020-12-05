#  print the minimum of two integers
#t0 = x
#t1 = y

main:
    li   $v0, 5         #   scanf("%d", &x);
    syscall             #
    move $t0, $v0

    li   $v0, 5         #   scanf("%d", &y);
    syscall             #
    move $t1, $v0

    bge $t0, $t1, skip  #if (x >= y) goto skip
    move $a0, $t0
skip:
    move $a0, $t1

    li   $v0, 1
    syscall
    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall

end:

    li $v0, 10
    syscall
