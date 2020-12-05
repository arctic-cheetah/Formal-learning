# this code reads 1 integer and prints it
# change it to read integers until their sum is >= 42
# and then print their sum

#t0 = sum
#t1 = x

main:

loop1:
    bge $t0, 42, end1

    li   $v0, 5        #   scanf("%d", &x);
    syscall            #
    move $t1, $v0

    add $t0, $t0, $t1   #sum = sum + x;
    j loop1
end1:

    move $a0, $t0      #   printf("%d\n", x);
    li   $v0, 1
    syscall

    li   $a0, 10       #   printf("%c", '\n');
    li   $v0, 11
    syscall


    li   $v0, 0        # return 0
    jr   $ra
