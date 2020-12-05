# this code reads 1 integer and prints it
# change it to read integers until their sum is >= 42
# and then print theintgers read in reverse order

# t0 = i
# t1 = sum
# v0 = x
# t3 = number[]
# t4 = temp

main:

loop0:
    bge $t1, 42, end0

    li   $v0, 5        #   scanf("%d", &x);
    syscall            #

    la $t3, numbers     #calculate array index
    mul $t4, $t0, 4
    add $t3, $t3, $t4

    sw $v0, 0($t3)      #numbers[i] = x;

    addi $t0, $t0, 1    # i +=1
    add $t1, $t1, $v0   #sum +=x
    j loop0
end0:


loop1:
    ble $t0, 0, end1
    addi $t0, $t0, -1   # i-=1

    la $t3, numbers      #calculate array index
    mul $t4, $t0, 4
    add $t3, $t3, $t4
    lw $a0, 0($t3)

    li   $v0, 1
    syscall

    li   $a0, 10     #   printf("%c", '\n');
    li   $v0, 11
    syscall

    j loop1
end1:

    li   $v0, 0        # return 0
    jr   $ra

.data

numbers: .word 0:1000       #int numbers[1000];
