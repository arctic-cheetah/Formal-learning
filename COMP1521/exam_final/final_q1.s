# COMP1521 20T3 final exam Q1 starter code

# This code reads 1 integer and prints it

# Change it to read 2 integers x and y,
# then print (x + y) * (x - y)

#t0 = x
#t1 = y
#x + y = t2
#x - y = a0

main:
    li   $v0, 5        #   scanf("%d", &x);
    syscall
    move $t0, $v0


    li   $v0, 5        #   scanf("%d", &y);
    syscall
    move $t1, $v0

    add $t2, $t0, $t1  #x + y = t2
    sub $a0, $t0, $t1  #x - y = a0
    mul $a0, $t2, $a0  #(x + y) * (x - y)



    li   $v0, 1         #   printf("%d\n", x);
    syscall

    li   $a0, '\n'     #   printf("%c", '\n');
    li   $v0, 11
    syscall

end:
    li   $v0, 0        #   return 0;
    jr   $ra
