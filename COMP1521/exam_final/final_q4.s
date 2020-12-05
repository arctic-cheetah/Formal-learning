# COMP1521 20T3 final exam Q4 starter code

# This code reads 1 integer and prints it

# Change it to read integers until low is greater or equal to high,
# then print their difference
#
#t0 = low
#t1 = high
#v0 = x

main:

    li $t0, 0           # low = 0
    li $t1, 100         # high = 100

loop0:
    bge $t0, $t1, end0  #if (low >= high) goto end0

    li   $v0, 5        #   scanf("%d", &x);
    syscall

    add $t0, $t0, $v0  #low +=x;
    sub $t1, $t1, $v0  #high -=x
    j loop0
end0:

    sub $a0, $t0, $t1   #low - high
    li   $v0, 1         #   printf("%d\n", x);
    syscall

    li   $a0, 10     #   printf("%c", '\n');
    li   $v0, 11
    syscall

    li   $v0, 0        #   return 0
    jr   $ra
