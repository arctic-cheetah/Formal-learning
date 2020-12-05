# this code reads 1 integer and prints it
# change it to read 2 integers
# then print their sum

#t0 = x
#t1 = y

main:
    li   $v0, 5        #   scanf("%d", &x);
    syscall            #
    move $t0, $v0      #   printf("%d\n", x);

    li $v0, 5
    syscall
    move $t1, $v0

    add $a0, $t1, $t0   #x + y

    li $v0, 1
    syscall

    li   $a0, '\n'     #   printf("%c", '\n');
    li   $v0, 11
    syscall

    li   $v0, 0        # return 0
    jr   $ra
